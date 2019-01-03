/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

#ifndef _ELGAR_SPRITE_RENDERER_HPP_
#define _ELGAR_SPRITE_RENDERER_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"
#include "elgar/graphics/buffers/VertexArrayObject.hpp"
#include "elgar/graphics/buffers/BufferObject.hpp"

#include "elgar/graphics/data/Texture.hpp"
#include "elgar/graphics/data/RGBA.hpp"
#include "elgar/graphics/Shader.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace elgar {
  
  /**
   * @brief The SpriteRenderer class handles the rendering of all Sprites (2D graphics objects)
   * 
   */
  class SpriteRenderer : public Singleton<SpriteRenderer> {
  friend class Engine;
  private:
    VertexArrayObject m_vao;              // The VAO for the Sprite Renderer
    BufferObject      m_vertex_buffer;    // Buffer to store the vertex data of a Sprite
    BufferObject      m_uv_buffer;        // Buffer to store the uv data of a Sprite

  private:
    /**
     * @brief Construct a new SpriteRenderer object
     * 
     */
    SpriteRenderer();

    /**
     * @brief Destroy the SpriteRenderer object
     * 
     */
    virtual ~SpriteRenderer();

  public:
    /**
     * @brief Draws a Sprite to the screen
     * 
     * @param shader    The shader program to use for drawing
     * @param model     The model matrix for the sprite (contains all information regarding position, size, and rotation)
     * @param color     The color to draw the sprite with
     * @param texture   The texture to use for the sprite (set to nullptr to draw without texture)
     */
    void Draw(
      const Shader &shader,
      const glm::mat4 &model,
      const RGBA &color,
      const Texture *texture 
    );

    /**
     * @brief Draw a set of sprites with a single draw call using Instancing
     * 
     * @param shader    The shader program to use (must be compatible with instancing)
     * @param models    The set of model matrices for each sprite
     * @param color     The color to draw the sprites with
     * @param texture   The texture to draw each sprite with
     */
    void DrawInstanced(
      const Shader &shader,
      const std::vector<glm::mat4> &models,      
      const RGBA &color,
      const Texture *texture
    );

  };

}

#endif