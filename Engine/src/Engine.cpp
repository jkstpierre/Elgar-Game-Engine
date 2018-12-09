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

    // Give status log
    LOG("Elgar online...\n");
  }

  Engine::~Engine() {
    // Terminate subsystems

    if (m_audio_system)
      delete m_audio_system;

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

  AudioSystem *Engine::GetAudioSystem() {
    return m_audio_system;  // Return handle to the audio system
  }
}