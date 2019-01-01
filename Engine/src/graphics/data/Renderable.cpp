/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/data/Renderable.hpp"

namespace elgar {
  
  // FUNCTIONS //

  Renderable::Renderable() : 
    m_vertex_buffer(GL_ARRAY_BUFFER), 
    m_uv_buffer(GL_ARRAY_BUFFER),
    m_color_buffer(GL_ARRAY_BUFFER),
    m_element_buffer(GL_ELEMENT_ARRAY_BUFFER)
  {
    // Do nothing
  }

  Renderable::~Renderable() {
    // Do nothing
  }

}