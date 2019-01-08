/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include <SDL2/SDL.h>

#include "elgar/Engine.hpp"
#include "elgar/core/Exception.hpp"
#include "elgar/core/IO.hpp"
#include "elgar/core/Macros.hpp"
#include "elgar/core/AudioSystem.hpp"
#include "elgar/core/Window.hpp"

#include "elgar/timers/FrameTimer.hpp"

#include "elgar/graphics/ImageLoader.hpp"
#include "elgar/graphics/ModelLoader.hpp"
#include "elgar/graphics/TextureStorage.hpp"
#include "elgar/graphics/ShaderManager.hpp"
#include "elgar/graphics/MeshManager.hpp"

#include "elgar/graphics/renderers/SpriteRenderer.hpp"
#include "elgar/graphics/renderers/TextRenderer.hpp"
#include "elgar/graphics/renderers/MeshRenderer.hpp"

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

    // Initialize the window
    new Window(window_name, window_width, window_height, window_flags);

    // Initialize elgar subsystem //

    InitSubsystems();

    SetRunning(false);  // Engine is not running by default

    // Give status log
    LOG("Elgar online...\n");
  }

  Engine::~Engine() {
    // Terminate subsystems

    DisableSubsystems();

    // Destroy the Window instance
    if (Window::GetInstance()) 
      delete Window::GetInstance();

    SDL_Quit(); // Shutdown SDL

    LOG("Elgar offline...\n");
  }

  void Engine::InitSubsystems() {
    // Initialize the audio subsystem
    new AudioSystem();

    // Initialize the image loader
    new ImageLoader();

    // Initialize the shader manager and compile all shader programs
    new ShaderManager();

    // Initialize the mesh manager and create all default meshes
    new MeshManager();

    // Initialize TextureStorage
    new TextureStorage();

    // Initialize the SpriteRenderer
    new SpriteRenderer();

    // Initialize the TextRenderer
    new TextRenderer();

    // Initialize the MeshRenderer
    new MeshRenderer();

    // Initialize the ModelLoader
    new ModelLoader();

  }

  void Engine::DisableSubsystems() {

    // Destroy the ShaderManager instance
    if (ShaderManager::GetInstance()) 
      delete ShaderManager::GetInstance();

    // Destroy the MeshManager instance
    if (MeshManager::GetInstance())
      delete MeshManager::GetInstance();

    // Destroy the Renderer2D instance
    if (SpriteRenderer::GetInstance())
      delete SpriteRenderer::GetInstance();

    // Destroy the TextRenderer instance
    if (TextRenderer::GetInstance())
      delete TextRenderer::GetInstance();

    // Destroy the MeshRenderer instance
    if (MeshRenderer::GetInstance())
      delete MeshRenderer::GetInstance();

    if (ModelLoader::GetInstance())
      delete ModelLoader::GetInstance();

    // Destroy the TextureStorage instance
    if (TextureStorage::GetInstance())
      delete TextureStorage::GetInstance();

    // Destroy the ImageLoader instance
    if (ImageLoader::GetInstance()) 
      delete ImageLoader::GetInstance();

    // Destroy the audio system
    if (AudioSystem::GetInstance()) 
      delete AudioSystem::GetInstance();
    
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
    
    // Create new frame timer and set the global fixed dt
    FrameTimer *frame_timer = new FrameTimer();
    frame_timer->SetFixedDeltaTime(delta_time);

    // Create the keyboard and mouse
    Keyboard *keyboard = new Keyboard();
    Mouse *mouse = new Mouse();

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

          keyboard->PressKey(e.key.keysym.sym);
        }
        else if (e.type == SDL_KEYUP) {
          // Handle key release

          keyboard->ReleaseKey(e.key.keysym.sym);
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
          // Handle mouse click

          if (e.button.button == SDL_BUTTON_LEFT) {
            mouse->PressButton(LEFT); // Handle left click
          }
          else if (e.button.button == SDL_BUTTON_RIGHT) {
            mouse->PressButton(RIGHT);  // Handle right click
          }
        }
        else if (e.type == SDL_MOUSEBUTTONUP) {
          // Handle mouse release

          if (e.button.button == SDL_BUTTON_LEFT) {
            mouse->ReleaseButton(LEFT); // Handle left release 
          }
          else if (e.button.button == SDL_BUTTON_RIGHT) {
            mouse->ReleaseButton(RIGHT);  // Handle right release
          }
        }
        else if (e.type == SDL_MOUSEMOTION) {
          // Handle mouse motion
          mouse->SetPosition({e.motion.x, e.motion.y});
        }
      }

      // Compute the frame time
      float new_time = (float) SDL_GetTicks() / 1000.0f;
      float frame_time = new_time - current_time;
      if (frame_time > 0.25) 
        frame_time = 0.25;

      current_time = new_time;

      if (update) {
        frame_timer->SetDeltaTime(frame_time); // Set the global delta time
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

      // Compute the alpha
      frame_timer->SetAlpha(accumulator / delta_time);  // Update global alpha

      // Draw the window contents
      if (Window::GetInstance())
        Window::GetInstance()->Present(render);
    }

    // Delete the FrameTimer
    delete frame_timer;

    // Delete the keyboard
    delete keyboard;

    // Delete the mouse
    delete mouse;
  }

  bool Engine::IsRunning() const {
    return m_running;
  }

  void Engine::SetRunning(const bool &running) {
    m_running = running;
  }

}