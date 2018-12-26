/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "elgar/Engine.hpp"
#include "elgar/core/Exception.hpp"
#include "elgar/core/IO.hpp"
#include "elgar/core/Macros.hpp"
#include "elgar/core/AudioSystem.hpp"
#include "elgar/core/Window.hpp"

#include "elgar/timers/FrameTimer.hpp"

#include "elgar/graphics/TextureManager.hpp"
#include "elgar/graphics/ShaderManager.hpp"

namespace elgar {

  // FUNCTIONS //

  Engine::Engine(
      const std::string &window_name, 
      const int &window_width, 
      const int &window_height, 
      const unsigned char &window_flags
  ) : Singleton<Engine>(this) {
    // Initialize subsystems

    int code = 0; // A response code to check for errors with

    code = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER); // Initialize Video, events, and time handling

    // If something went wrong
    if (code < 0) {
      throw Exception("ERROR: Failed to initialize SDL! SDL_Error: " + std::string(SDL_GetError()));
    }

    // Enable PNG image loading
    int flags = IMG_INIT_PNG;
    code = IMG_Init(flags); 

    // If something went wrong
    if ((code & flags) != flags) {
      throw Exception("ERROR: Failed to initialize SDL2_image! SDL_Error: " + std::string(IMG_GetError()));
    }

    // Enable true type fonts
    code = TTF_Init();

    // If something went wrong
    if(code < 0) {
      throw Exception("ERROR: Failed to initialize SDL2_ttf! SDL_Error: " + std::string(TTF_GetError()));
    }

    // Initialize elgar subsystems

    // Initialize the window
    Window::SetInstance(new Window(window_name, window_width, window_height, window_flags));

    // Initialize the audio subsystem
    AudioSystem::SetInstance(new AudioSystem());

    // Initialize the texture manager
    TextureManager::SetInstance(new TextureManager());

    // Initialize the shader manager
    ShaderManager::SetInstance(new ShaderManager());

    SetRunning(false);  // Engine is not running by default

    // Give status log
    LOG("Elgar online...\n");
  }

  Engine::~Engine() {
    // Terminate subsystems

    // Destroy the audio system
    if (AudioSystem::GetInstance()) {
      delete AudioSystem::GetInstance();
    }

    // Destroy the TextureManager instance
    if (TextureManager::GetInstance()) {
      delete TextureManager::GetInstance();
    }

    // Destroy the ShaderManager instance
    if (ShaderManager::GetInstance()) {
      delete ShaderManager::GetInstance();
    }

    // Destroy the Window instance
    if (Window::GetInstance()) {
      delete Window::GetInstance();
    }

    TTF_Quit(); // Shutdown SDL_ttf
    IMG_Quit(); // Shutdown SDL_image
    SDL_Quit(); // Shutdown SDL

    LOG("Elgar offline...\n");
  }

  void Engine::Run(void (*update)(), void (*fixed_update)(), void (*render)()) {
    // If engine is already running, do nothing
    if (IsRunning()) 
      return;

    SetRunning(true); // Engine is now running

    // Struct to store event data
    SDL_Event e;

    /* Frame delta time variables */
    float delta_time = 1.0f / DEFAULT_PHYS_STEPS_PER_SECOND;
    
    // Set the global fixed dt
    FrameTimer::SetFixedDeltaTime(delta_time);

    float current_time = (float) SDL_GetTicks() / 1000.0f;
    float accumulator = 0.0f;

    while (m_running) {
      /* BEGIN APPLICATION LOOP */

      // Poll for events
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
          SetRunning(false);
        }
        else if (e.type == SDL_KEYDOWN) {
          // Handle key press

          Keyboard::PressKey(e.key.keysym.sym);
        }
        else if (e.type == SDL_KEYUP) {
          // Handle key release

          Keyboard::ReleaseKey(e.key.keysym.sym);
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
          // Handle mouse click

          if (e.button.button == SDL_BUTTON_LEFT) {
            Mouse::PressButton(LEFT); // Handle left click
          }
          else if (e.button.button == SDL_BUTTON_RIGHT) {
            Mouse::PressButton(RIGHT);  // Handle right click
          }
        }
        else if (e.type == SDL_MOUSEBUTTONUP) {
          // Handle mouse release

          if (e.button.button == SDL_BUTTON_LEFT) {
            Mouse::ReleaseButton(LEFT); // Handle left release 
          }
          else if (e.button.button == SDL_BUTTON_RIGHT) {
            Mouse::ReleaseButton(RIGHT);  // Handle right release
          }
        }
        else if (e.type == SDL_MOUSEMOTION) {
          // Handle mouse motion
          Mouse::SetPosition({e.motion.x, e.motion.y});
        }
      }

      // Compute the frame time
      float new_time = (float) SDL_GetTicks() / 1000.0f;
      float frame_time = new_time - current_time;
      if (frame_time > 0.25) 
        frame_time = 0.25;

      current_time = new_time;

      if (update) {
        FrameTimer::SetDeltaTime(frame_time); // Set the global delta time
        update(); // Call the supplied user update function
      }

      // Handle phys steps
      if (fixed_update) {
        accumulator += frame_time;

        while (accumulator >= delta_time) {
          fixed_update();
          accumulator -= delta_time;
        }
      }

      // Compute interpolated alpha for rendering
      const float alpha = accumulator / delta_time; 

      FrameTimer::SetAlpha(alpha);  // Update global alpha

      // Draw the window contents
      if (Window::GetInstance())
        Window::GetInstance()->Present(render);
    }
  }

  bool Engine::IsRunning() const {
    return m_running;
  }

  void Engine::SetRunning(const bool &running) {
    m_running = running;
  }

}