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
#include "elgar/timers/FrameTimer.hpp"

namespace elgar {

  // FUNCTIONS //

  Engine::Engine() {
    // Check to make sure engine is only instantiated once
    if (InstanceCounter<Engine>::GetCount() > 1) {
      InstanceCounter<Engine>::SetCount(1);

      throw Exception("ERROR: Elgar has already been initialized!");
    }

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

    // Initialize the audio subsystem
    m_audio_system = new AudioSystem();

    SetRunning(false);  // Engine is not running by default

    SetWindow(nullptr); // No window by default

    // Give status log
    LOG("Elgar online...\n");
  }

  Engine::~Engine() {
    // Terminate subsystems

    if (m_audio_system)
      delete m_audio_system;

    if (m_window)
      delete m_window;

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
    }
  }

  bool Engine::IsRunning() const {
    return m_running;
  }

  void Engine::SetRunning(const bool &running) {
    m_running = running;
  }

  AudioSystem *Engine::GetAudioSystem() {
    return m_audio_system;  // Return handle to the audio system
  }

  void Engine::SetWindow(Window *window) {
    m_window = window;
  }

  const Window *Engine::GetWindow() {
    return m_window;
  }
}