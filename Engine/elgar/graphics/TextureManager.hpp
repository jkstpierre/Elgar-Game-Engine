/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_TEXTURE_MANAGER_HPP_
#define _ELGAR_TEXTURE_MANAGER_HPP_

// INCLUDES //

#include <unordered_map>
#include <string>

#include "elgar/graphics/Texture.hpp"
#include "elgar/core/Singleton.hpp"

namespace elgar {

  /**
   * @brief      The TextureManager class handles the creation, loading, 
   *             and storage of OpenGL textures. (Is a Singleton class)
   */
  class TextureManager : public Singleton<TextureManager> {
  friend class Engine;
  private:
    std::unordered_map<std::string, Texture *> m_textures;  // The table of textures in memory

  private:
    /**
     * @brief      Constructs a TextureManager object
     */
    TextureManager();

    /**
     * @brief      Destroys a TextureManager object
     */
    virtual ~TextureManager();

  public:
    /**
     * @brief      Loads a texture from disk.
     *
     * @param[in]  filepath  The filepath to the desired texture
     * @param[in]  name      The name to store the texture as (defaults to filepath)
     *
     * @return     true if texture successfully loaded into memory, false otherwise
     */
    bool LoadTextureFromDisk(const std::string &filepath, const std::string &name = "");

    /**
     * @brief      Retrieves a loaded texture by name
     *
     * @param[in]  texture_name  The texture name
     *
     * @return     Pointer to the texture requested or nullptr if not found.
     */
    const Texture *GetTexture(const std::string &texture_name) const;

  };

}

#endif