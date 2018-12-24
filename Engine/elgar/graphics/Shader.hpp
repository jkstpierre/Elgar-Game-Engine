/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_SHADER_HPP_
#define _ELGAR_SHADER_HPP_

// INCLUDES //

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <string>

namespace elgar {

  /**
   * @brief      The Shader class is a wrapper for interacting with OpenGL shader programs
   */
  class Shader {
  friend class ShaderManager;
  private:
    GLuint m_id;  // The shader program id

    std::unordered_map<std::string, GLint> m_uniform_locs;  // Hash table of all uniform locations

  private:
    /**
     * @brief      Constructs a new Shader 
     *
     * @param[in]  vertex_code    The vertex shader code (in GLSL)
     * @param[in]  fragment_code  The fragment shader code (in GLSL)
     * @param[in]  geometry_code  The geometry shader code (in GLSL)
     */
    Shader(const char *vertex_code, const char *fragment_code, const char *geometry_code = NULL);

    /**
     * @brief      Destroys a Shader
     */
    virtual ~Shader();

  private:
    /**
     * @brief      Get the location of a given uniform
     *
     * @param[in]  name  The name of the uniform
     *
     * @return     The uniform location on the graphics card
     */
    GLint GetUniformLocation(const std::string &name);

  public:
    void Use() const;

    void SetBool(const std::string &name, GLboolean value);

    void SetInt(const std::string &name, GLint value);

    void SetIntArray(const std::string &name, GLsizei count, GLint *values);

    void SetFloat(const std::string &name, GLfloat value);

    void SetFloatArray(const std::string &name, GLsizei count, GLfloat *values);

    void SetVec2(const std::string &name, const glm::vec2 &value);

    void SetVec2Array(const std::string &name, GLsizei count, const GLfloat *values);

    void SetVec3(const std::string &name, const glm::vec3 &value);

    void SetVec3Array(const std::string &name, GLsizei count, const GLfloat *values);

    void SetVec4(const std::string &name, const glm::vec4 &value);

    void SetMat2(const std::string &name, const glm::mat2 &mat);

    void SetMat3(const std::string &name, const glm::mat3 &mat);

    void SetMat4(const std::string &name, const glm::mat4 &mat);
  };

}

#endif