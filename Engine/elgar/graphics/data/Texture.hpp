/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_TEXTURE_HPP_
#define _ELGAR_TEXTURE_HPP_

// INCLUDES //

#include <GL/glew.h>

#include "elgar/graphics/data/Image.hpp"

namespace elgar {
  /**
   * @brief      The Texture class is a simple wrapper around OpenGL textures
   */
  class Texture {
  private:
    GLuint  m_id;       // The id of the OpenGL texture
    GLsizei m_width;    // The width in pixels
    GLsizei m_height;   // The height in pixels

  public:
    /**
     * @brief      Builds a new Texture from Image data
     *
     * @param      Reference to the Image data to build texture from
     */
    Texture(const Image &image);

    /**
     * @brief      Destroys a Texture
     */
    virtual ~Texture();

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

    /**
     * @brief Check if two Textures are equal (i.e. have same id)
     * 
     * @param texture   The texture to compare to
     * @return true     If textures are equivalent
     * @return false    If textures are not equivalent
     */
    bool operator ==(const Texture &texture) const;

    /**
     * @brief Check if two Textures are not equal (i.e. have different ids)
     * 
     * @param texture   The texture to compare to
     * @return true     If textures are not equal
     * @return false    If textures are equal
     */
    bool operator !=(const Texture &texture) const;

    /**
     * @brief Get the width of the Texture
     * 
     * @return Reference to the Texture width
     */
    const GLsizei &GetWidth() const;

    /**
     * @brief Get the height of the Texture
     * 
     * @return Reference to the Texture height
     */
    const GLsizei &GetHeight() const;
  };
}

#endif