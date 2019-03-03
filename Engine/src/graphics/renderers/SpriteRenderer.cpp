/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

// INCLUDES //

#include "elgar/graphics/renderers/SpriteRenderer.hpp"

#include "elgar/core/Macros.hpp"

namespace elgar {

  // LOCAL DATA //

  const std::vector<glm::vec3> default_vertices = {
    {-0.5f, -0.5f, 0.0f},   // Bottom left vertex
    {0.5f, -0.5f, 0.0f},    // Bottom right vertex
    {-0.5f, 0.5f, 0.0f},    // Top left vertex
    {0.5f, 0.5f, 0.0f}      // Top right vertex
  };

  const std::vector<glm::vec2> default_uvs = {
    {0.0f, 0.0f},     // Bottom left vertex
    {1.0f, 0.0f},     // Bottom right vertex
    {0.0f, 1.0f},     // Top left vertex
    {1.0f, 1.0f}      // Top right vertex
  };

  // FUNCTIONS //

  SpriteRenderer::SpriteRenderer() : 
    Singleton<SpriteRenderer>(this), 
    m_vertex_buffer(GL_ARRAY_BUFFER), 
    m_uv_buffer(GL_ARRAY_BUFFER) 
  {
    LOG("Initializing Sprite Renderer...\n");

    m_vao.Bind(); // Bind the VAO for the renderer

    m_vertex_buffer.Bind(); // Bind the vertex buffer
    m_vertex_buffer.FillData(
      &default_vertices[0][0],    // Send the vertices to OpenGL
      sizeof(glm::vec3) * default_vertices.size(),    // Tell OpenGL the number of bytes to allocate
      GL_STATIC_DRAW    // Data will not be modified
    );

    m_uv_buffer.Bind(); // Setup the uv buffer
    m_uv_buffer.FillData(
      NULL,                   // Orphan the buffer for later rendering
      sizeof(glm::vec2) * default_vertices.size(),    // Allocate buffer size
      GL_DYNAMIC_DRAW   // Data will be modified frequently
    );

    // Tell the VAO how the data is formatted

    m_vertex_buffer.Bind(); // Bind vertex buffer
    m_vao.EnableAttribute(0); // Bind attrib 0
    m_vao.AttributePointer(
      0,            // Location 0
      3,            // x, y, z
      GL_FLOAT,     // Data type
      GL_FALSE,     // Do not normalize the data
      0,            // Tightly packed
      (GLvoid *)0   // No stride
    );

    m_uv_buffer.Bind();   // Bind uv buffer
    m_vao.EnableAttribute(1); // Bind attrib 1
    m_vao.AttributePointer(
      1,            // Location 1
      2,            // u, v
      GL_FLOAT,     // Data type
      GL_FALSE,     // Do not normalize the data
      0,            // Tightly packed
      (GLvoid *)0   // No stride
    );

    m_vao.Unbind(); // Unbind the vao

    LOG("Sprite Renderer online...\n");
  }

  SpriteRenderer::~SpriteRenderer() {

    LOG("Sprite Renderer offline...\n");
  }

  void SpriteRenderer::Draw(const Shader &shader, const glm::mat4 &model, const RGBA &color, const Texture *texture) {
    // Draw the Sprite

    shader.Use();   // Use the shader program

    // Check for texture
    if (texture) {
      texture->Bind(0);   // Bind texture to location 0
      shader.SetBool("use_texture", GL_TRUE);   // Tell the shader to sample the texture
    }
    else {
      shader.SetBool("use_texture", GL_FALSE);  // Tell the shader to ignore texture
    }

    shader.SetVec4("color", color.GetData());   // Send color to shader
    shader.SetMat4("model_matrix", model);      // Set the model matrix
    shader.SetBool("use_instancing", GL_FALSE); // We are not instancing

    m_vao.Bind();   // Bind the VAO for rendering

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);    // Draw the sprite

    m_vao.Unbind(); // Unbind the VAO
  }

  void SpriteRenderer::DrawInstanced(
    const Shader &shader, 
    const std::vector<glm::mat4> &models, 
    const RGBA &color, 
    const Texture *texture
  ) {
    // Draw the Sprites

    shader.Use();   // Use the shader program

    // Check for texture
    if (texture) {
      texture->Bind(0);   // Bind the texture to location 0
      shader.SetBool("use_texture", GL_TRUE); // Tell OpenGL to sample the texture
    }
    else {
      shader.SetBool("use_texture", GL_FALSE);
    }

    shader.SetVec4("color", color.GetData());   // Send color to shader
    shader.SetBool("use_instancing", GL_TRUE);  // Enable instancing

    m_vao.Bind(); // Bind the vao to draw with

    // Send model matrices to the vao

    // Create a new buffer for the model data and fill it with the model matrix data
    BufferObject model_buffer(GL_ARRAY_BUFFER);
    model_buffer.Bind();
    model_buffer.FillData(
      &models[0][0][0],
      sizeof(glm::mat4) * models.size(),
      GL_STATIC_DRAW
    );

    // Tell OpenGL how the model matrix data is formatted
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

    // Draw the Sprites
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, models.size());

    m_vao.Unbind(); // Unbind the vao since we are done drawing
  }

}