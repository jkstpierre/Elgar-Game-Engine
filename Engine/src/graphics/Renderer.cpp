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
    LOG("Rendering context created!\n");
  }

  Renderer::~Renderer() {
    LOG("Rendering context destroyed!\n");
  }

}