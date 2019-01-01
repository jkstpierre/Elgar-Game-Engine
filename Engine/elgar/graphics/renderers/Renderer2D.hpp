/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_RENDERER_2D_HPP_
#define _ELGAR_RENDERER_2D_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"

#include "elgar/graphics/data/Vertex.hpp"
#include "elgar/graphics/buffers/BufferObject.hpp"
#include "elgar/graphics/buffers/VertexArrayObject.hpp"
#include "elgar/graphics/Shader.hpp"

namespace elgar {

  /**
   * @brief The Renderer2D class handles the rendering of 2D Sprites to the screen.
   * 
   */
  class Renderer2D : public Singleton< Renderer2D > {
  friend class Engine;  // Allow Engine to instantiate
  friend class Sprite;  // Allow Sprites to Register for drawing
  friend class Window;  // Allow Window to Present
  private:
    /**
     * @brief Construct a new Renderer2D instance
     * 
     */
    Renderer2D();

  };

}

#endif