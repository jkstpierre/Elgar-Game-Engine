/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_TEXTURE_HPP_
#define _ELGAR_TEXTURE_HPP_

// INCLUDES //

#include <GL/glew.h>

namespace elgar {
  /**
   * @brief      The Texture class is a simple wrapper around OpenGL textures
   */
  class Texture {
  friend class TextureManager;
  private:
    GLuint m_id;  // The id of the OpenGL texture

  private:
    /**
     * @brief      Builds a new Texture
     *
     * @param      data    The pixel data for the texture
     * @param[in]  width   The width (in pixels)
     * @param[in]  height  The height (in pixels)
     * @param[in]  mode    The mode  (the format)
     */
    Texture(GLubyte *data, const GLsizei &width, const GLsizei &height, const GLint &mode);

    /**
     * @brief      Destroys a Texture
     */
    virtual ~Texture();

  public:
    /**
     * @brief Bind the texture to an index for rendering
     * 
     * @param index The index to bind to (default is 0)
     */
    void Bind(const GLuint &index = 0) const;

    /**
     * @brief Unbind the texture from an index for rendering
     * 
     * @param index The index to unbind (default is 0)
     */
    void Unbind(const GLuint &index = 0) const;
  };
}

#endif