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

    std::unordered_map<std::string, GLint> m_uniforms;  // Hash table of all uniform locations

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

  public:
    /**
     * @brief      Use the shader program
     */
    void Use() const;

    /**
     * @brief      Set a boolean uniform
     *
     * @param[in]  name   The name of the uniform
     * @param[in]  value  The value
     */
    void SetBool(const std::string &name, GLboolean value) const;

    /**
     * @brief      Sets an integer uniform
     *
     * @param[in]  name   The name of the uniform
     * @param[in]  value  The value
     */
    void SetInt(const std::string &name, GLint value) const;

    /**
     * @brief      Sets an integer array uniform
     *
     * @param[in]  name    The name of the uniform
     * @param[in]  count   The count
     * @param      values  The values
     */
    void SetIntArray(const std::string &name, GLsizei count, GLint *values) const;

    /**
     * @brief      Sets a float uniform
     *
     * @param[in]  name   The name of the uniform
     * @param[in]  value  The value
     */
    void SetFloat(const std::string &name, GLfloat value) const;

    /**
     * @brief      Sets a float array uniform
     *
     * @param[in]  name    The name of the uniform
     * @param[in]  count   The count
     * @param      values  The values
     */
    void SetFloatArray(const std::string &name, GLsizei count, GLfloat *values) const;

    /**
     * @brief      Sets a vector2 uniform
     *
     * @param[in]  name   The name of the uniform
     * @param[in]  value  The value
     */
    void SetVec2(const std::string &name, const glm::vec2 &value) const;

    /**
     * @brief      Sets a vector2 array uniform
     *
     * @param[in]  name    The name of the uniform
     * @param[in]  count   The count
     * @param[in]  values  The values
     */
    void SetVec2Array(const std::string &name, GLsizei count, const GLfloat *values) const;

    /**
     * @brief      Sets a vector3 uniform
     *
     * @param[in]  name   The name of the uniform
     * @param[in]  value  The value
     */
    void SetVec3(const std::string &name, const glm::vec3 &value) const;

    /**
     * @brief      Sets a vector3 array uniform
     *
     * @param[in]  name    The name of the uniform
     * @param[in]  count   The count
     * @param[in]  values  The values
     */
    void SetVec3Array(const std::string &name, GLsizei count, const GLfloat *values) const;

    /**
     * @brief      Sets a vector4 uniform
     *
     * @param[in]  name   The name of the uniform
     * @param[in]  value  The value
     */
    void SetVec4(const std::string &name, const glm::vec4 &value) const;

    /**
     * @brief      Sets a mat2 uniform
     *
     * @param[in]  name  The name of the uniform
     * @param[in]  mat   The matrix
     */
    void SetMat2(const std::string &name, const glm::mat2 &mat) const;

    /**
     * @brief      Sets a mat3 uniform
     *
     * @param[in]  name  The name of the uniform
     * @param[in]  mat   The matrix
     */
    void SetMat3(const std::string &name, const glm::mat3 &mat) const;

    /**
     * @brief      Sets a mat4 uniform
     *
     * @param[in]  name  The name of the uniform
     * @param[in]  mat   The matrix
     */
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;

  };

}

#endif