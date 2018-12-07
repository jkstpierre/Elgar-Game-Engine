/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/Engine.hpp"

namespace elgar {

  // STATIC FIELDS //

  Engine *Engine::m_instance = nullptr; // No engine instance at program start
  
  // FUNCTIONS //

  Engine::Engine() {

  }

  Engine::~Engine() {

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
};