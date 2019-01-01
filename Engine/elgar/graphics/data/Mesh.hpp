/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_MESH_HPP_
#define _ELGAR_MESH_HPP_

// INCLUDES //

#include "elgar/graphics/data/Vertex.hpp"
#include "elgar/graphics/data/Texture.hpp"
#include "elgar/graphics/data/RGBA.hpp"
#include "elgar/graphics/buffers/BufferObject.hpp"
#include "elgar/graphics/buffers/VertexArrayObject.hpp"
#include "elgar/graphics/Shader.hpp"

#include <vector>

namespace elgar {

  /**
   * @brief A Mesh is a collection of Vertices to be rendered together
   * 
   */
  class Mesh {
  private:
    std::vector<Vertex> m_vertices;   // The vertices of the Mesh
    std::vector<GLuint> m_indices;    // The indices of the Mesh
    std::vector<const Texture *> m_textures;    // The textures of the Mesh

    RGBA m_color;     // The Mesh color

  private:
    VertexArrayObject m_vao;          // The vertex array object for the mesh
    BufferObject      m_vbo;          // The vertex buffer for the mesh
    BufferObject      m_ebo;          // The element buffer for the mesh

  public:
    /**
     * @brief Construct a new Mesh object
     * 
     * @param vertices    The vertices of the Mesh
     * @param indices     The element indices of the Mesh
     * @param textures    The textures of the Mesh
     * @param color       The color of the Mesh
     */
    Mesh(
      const std::vector<Vertex> vertices,
      const std::vector<GLuint> indices,
      const std::vector<const Texture *> textures,
      const RGBA &color
    );

    /**
     * @brief Destroy the Mesh object
     * 
     */
    virtual ~Mesh();

    /**
     * @brief Draw the Mesh using a Shader program
     * 
     * @param shader    Const reference to the compiled Shader to render with
     */
    void Draw(const Shader &shader) const;

  };

}

#endif