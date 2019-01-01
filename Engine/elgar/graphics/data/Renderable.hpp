/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_RENDERABLE_HPP_
#define _ELGAR_RENDERABLE_HPP_

// INCLUDES //

#include <glm/glm.hpp>
#include <vector>

#include "elgar/graphics/buffers/VertexArrayObject.hpp"
#include "elgar/graphics/buffers/BufferObject.hpp"
#include "elgar/graphics/data/RGBA.hpp"

#include "elgar/graphics/Shader.hpp"

namespace elgar {

  /**
   * @brief      A Renderable is an abstract base class for encapsulating relevant functionality for 
   *             all objects that get displayed by a Renderer.
   */
  class Renderable {
  protected:
    VertexArrayObject m_vao;            // The vertex array object
    BufferObject      m_vertex_buffer;  // Vertex data buffer
    BufferObject      m_uv_buffer;      // UV data buffer
    BufferObject      m_color_buffer;   // Color data buffer

    BufferObject      m_element_buffer; // The element buffer

  public:
    /**
     * @brief Construct a new Renderable object
     * 
     */
    Renderable();

    /**
     * @brief Destroy the Renderable object
     * 
     */
    virtual ~Renderable();

    /**
     * @brief Draw the renderable using a Shader program
     * 
     * @param shader          The shader program to render with
     * @param color           The color to render with
     * @parma model_matrix    The model matrix to render with
     */
    virtual void Draw(
      const Shader &shader, 
      const RGBA &color,
      const glm::mat4 &model_matrix) const = 0;

    /**
     * @brief Draw the renderable using instanced rendering
     * 
     * @param shader            The shader program to use
     * @param model_matrices    The model matrices to use
     */
    virtual void DrawInstanced(
      const Shader &shader, 
      const std::vector<const glm::mat4> &model_matrices
    ) const = 0;

  };

}

#endif