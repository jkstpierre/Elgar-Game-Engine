/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/data/Mesh.hpp"

namespace elgar {

  // FUNCTIONS //

  Mesh::Mesh(
    const std::vector<Vertex> vertices,
    const std::vector<GLuint> indices,
    const std::vector<const Texture *> textures,
    const RGBA &color
  ) : m_vbo(GL_ARRAY_BUFFER), m_ebo(GL_ELEMENT_ARRAY_BUFFER) {
    // Copy the vertices
    m_vertices = vertices;

    // Copy the indices
    m_indices = indices;

    // Copy the textures
    m_textures = textures;

    // Copy the color
    m_color = color;

    // Setup the Mesh
    m_vao.Bind(); // Bind the VAO
   
    m_vbo.Bind(); // Bind the VBO
    // Send the vertex data to the GPU
    m_vbo.FillData(&m_vertices[0], m_vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);

    m_ebo.Bind(); // Bind the element buffer
    // Send the element data to the GPU
    m_ebo.FillData(&m_indices[0], m_indices.size() * sizeof(GLuint), GL_STATIC_DRAW);

    // Setup the vertex attributes

    // Setup position attribute at location 0
    m_vao.EnableAttribute(0);
    m_vao.AttributePointer(
      0,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (GLvoid *)0
    );

    // Setup normal attribute at location 1
    m_vao.EnableAttribute(1);
    m_vao.AttributePointer(
      1,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (GLvoid *)offsetof(Vertex, m_normal)
    );

    // Setup texture uv attribute at location 2
    m_vao.EnableAttribute(2);
    m_vao.AttributePointer(
      2,
      2,
      GL_FLOAT,
      GL_FALSE,
      sizeof(Vertex),
      (GLvoid *)offsetof(Vertex, m_uv)
    );

    m_vao.Unbind(); // Unbind the VAO
  }

  Mesh::~Mesh() {
    // Do nothing
  }

  void Mesh::Draw(const Shader &shader) const {
    // Draw the mesh using the shader program
  }

}