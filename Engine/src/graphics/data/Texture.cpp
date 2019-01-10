/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/data/Texture.hpp"

namespace elgar {

  // FUNCTIONS //

  Texture::Texture(const Image &image, const TextureType &type, const TextureParams &params) {
    glGenTextures(1, &m_id);  // Generate a new OpenGL texture
    this->Bind(); // Bind the texture

    m_type = type;  // Copy the type

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.min_filter_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.mag_filter_mode);

    GLint mode = GL_RGB;
    if (image.channels == 1) {
      mode = GL_RED;
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Set the pixel storage mode
    }
    else if (image.channels == 4)
      mode = GL_RGBA;

    // Send OpenGL the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, mode, image.width, image.height, 0, mode, GL_UNSIGNED_BYTE, image.data);

    // Generate mipmaps for the texture
    glGenerateMipmap(GL_TEXTURE_2D);

    // Copy the width and height
    m_width = image.width;
    m_height = image.height;

    // Reset pixel storage mode if necessary
    if (image.channels == 1) {
      glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  // Back to default value
    }

    this->Unbind(); // Unbind the texture
  }

  Texture::~Texture() {
    glDeleteTextures(1, &m_id); // Delete the texture
  }

  void Texture::Bind(const GLuint &index) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_id);
  }

  void Texture::Unbind(const GLuint &index) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  bool Texture::operator ==(const Texture &texture) const {
    return m_id == texture.m_id;
  }

  bool Texture::operator !=(const Texture &texture) const {
    return m_id != texture.m_id;
  }

  const GLsizei &Texture::GetWidth() const {
    return m_width;
  }

  const GLsizei &Texture::GetHeight() const {
    return m_height;
  }

  const TextureType &Texture::GetType() const {
    return m_type;
  }

}