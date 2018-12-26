/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/Renderer.hpp"
#include "elgar/core/Macros.hpp"

namespace elgar {

  // FUNCTIONS //

  Renderer::Renderer() {
    LOG("Renderer created!\n");
  }

  Renderer::~Renderer() {
    LOG("Renderer destroyed!\n");
  }

}