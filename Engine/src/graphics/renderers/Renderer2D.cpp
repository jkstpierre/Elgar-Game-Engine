/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/renderers/Renderer2D.hpp"
#include "elgar/graphics/ShaderManager.hpp"
#include "elgar/core/Macros.hpp"

// DEFINES //

#define DEFAULT_MAX_BATCH_SIZE    10000     // The default max number of objects per batch


namespace elgar {

  // FUNCTIONS //
  Renderer2D::Renderer2D() : Singleton<Renderer2D>(this) {

  }

}