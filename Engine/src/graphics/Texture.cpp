/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/Texture.hpp"

namespace elgar {

  // FUNCTIONS //

  Texture::Texture(GLubyte *data, const GLsizei &width, const GLsizei &height, const GLint &mode) {
    glGenTextures(1, &m_id);  // Generate a new OpenGL texture
    this->Bind(); // Bind the texture

    // Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Send OpenGL the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);

    // Create Mipmap for the texture
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  Texture::~Texture() {
    glDeleteTextures(1, &m_id); // Delete the texture
  }

  void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);
  }

  void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}