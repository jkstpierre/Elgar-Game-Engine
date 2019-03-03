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

    std::unordered_map<std::string, GLint> m_uniform_cache;   // Cache of uniform locations
    std::unordered_map<std::string, GLint> m_attrib_cache;    // Cache of attribute locations

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

    /**
     * @brief Checks uniform cache for the given uniform, updates the cache if necessary
     * 
     * @param name    The name of the uniform in the GLSL source code
     * @return GLint  The location of the uniform, or -1 if not found
     */
    GLint UpdateUniformCache(const std::string &name);

    /**
     * @brief Checks attribute cache for the given attribute, updates the cache if necessary
     * 
     * @param name    The name of the attribute in the GLSL source code
     * @return GLint  The location of the attribute, or -1 if not found
     */
    GLint UpdateAttributeCache(const std::string &name);

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

    /**
     * @brief Enable an attribute in the loaded shader program
     * 
     * @param name The name of the attribute in the GLSL source code
     */
    void EnableAttribute(const std::string &name) const;

    /**
     * @brief Disable an attribute in the loaded shader program
     * 
     * @param name The name of the attribute in the GLSL source code
     */
    void DisableAttribute(const std::string &name) const;

    /**
     * @brief Tell OpenGL how to format the currently bound array buffer's data
     * 
     * @param name          The name of the attribute to associate with the currently bound buffer
     * @param size          The number of elements in the attribute
     * @param type          The data type of the attribute
     * @param normalized    Should GLSL normalize the attribute data
     * @param stride        How many bytes until next occurance of the attribute
     * @param pointer       What is the offset in bytes until the start of the attribute
     */
    void AttributePointer(
      const std::string &name,
      const GLint &size,
      const GLenum &type,
      const GLboolean &normalized,
      const GLsizei &stride,
      const GLvoid *pointer
    ) const;

    /**
     * @brief Set the attribute divisor during instanced rendering
     * 
     * @param name      The name of the attribute to set
     * @param divisor   The divisor to give to the attribute
     */
    void AttributeDivisor(const std::string &name, const GLuint &divisor) const;

  };

}

#endif