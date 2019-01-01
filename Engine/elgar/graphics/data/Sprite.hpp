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
#include "elgar/graphics/data/RGBA.hpp"

#include "elgar/graphics/buffers/VertexArrayObject.hpp"
#include "elgar/graphics/buffers/BufferObject.hpp"

#include "elgar/graphics/data/Renderable.hpp"

#include <vector>

namespace elgar {

  /**
   * @brief      A Sprite is a 2D textured quad that can be rendered
   */
  class Sprite : public Renderable {
  friend class Renderer2D;  // Grant Renderer2D privileges
  private:
    const Texture *m_texture;   // The texture for the Sprite

  private:
    static const std::vector<glm::vec2> m_default_uvs;        // The sprite uv's
    static const std::vector<glm::vec3> m_default_vertices;   // The sprite vertices

  public:
    /**
     * @brief Construct a new Sprite object
     * 
     * @param texture   The texture to use for the Sprite (defaults to nullptr)
     */
    Sprite(const Texture *texture = nullptr);

    /**
     * @brief Destroy the Sprite object
     * 
     */
    virtual ~Sprite();

    /**
     * @brief Set the Texture for the Sprite
     * 
     * @param texture The Texture to set for the sprite
     */
    void SetTexture(const Texture *texture);

    /**
     * @brief Get the Texture of the Sprite
     * 
     * @return The sprite's texture, or nullptr if no texture 
     */
    const Texture *GetTexture() const;

    /**
     * @brief Get the default vertices of the sprite
     * 
     * @return A vector containing the vertices
     */
    static const std::vector<glm::vec3> &GetDefaultVertices();

    /**
     * @brief Get the default texture coordinates of the sprite
     * 
     * @return Reference to the texture coordinates
     */
    static const std::vector<glm::vec2> &GetDefaultTexCoords();

    /**
     * @brief Draw the Sprite using a Shader
     * 
     * @param shader          The shader program to render with
     * @param color           The color to draw with
     * @param model_matrix    The model matrix to translate by
     */
    void Draw(
      const Shader &shader, 
      const RGBA &color,
      const glm::mat4 &model_matrix) const;

    /**
     * @brief Draw the Sprite multiple times with one draw call using Instancing
     * 
     * @param shader          The shader program to use
     * @param model_matrices  The set of model matrices
     */
    void DrawInstanced(
      const Shader &shader, 
      const std::vector<const glm::mat4> &model_matrices
    ) const;

  };

}

#endif