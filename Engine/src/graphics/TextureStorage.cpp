/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/TextureStorage.hpp"
#include "elgar/core/Macros.hpp"

namespace elgar {

  // FUNCTIONS //

  TextureStorage::TextureStorage() : Singleton<TextureStorage>(this) {
    LOG("TextureStorage online...\n");
  }

  TextureStorage::~TextureStorage() {
    // Delete all cached textures
    for (auto it = m_textures.begin(); it != m_textures.end(); it++) {
      delete it->second;
    }

    m_textures.clear();

    LOG("TextureStorage offline...\n");
  }

  bool TextureStorage::Save(const std::string &name, const Texture *texture) {
    if (m_textures.find(name) != m_textures.end()) {
      LOG("Error: TextureStorage already contains a texture under name: %s\n", name.c_str());
      return false;
    }

    m_textures.insert(std::pair<std::string, const Texture *>(name, texture));  // Add the texture to the table

    return true;
  }

  const Texture *TextureStorage::Load(const std::string &name) const {
    if (m_textures.find(name) == m_textures.end())
      return nullptr;

    return m_textures.at(name);
  }
}