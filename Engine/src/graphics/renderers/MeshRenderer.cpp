/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

// INCLUDES //

#include "elgar/graphics/renderers/MeshRenderer.hpp"
#include "elgar/core/Macros.hpp"

namespace elgar {

  // FUNCTIONS //

  MeshRenderer::MeshRenderer() : Singleton<MeshRenderer>(this), m_vbo(GL_ARRAY_BUFFER), m_ebo(GL_ELEMENT_ARRAY_BUFFER) {
    // Setup VAO
    m_vao.Bind();

    // Setup vertex buffer
    m_vbo.Bind(); 
    m_vbo.FillData(
      NULL,   // Orphan the buffer
      sizeof(Vertex) * MESH_MAX_VERTEX_COUNT,   // Allocate bytes
      GL_DYNAMIC_DRAW   // Buffer will be modified frequently
    );

    // Setup element buffer
    m_ebo.Bind();
    m_ebo.FillData(
      NULL,   // Orphan the buffer
      sizeof(GLuint) * MESH_MAX_INDEX_COUNT,   // Allocate bytes (TODO: Precisely calculate)
      GL_DYNAMIC_DRAW   // Buffer will be modified frequently
    );

    // Setup vertex attribs
    m_vbo.Bind();
    m_vao.EnableAttribute(0);   // Bind location 0
    m_vao.AttributePointer(
      0,    // Location 0 
      3,    // x, y, z,
      GL_FLOAT,   // Data type
      GL_FALSE,   // Do not normalize the data
      sizeof(Vertex),   // Number of bytes until next attrib
      (GLvoid *)0       // No offset
    );

    m_vao.EnableAttribute(1);   // Bind location 1
    m_vao.AttributePointer(
      1,    // Location 1
      3,    // normal
      GL_FLOAT,   // Data type
      GL_FALSE,   // Do not normalize the data
      sizeof(Vertex),   // Number of bytes until next attrib
      (GLvoid *)offsetof(Vertex, normal)    // Offset to the next normal
    );

    m_vao.EnableAttribute(2);   // Bind location 2
    m_vao.AttributePointer(
      2,        // Location 2
      2,        // u,v
      GL_FLOAT, // Data type
      GL_FALSE,
      sizeof(Vertex),
      (GLvoid *)offsetof(Vertex, uv)
    );

    m_vao.Unbind();   // Unbind the vao

    LOG("MeshRenderer online...\n");
  }

  MeshRenderer::~MeshRenderer() {
    LOG("MeshRenderer offline...\n");
  }

  void MeshRenderer::RegisterMesh(const Mesh &mesh) const {
    m_vao.Bind();   // Bind the vao

    const std::vector<Vertex> &vertices = mesh.GetVertices();
    const std::vector<GLuint> &indices = mesh.GetIndices();

    m_vbo.Bind();   // Bind the vbo
    m_vbo.FillSubData(
      &vertices[0],     // Pointer to the vertex data
      vertices.size() * sizeof(Vertex),   // Number of bytes
      0   // No offset
    );

    m_ebo.Bind();   // Bind the ebo
    m_ebo.FillSubData(
      &indices[0],      // Pointer to the index data
      indices.size() * sizeof(GLuint),    // Number of bytes
      0   // No offset
    );

    m_vao.Unbind();   // Unbind our vao
  }

  void MeshRenderer::Draw(const Mesh &mesh, const Shader &shader, const RGBA &color, const glm::mat4 &model) const {
    shader.Use();   // Enable the shader program

    RegisterMesh(mesh); // Register the mesh for rendering

    // Set shader uniforms
    shader.SetVec4("color", color.GetData());
    shader.SetMat4("model_matrix", model);
    shader.SetBool("use_instancing", GL_FALSE);

    const std::vector<const Texture *> &textures = mesh.GetTextures();

    if (textures.empty())
      shader.SetBool("use_texture", GL_FALSE);
    else {
      shader.SetBool("use_texture", GL_TRUE);

      // Grab reference to the mesh textures
      const std::vector<const Texture *> &textures = mesh.GetTextures();

      // TODO: Bind the textures of the mesh
      for (unsigned int i = 0; i < textures.size(); i++) {
        
      }
    }

    // Draw the mesh
    m_vao.Bind();

    // Draw the mesh
    glDrawElements(GL_TRIANGLES, mesh.GetIndices().size(), GL_UNSIGNED_INT, 0);

    m_vao.Unbind();
  }

  void MeshRenderer::DrawInstanced(const Mesh &mesh, const Shader &shader, const RGBA &color, const std::vector<glm::mat4> &models) const {

  }

}