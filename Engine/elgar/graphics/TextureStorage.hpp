/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

#ifndef _ELGAR_TEXTURE_STORAGE_HPP_
#define _ELGAR_TEXTURE_STORAGE_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"
#include "elgar/graphics/data/Texture.hpp"

#include <unordered_map>
#include <string>

namespace elgar {

  /**
   * @brief The TextureStorage class handles the caching of textures for reuse later (NOTE: Cached textures will be deleted on shutdown!)
   * 
   */
  class TextureStorage : public Singleton<TextureStorage> {
  friend class Engine;
  private:
    std::unordered_map<std::string, const Texture *> m_textures;    // Set of textures to store

  private:
    /**
     * @brief Construct a new TextureStorage object
     * 
     */
    TextureStorage();

    /**
     * @brief Destroy the TextureStorage object
     * 
     */
    virtual ~TextureStorage();

  public:
    /**
     * @brief Saves a texture to memory under a given name
     * 
     * @param name      The name of the texture to save
     * @param texture   Pointer to the texture
     * @return true     If save was successful
     * @return false    If save failed
     */
    bool Save(const std::string &name, const Texture *texture);

    /**
     * @brief Load a texture from memory
     * 
     * @param name      The name the texture was saved under
     * @return          Const pointer to the texture or nullptr if not found
     */
    const Texture *Load(const std::string &name) const;
  };

}

#endif