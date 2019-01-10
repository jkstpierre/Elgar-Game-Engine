/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_SHADER_MANAGER_HPP_
#define _ELGAR_SHADER_MANAGER_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"
#include "elgar/graphics/Shader.hpp"

// DEFINES //

#define SHADER_BASIC_PROGRAM    "PROGRAM_0"   // Name of the basic shader program
#define SHADER_TEXT_PROGRAM     "PROGRAM_1"   // Name of the text shader program
#define SHADER_SCENE_PROGRAM    "PROGRAM_2"   // Name of the scene shader program

namespace elgar {

  /**
   * @brief      The ShaderManager class handles the loading and storage of Shader instances
   *             (Is a Singleton class)
   */
  class ShaderManager : public Singleton<ShaderManager> {
  friend class Engine;
  private:
    std::unordered_map<std::string, Shader *> m_shaders;  // Table of Shaders

  private:
    /**
     * @brief     Constructs a new ShaderManager instance
     */
    ShaderManager();

    /**
     * @brief      Destroys the ShaderManager instance
     */
    virtual ~ShaderManager();

  private:
    /**
     * @brief      Builds the embedded shader programs Elgar ships with
     */
    void BuildDefaultShaders();

  public:
    /**
     * @brief      Creates a new Shader program
     *
     * @param[in]  name           The name of the shader program
     * @param[in]  vertex_path    The vertex shader path
     * @param[in]  fragment_path  The fragment shader path
     * @param[in]  geometry_path  The geometry shader path (optional)
     *
     * @return     True if shader created successfully, false otherwise
     */
    bool CreateShader(
      const std::string &name,
      const std::string &vertex_path, 
      const std::string &fragment_path,
      const std::string &geometry_path = "");

    /**
     * @brief      Destroys a Shader and frees all resources it held
     *
     * @param[in]  name  The name of the shader
     */
    void DestroyShader(const std::string &name);

    /**
     * @brief      Gets a created Shader program
     *
     * @param[in]  name  The name of the Shader
     *
     * @return     Handle to the Shader or nullptr if not created
     */
    const Shader *GetShader(const std::string &name) const;
  };

}

#endif