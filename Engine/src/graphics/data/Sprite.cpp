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
    shader.SetBool("use_instancing", GL_FALSE); // We are not instance rendering

    // Bind the vao for rendering
    m_vao.Bind();

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

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  // Draw the sprite

    // Unbind the vao
    m_vao.Unbind();
  }

  void Sprite::DrawInstanced(
    const Shader &shader, 
    const RGBA &color,
    const std::vector<glm::mat4> &model_matrices
  ) const 
  {
    shader.Use();   // Use our shader program

    // Check for texture
    if (m_texture) {
      m_texture->Bind(0);   // Bind the texture to id 0
      shader.SetBool("use_texture", GL_TRUE); // Tell the shader to enable texture sampling
    }
    else {
      shader.SetBool("use_texture", GL_FALSE);  // Disable texture sampling
    }

    // Set the color
    shader.SetVec4("color", color.GetData()); // Set the color for the sprite

    // Enable instancing on the shader
    shader.SetBool("use_instancing", GL_TRUE);

    // Bind the vao to send data to
    m_vao.Bind();

    BufferObject model_buffer(GL_ARRAY_BUFFER); // Create a buffer object for the model matrices
    model_buffer.Bind();  // Bind the buffer
    model_buffer.FillData(
      &model_matrices[0][0][0],   // Model matrix data
      sizeof(glm::mat4) * model_matrices.size(),    // Size in bytes of the buffer
      GL_STATIC_DRAW              // Data will not change
    );

    m_vao.EnableAttribute(2); // Bind attrib 2 for 1st row of matrix
    m_vao.AttributePointer(
      2,  // Location 2
      4,  // 1 row of matrix
      GL_FLOAT, // Data type
      GL_FALSE, // Do not normalize
      sizeof(glm::mat4),  // Number of bytes until next equivalent attribute
      (GLvoid *)0 // No offset
    );

    m_vao.EnableAttribute(3);
    m_vao.AttributePointer(
      3,  // Location 3
      4,  // 2nd row of matrix
      GL_FLOAT,
      GL_FALSE,
      sizeof(glm::mat4),
      (GLvoid *)sizeof(glm::vec4)
    );

    m_vao.EnableAttribute(4);
    m_vao.AttributePointer(
      4,  // Location 4
      4,  // 3rd row of matrix
      GL_FLOAT,
      GL_FALSE,
      sizeof(glm::mat4),
      (GLvoid *)(sizeof(glm::vec4) * 2)
    );

    m_vao.EnableAttribute(5);
    m_vao.AttributePointer(
      5,  // Location 5
      4,  // 4th row of matrix
      GL_FLOAT,
      GL_FALSE,
      sizeof(glm::mat4),
      (GLvoid *)(sizeof(glm::vec4) * 3)
    );

    // Tell OpenGL to use 1 matrix per instance
    m_vao.AttributeDivisor(2, 1);
    m_vao.AttributeDivisor(3, 1);
    m_vao.AttributeDivisor(4, 1);
    m_vao.AttributeDivisor(5, 1);

    // Draw the sprites
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, model_matrices.size());

    m_vao.Unbind(); // Unbind the vao
  }

}