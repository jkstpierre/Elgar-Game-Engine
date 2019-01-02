/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/TextureManager.hpp"
#include "elgar/core/Macros.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "elgar/graphics/aux/stb_image.h"

namespace elgar {

  // FUNCTIONS //

  TextureManager::TextureManager() : Singleton<TextureManager>(this) {
    LOG("TextureManager online...\n");
  }

  TextureManager::~TextureManager() {
    for(auto it = m_textures.begin(); it != m_textures.end(); it++) {
      Texture *texture = it->second;

      delete texture;
    }

    m_textures.clear();

    LOG("TextureManager offline...\n");
  }

  bool TextureManager::BuildTexture(const std::string &filepath, const std::string &name) {
    // Check for naming collision
    if (name.empty() && m_textures.find(filepath) != m_textures.end()) {
      LOG("ERROR: Texture already loaded in memory under the name: %s\n", filepath.c_str());
      return false;
    }
    else if (!name.empty() && m_textures.find(name) != m_textures.end()) {
      LOG("ERROR: Texture already loaded in memory under the name: %s\n", name.c_str());
      return false;
    }

    int width, height, channels;

    stbi_set_flip_vertically_on_load(true); // Flip image vertically
    unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if (!data) {
      LOG("ERROR: Failed to load texture %s from disk!\n", filepath.c_str());
      return false;
    }

    if (channels != 3 && channels != 4) {
      LOG("ERROR: Unsupported image format!\n");
      return false;
    }

    // Set the pixel format
    GLint mode = GL_RGB;
    if (channels == 4)
      mode = GL_RGBA;

    // Create a new texture
    Texture *new_texture = new Texture(data, width, height, mode);

    // Generate texture name
    std::string texture_name = name;

    // Use default name
    if (name.empty())
      texture_name = filepath;

    m_textures[texture_name] = new_texture; // Store the texture

    stbi_image_free(data);  // Free the image data now the OpenGL has it

    return true;
  }

  const Texture *TextureManager::GetTexture(const std::string &texture_name) const {
    if (m_textures.find(texture_name) != m_textures.end())
      return m_textures.at(texture_name);

    return nullptr;
  }

  void TextureManager::DestroyTexture(const std::string &name) {
    if (m_textures.find(name) != m_textures.end()) {
      delete m_textures.at(name);
      m_textures.erase(name);
    }
  }

}