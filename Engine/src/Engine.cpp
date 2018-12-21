/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <AL/al.h>

#include "elgar/Engine.hpp"
#include "elgar/core/Exception.hpp"
#include "elgar/core/Macros.hpp"
#include "elgar/timers/FrameTimer.hpp"

namespace elgar {

  // STATIC FIELDS //

  Engine *Engine::m_instance = nullptr; // No engine instance at program start
  
  // FUNCTIONS //

  Engine::Engine() {
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

    m_running = false;

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

  void Engine::Init() {
    if (!m_instance)
      m_instance = new Engine();  // Create an engine instance if one does not yet exist
  }

  void Engine::Shutdown() {
    if (m_instance)
      delete m_instance;  // Destroy the engine if it exists

    m_instance = nullptr;
  }

  Engine *Engine::GetInstance() {
    return m_instance;  // Return handle to the engine instance
  }

  void Engine::Run(void (*update)(), void (*fixed_update)(), void (*render)()) {
    // If engine is already running, do nothing
    if (IsRunning()) 
      return;

    m_running = true; // Engine is now running

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
          m_running = false;
        }
        else if (e.type == SDL_KEYDOWN) {
          // Handle key press
        }
        else if (e.type == SDL_KEYUP) {
          // Handle key release
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
          // Handle mouse click
        }
        else if (e.type == SDL_MOUSEBUTTONUP) {
          // Handle mouse release
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