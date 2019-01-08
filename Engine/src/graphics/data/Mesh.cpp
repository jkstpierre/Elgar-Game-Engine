/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/data/Mesh.hpp"
#include "elgar/core/Exception.hpp"

namespace elgar {

  // FUNCTIONS //

  Mesh::Mesh(
    const std::vector<Vertex> &vertices,
    const std::vector<GLuint> &indices,
    const std::vector<const Texture *> &textures
  ) {
    // Check for invalid mesh size
    if (vertices.size() > MESH_MAX_VERTEX_COUNT)
      throw Exception("ERROR: Attempted to create mesh with too many vertices!");

    if (indices.size() > MESH_MAX_INDEX_COUNT)
      throw Exception("ERROR: Attempted to create mesh with too many indices!");

    // Copy the vertices
    m_vertices = vertices;

    // Copy the indices
    m_indices = indices;

    // Copy the textures
    m_textures = textures;
  }

  Mesh::~Mesh() {
    // Do nothing
  }

  const std::vector<Vertex> &Mesh::GetVertices() const {
    return m_vertices;
  }

  const std::vector<GLuint> &Mesh::GetIndices() const {
    return m_indices;
  }

  const std::vector<const Texture *> &Mesh::GetTextures() const {
    return m_textures;
  }

}