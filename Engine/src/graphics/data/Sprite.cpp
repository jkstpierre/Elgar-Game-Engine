/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/data/Sprite.hpp"

namespace elgar {

  // STATIC FIELDS //

  const std::vector<glm::vec3> Sprite::m_default_vertices = {
    {-0.5f, -0.5f, 0.0f},   // Bottom left vertex
    {0.5f, -0.5f, 0.0f},    // Bottom right vertex
    {-0.5f, 0.5f, 0.0f},    // Top left vertex
    {0.5f, 0.5f, 0.0f}      // Top right vertex
  };

  const std::vector<glm::vec2> Sprite::m_default_uvs = {
    {0.0f, 0.0f},           // Bottom left vertex
    {1.0f, 0.0f},           // Bottom right vertex
    {0.0f, 1.0f},           // Top left vertex
    {1.0f, 1.0f}            // Top right vertex
  };

  // FUNCTIONS //

  Sprite::Sprite(const Texture *texture) {
    SetTexture(texture);  // Set the texture

    // Setup sprite here //
    m_vao.Bind(); // Bind the vao

    // Send vertex data to OpenGL
    m_vertex_buffer.Bind(); // Bind the vbo
    m_vertex_buffer.FillData(
      &m_default_vertices[0][0],  // The vertex data 
      sizeof(glm::vec3) * m_default_vertices.size(),    // Number of bytes
      GL_STATIC_DRAW    // Buffer will never be modified
    );

    // Send uv data to OpenGL
    m_uv_buffer.Bind();   // Bind the uv buffer
    m_uv_buffer.FillData(
      &m_default_uvs[0][0], // The uv data
      sizeof(glm::vec2) * m_default_uvs.size(),   // Number of bytes
      GL_STATIC_DRAW    // Buffer will never be modified
    );

    m_vertex_buffer.Bind(); // Bind the vbo
    m_vao.EnableAttribute(0); // Bind attrib 0
    m_vao.AttributePointer(
      0,    // Attrib 0
      3,    // x, y, z
      GL_FLOAT,   // Data type
      GL_FALSE,   // Do not normalize data
      0,          // Tightly packed data
      (GLvoid *)0 // No offset
    );

    m_uv_buffer.Bind(); // Bind the uv buffer
    m_vao.EnableAttribute(1); // Bind attrib 1
    m_vao.AttributePointer(
      1,        // Attrib 1
      2,        // u, v
      GL_FLOAT, // Data type
      GL_FALSE, // Do not normalize data
      0,        // Tightly packed data
      (GLvoid *)0 // No offset
    );

    m_vao.Unbind(); // Unbind the vao
  }

  Sprite::~Sprite() {
    // Do nothing
  }

  void Sprite::SetTexture(const Texture *texture) {
    m_texture = texture;
  }

  const Texture *Sprite::GetTexture() const {
    return m_texture;
  }

  const std::vector<glm::vec3> &Sprite::GetDefaultVertices() {
    return m_default_vertices;
  }

  const std::vector<glm::vec2> &Sprite::GetDefaultTexCoords() {
    return m_default_uvs;
  }

  void Sprite::Draw(
    const Shader &shader, 
    const RGBA &color, 
    const glm::mat4 &model_matrix) const 
  {
    shader.Use();   // Use the shader program

    // Check for texture
    if (m_texture) {
      m_texture->Bind(0);   // Bind the texture to id 0
      shader.SetBool("use_texture", GL_TRUE); // Tell the shader to enable texture sampling
    }
    else {
      shader.SetBool("use_texture", GL_FALSE);  // Disable texture sampling
    }

    shader.SetVec4("color", color.GetData()); // Set the color for the sprite
    shader.SetMat4("model_matrix", model_matrix); // Set the model matrix for the sprite
    
    // Bind the vao for rendering
    m_vao.Bind();

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  // Draw the sprite

    // Unbind the vao
    m_vao.Unbind();
  }

  void Sprite::DrawInstanced(
    const Shader &shader, 
    const std::vector<const glm::mat4> &model_matrices
  ) const 
  {

  }

}