/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_SPRITE_HPP_
#define _ELGAR_SPRITE_HPP_

// INCLUDES //

#include "elgar/graphics/data/Vertex.hpp"
#include "elgar/graphics/data/Texture.hpp"

#include "elgar/physics/InterpolatedMovable.hpp"

// DEFINES //

#define SPRITE_VERTEX_COUNT   4   // Number of vertices for a Sprite

namespace elgar {

  /**
   * @brief      A Sprite is a 2D textured quad that can be rendered
   */
  class Sprite : public InterpolatedMovable {
  private:
    const Texture *m_texture;   // The texture for the Sprite

    Vertex m_vertices[SPRITE_VERTEX_COUNT] = {
      {
        {0.0f, 0.0f, 0.0f},   // Bottom left position
        {0.0f, 0.0f},         // Bottom left uv
        {255, 255, 255, 255}  // Default to white
      },
      {
        {1.0f, 0.0f, 0.0f},   // Bottom right position
        {1.0f, 0.0f},         // Bottom right uv
        {255, 255, 255, 255}  // Default to white
      },
      {
        {1.0f, 1.0f, 0.0f},   // Top right position
        {1.0f, 1.0f},         // Top right uv
        {255, 255, 255, 255}  // Default to white
      },
      {
        {0.0f, 1.0f, 0.0f},   // Top left position
        {0.0f, 1.0f},         // Top left uv
        {255, 255, 255, 255}  // Default to white
      }
    };   // The default vertices for the Sprite

    glm::vec3 m_dimensions; // The dimensions of the Sprite

  public:
    /**
     * @brief Construct a new Sprite object
     * 
     * @param width     The width of the Sprite in scene units
     * @param height    The height of the Sprite in scene units
     * @param texture   The texture to use for the sprite (defaults to nullptr)
     */
    Sprite(const GLfloat &width, const GLfloat &height, const Texture *texture = nullptr);

    /**
     * @brief Destroy the Sprite object
     * 
     */
    virtual ~Sprite();

    /**
     * @brief Set the color for the Sprite
     * 
     * @param color The RGBA color for the Sprite
     */
    void SetColor(const RGBA &color);

    /**
     * @brief Change the color for the SpriteS
     * 
     * @param delta_color The change in color for the sprite
     */
    void ChangeColor(const RGBA & delta_color);

    /**
     * @brief Set the Texture for the Sprite
     * 
     * @param texture The Texture to set for the sprite
     */
    void SetTexture(const Texture *texture);

    /**
     * @brief Set the dimensions of the Sprite
     * 
     * @param width   The width of the Sprite
     * @param height  The height of the Sprite
     */
    void SetDimensions(const float &width, const float &height);

    /**
     * @brief Change the dimensions of the Sprite
     * 
     * @param delta_width   The change in width
     * @param delta_height  The change in height
     */
    void ChangeDimensions(const float &delta_width, const float &delta_height);

  private:
    /**
     * @brief Helper function for updating the dimensions in the vertices
     * 
     */
    void UpdateDimensions();
  };

}

#endif