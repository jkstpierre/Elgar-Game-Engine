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
#include "elgar/graphics/buffers/BufferObject.hpp"
#include "elgar/graphics/buffers/VertexArrayObject.hpp"
#include "elgar/graphics/Shader.hpp"

#include <vector>

// DEFINES //

#define MESH_MAX_VERTEX_COUNT   65536
#define MESH_MAX_INDEX_COUNT    MESH_MAX_VERTEX_COUNT * 6   // TODO: Figure out actual max later

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

  public:
    /**
     * @brief Construct a new Mesh object
     * 
     * @param vertices    The vertices of the Mesh
     * @param indices     The element indices of the Mesh
     * @param textures    The textures of the Mesh
     */
    Mesh(
      const std::vector<Vertex> &vertices,
      const std::vector<GLuint> &indices,
      const std::vector<const Texture *> &textures
    );

    /**
     * @brief Destroy the Mesh object
     * 
     */
    virtual ~Mesh();

    /**
     * @brief Get the vertices of the Mesh as a reference
     * 
     * @return Reference to the vertices of the Mesh
     */
    const std::vector<Vertex> &GetVertices() const;

    /**
     * @brief Get the indices of the Mesh as a reference
     * 
     * @return Reference to the indices of the Mesh
     */
    const std::vector<GLuint> &GetIndices() const;

    /**
     * @brief Get the textures of the Mesh as a reference
     * 
     * @return Reference to the textures of the Mesh
     */
    const std::vector<const Texture *> &GetTextures() const;

  };

}

#endif