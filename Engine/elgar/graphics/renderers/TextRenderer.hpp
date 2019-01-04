/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

/**
 * @file TextRenderer.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _ELGAR_TEXT_RENDERER_HPP_
#define _ELGAR_TEXT_RENDERER_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"
#include "elgar/graphics/data/ASCII.hpp"
#include "elgar/graphics/data/RGBA.hpp"

#include "elgar/graphics/buffers/VertexArrayObject.hpp"
#include "elgar/graphics/buffers/BufferObject.hpp"
#include "elgar/graphics/Shader.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>

namespace elgar {

  /**
   * @brief The TextRenderer class handles the compilation and rendering of ASCII text using true type fonts
   * 
   */
  class TextRenderer : public Singleton<TextRenderer> {
  friend class Engine;
  private:
    FT_Library  m_context;    // FreeType library context
    std::map<GLchar, ASCII> m_ascii_table;    // Hash table of characters for performance

    VertexArrayObject m_vao;            // VAO for the TextRenderer
    BufferObject      m_vertex_buffer;  // VBO for the TextRenderer
    BufferObject      m_uv_buffer;      // UV Buffer for the TextRenderer

  private:
    /**
     * @brief Construct a new TextRenderer object
     * 
     */
    TextRenderer();

    /**
     * @brief Destroy the TextRenderer object
     * 
     */
    virtual ~TextRenderer();

    /**
     * @brief Cleanup the ASCII table freeing all resources (MUST BE DONE BEFORE A NEW BINDING)
     * 
     */
    void CleanTable();

  public:
    /**
     * @brief Bind a font to render with at a given size
     * 
     * @param path        The path to the ttf file
     * @param size        The size of the font
     * @return GLboolean  True if bind successful, false otherwise
     */
    GLboolean BindFont(const std::string &path, const GLuint &size);

    /**
     * @brief Unbinds a font, freeing all ascii textures from memory (MUST BE DONE BEFORE A NEW BINDING)
     * 
     */
    void UnbindFont();

    /**
     * @brief Checks if an ASCII alphabet is bound
     * 
     * @return True if a TTF is bound, false otherwise
     */
    GLboolean IsBound() const;

    /**
     * @brief Get the size of the Alphabet
     * 
     * @return Number of chars loaded in memory
     */
    GLsizei GetAlphabetSize() const;

    /**
     * @brief Draw a string of text to the screen
     * 
     * @param shader    The shader to use
     * @param text      The text to draw
     * @param color     The color of the text 
     * @param model     The model matrix for the textbox
     * @param scale     The space between letters (defaults to 1.0f)
     */
    void Draw(
      const Shader &shader,
      const std::string &text,
      const RGBA &color,
      const glm::mat4 &model,
      const GLfloat &scale = 1.0f
    ) const;

  };

}

#endif