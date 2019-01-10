/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

/**
 * @file TextRenderer.cpp
 * @author your name (you@domain.com)
 * @brief The TextRenderer class handles the compilation and rendering of ASCII text using true type fonts
 * @version 0.1
 * @date 2019-01-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

// INCLUDES //

#include "elgar/graphics/renderers/TextRenderer.hpp"
#include "elgar/core/Macros.hpp"
#include "elgar/core/Exception.hpp"

// DEFINES //

#define ASCII_VERTEX_COUNT    4

namespace elgar {

  // LOCAL DATA //

  const glm::vec2 default_uvs[ASCII_VERTEX_COUNT] = {
    {0.0f, 1.0f},   // Top left
    {1.0f, 1.0f},   // Top right
    {0.0f, 0.0f},   // Bottom left
    {1.0f, 0.0f}    // Bottom right
  };

  // FUNCTIONS //

  TextRenderer::TextRenderer() : Singleton<TextRenderer>(this), m_vertex_buffer(GL_ARRAY_BUFFER), m_uv_buffer(GL_ARRAY_BUFFER) {
    if (FT_Init_FreeType(&m_context) != 0) {
      throw Exception("ERROR: Failed to initialize FreeType library!");
    }

    // Setup vao and vbo
    m_vao.Bind();
    m_vertex_buffer.Bind();
    m_vertex_buffer.FillData(
      NULL,       // Orphan the vbo
      sizeof(glm::vec3) * ASCII_VERTEX_COUNT,   // Size to expect in bytes
      GL_DYNAMIC_DRAW   // Buffer will be updated frequently
    );

    // Setup texture coordinates buffer
    m_uv_buffer.Bind();
    m_uv_buffer.FillData(
      default_uvs,    // Send OpenGL the uv data
      sizeof(glm::vec2) * ASCII_VERTEX_COUNT,   // Size in bytes
      GL_STATIC_DRAW    // Buffer will never be modified
    );

    // Configure attributes
    m_vertex_buffer.Bind(); // Bind vbo
    m_vao.EnableAttribute(0); // Bind to location 0
    m_vao.AttributePointer(
      0,    // Location 0
      3,    // x, y, z
      GL_FLOAT,   // Data type
      GL_FALSE,   // Do not normalize
      0,    // Data is tightly packed
      (GLvoid *)0   // No offset
    );

    m_uv_buffer.Bind(); // Bind the uv buffer
    m_vao.EnableAttribute(1); // Bind to location 1
    m_vao.AttributePointer(
      1,    // Location 1
      2,    // u, v
      GL_FLOAT,   // Data type
      GL_FALSE,   // Do not normalize
      0,    // Data is tightly packed
      (GLvoid *)0 // No offset
    );

    m_uv_buffer.Unbind(); // Unbind the uv buffer
    m_vao.Unbind(); // Unbind the vao

    LOG("TextRenderer online...\n");
  }

  TextRenderer::~TextRenderer() {
    UnbindFont();   // Unbind the currently loaded font

    FT_Done_FreeType(m_context);    // Destroy FreeType
    LOG("TextRenderer offline...\n");
  }

  GLboolean TextRenderer::BindFont(const std::string &path, const GLuint &size) {
    if (IsBound()) {
      LOG("Error: Cannot bind new TTF while one is already bound! Make sure to unbind first!\n");
      return GL_FALSE;
    }

    FT_Face font;   // The font to open

    // Load the font
    if (FT_New_Face(m_context, path.c_str(), 0, &font) != 0) {
      LOG("Error: Failed to load font %s! Make sure path is correct...\n", path.c_str());
      return GL_FALSE;
    }

    // Set font size
    FT_Set_Pixel_Sizes(font, 0, size);

    // Build the alphabet

    // Iterate through each character
    for (GLubyte c = 0; c < 128; c++) {
      if (FT_Load_Char(font, c, FT_LOAD_RENDER) != 0) {
        LOG("ERROR: Failed to load %c from %s!\n", c, path.c_str());
        continue;
      }

      // Build an image for the character
      Image char_img;
      char_img.channels = 1;
      char_img.width    = font->glyph->bitmap.width;
      char_img.height   = font->glyph->bitmap.rows;
      char_img.data     = font->glyph->bitmap.buffer;

      // Texture params
      TextureParams tex_params;
      tex_params.wrap_mode = GL_CLAMP_TO_EDGE;
      tex_params.min_filter_mode = GL_LINEAR;
      tex_params.mag_filter_mode = GL_LINEAR;

      // Create a new texture
      const Texture *tex = new Texture(char_img, TEXTURE_DIFFUSE, tex_params);

      // Create an ASCII character to store relevant data
      ASCII character;
      character.texture = tex;  // Copy pointer to texture
      character.size = glm::ivec2(char_img.width, char_img.height);   // Set the size of the character
      character.bearing = glm::ivec2(font->glyph->bitmap_left, font->glyph->bitmap_top);  // Set the bearing
      character.advance = font->glyph->advance.x;   // Set the advance

      // Add the characters to the table
      m_ascii_table.insert(std::pair<GLchar, ASCII>(c, character));
    }

    FT_Done_Face(font); // Destroy the font since we no longer need it

    return GL_TRUE;
  }

  void TextRenderer::UnbindFont() {
    // Delete all the textures created by OpenGL
    for (auto it = m_ascii_table.begin(); it != m_ascii_table.end(); it++) {
      ASCII &c = it->second;
      delete c.texture; // Delete the OpenGL texture
    }

    m_ascii_table.clear();
  }

  GLboolean TextRenderer::IsBound() const {
    return !m_ascii_table.empty();
  }

  GLsizei TextRenderer::GetAlphabetSize() const {
    return m_ascii_table.size();
  }

  void TextRenderer::Draw(
      const Shader &shader,
      const std::string &text,
      const RGBA &color,
      const glm::mat4 &model,
      const GLfloat &scale
  ) const 
  {
    shader.Use(); // Use the shader program

    shader.SetBool("use_texture", GL_TRUE);     // We are going to be sampling
    shader.SetBool("use_instancing", GL_FALSE); // We are using separate draw calls

    shader.SetVec4("color", color.GetData());   // Set the text color
    shader.SetMat4("model_matrix", model);      // Set the model matrix

    // Offset for representing the cursor
    GLfloat x_offset = 0.0f;

    // Bind the vao for drawing
    m_vao.Bind();

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw each character
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
      GLchar index = *c;

      // Dont bother rendering if not in table
      if (m_ascii_table.find(index) == m_ascii_table.end())
        continue;

      const ASCII &character = m_ascii_table.at(index);

      GLfloat xpos = x_offset + character.bearing.x * scale;
      GLfloat ypos = -1 * (character.size.y - character.bearing.y) * scale;

      // Compute dimensions
      GLfloat width = character.size.x * scale;
      GLfloat height = character.size.y * scale;

      // Build the vertices
      const glm::vec3 vertices[ASCII_VERTEX_COUNT] = {
        {xpos, ypos, 0.0f},     // Bottom left
        {xpos + width, ypos, 0.0f},    // Bottom right
        {xpos, ypos + height, 0.0f},   // Top left
        {xpos + width, ypos + height, 0.0f}   // Top right
      };

      // Bind the character texture
      character.texture->Bind();

      // Send the vertex buffer the vertex data
      m_vertex_buffer.Bind();
      m_vertex_buffer.FillSubData(
        vertices, // The vertex data
        sizeof(glm::vec3) * ASCII_VERTEX_COUNT, // The size in bytes
        0         // No offset
      );
      m_vertex_buffer.Unbind(); // Unbind vbo

      // Draw the character
      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      // Advance the cursor
      x_offset += (character.advance >> 6) * scale;
    }

    // Disable alpha blending
    glDisable(GL_BLEND);

    // Unbind the vao
    m_vao.Unbind();
  }

}