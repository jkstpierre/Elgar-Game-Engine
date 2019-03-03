/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

// INCLUDES //

#include "elgar/graphics/data/Texture.hpp"
#include "elgar/graphics/data/RGBA.hpp"

#include <glm/glm.hpp>

#include <vector>

namespace elgar {

  /**
   * @brief A Sprite is a 2D renderable entity to be rendered by the SpriteRenderer
   * 
   */
  class Sprite {
  private:
    std::vector<glm::vec2> m_uvs;   // The sprite uv's
    RGBA m_color;   // The color of the sprite
    const Texture *m_texture;   // The sprite texture

  public:
    /**
     * @brief Construct a new Sprite object
     * 
     * @param texture   The texture of the Sprite
     * @param color     The color of the Sprite
     * @param uv_array  The Sprite texture UV's
     */
    Sprite(const Texture *texture, const RGBA &color, const std::vector<glm::vec2> uv_array);

    /**
     * @brief Destroy the Sprite object
     * 
     */
    virtual ~Sprite();

    /**
     * @brief Get the TextureCoords object
     * 
     * @return Reference to the texture uv's
     */
    const std::vector<glm::vec2> &GetTextureCoords() const;

    /**
     * @brief Get the Texture object
     * 
     * @return Pointer to the Texture
     */
    const Texture *GetTexture() const;

    /**
     * @brief Get the Color object
     * 
     * @return Reference to the Color of the Sprite
     */
    const RGBA &GetColor() const;
  };

}