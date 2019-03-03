/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/Shader.hpp"
#include "elgar/core/Exception.hpp"
#include "elgar/core/Macros.hpp"

namespace elgar {

  // FUNCTIONS //

  Shader::Shader(const char *vertex_code, const char *fragment_code, const char *geometry_code) {
    // Temporary shader program id's
    GLuint vertex_program, fragment_program, geometry_program;
    GLint success;
    GLchar info_log[1024];  // Give 1 KB for error logs

    // Create vertex shader program
    vertex_program = glCreateShader(GL_VERTEX_SHADER);

    // Send source to the vertex program
    glShaderSource(vertex_program, 1, &vertex_code, NULL);
    
    // Compile the vertex shader
    glCompileShader(vertex_program);

    // Check for compilation errors
    glGetShaderiv(vertex_program, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vertex_program, 1024, NULL, info_log);
      throw Exception("ERROR: Failed to compile vertex shader!\n" + std::string(info_log));
    }

    // Create the fragment shader program
    fragment_program = glCreateShader(GL_FRAGMENT_SHADER);

    // Send source to the fragment program
    glShaderSource(fragment_program, 1, &fragment_code, NULL);
    
    // Compile the fragment shader
    glCompileShader(fragment_program);

    // Check for compilation errors
    glGetShaderiv(fragment_program, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fragment_program, 1024, NULL, info_log);
      throw Exception("ERROR: Failed to compile fragment shader!\n" + std::string(info_log));
    }

    // If a geometry shader has been provided
    if (geometry_code) {
      // Create the geometry shader program
      geometry_program = glCreateShader(GL_GEOMETRY_SHADER);

      // Send source to the geometry program
      glShaderSource(geometry_program, 1, &geometry_code, NULL);

      // Compile the geometry shader
      glCompileShader(geometry_program);

      // Check for compilation errors
      glGetShaderiv(geometry_program, GL_COMPILE_STATUS, &success);
      if (!success) {
        glGetShaderInfoLog(geometry_program, 1024, NULL, info_log);
        throw Exception("ERROR: Failed to compile geometry shader!\n" + std::string(info_log));
      }
    }

    // Create the shader program
    m_id = glCreateProgram();
      
    // Attach the vertex shader
    glAttachShader(m_id, vertex_program);

    // Attach the geometry shader (if applicable)
    if (geometry_code)
      glAttachShader(m_id, geometry_program);

    // Attach the fragment shader
    glAttachShader(m_id, fragment_program);

    // Link the programs
    glLinkProgram(m_id);

    // Check for linker errors
    glGetShaderiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(m_id, 1024, NULL, info_log);
      throw Exception("ERROR: Failed to link shader program!\n" + std::string(info_log));
    }

    // Delete obsolete shaders
    glDeleteShader(vertex_program);

    if (geometry_code)
      glDeleteShader(geometry_program);

    glDeleteShader(fragment_program);

    LOG("Shader compiled and linked successfully!\n");
    glGetError(); // Clear error buffer
  }

  Shader::~Shader() {
    glDeleteProgram(m_id);
    LOG("Shader destroyed...\n");
  }

  GLint Shader::UpdateUniformCache(const std::string &name) {
    if (m_uniform_cache.find(name) != m_uniform_cache.end())
      return m_uniform_cache.at(name);

    GLint loc = glGetUniformLocation(m_id, name.c_str());

    if (loc == -1)
      return -1;

    m_uniform_cache.insert(std::pair<std::string, GLint>(name, loc));

    return loc;
  }

  GLint Shader::UpdateAttributeCache(const std::string &name) {
    if (m_attrib_cache.find(name) != m_attrib_cache.end())
      return m_attrib_cache.at(name);

    GLint loc = glGetAttribLocation(m_id, name.c_str());

    if (loc == -1)
      return -1;
    
    m_attrib_cache.insert(std::pair<std::string, GLint>(name, loc));

    return loc;
  }

  void Shader::Use() const {
    glUseProgram(m_id);
  }

  void Shader::SetBool(const std::string &name, GLboolean value) const {
      glUniform1i(glGetUniformLocation(m_id, name.c_str()), (GLint)value);
  }

  void Shader::SetInt(const std::string &name, GLint value) const {
      glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
  }

  void Shader::SetIntArray(const std::string &name, GLsizei count, GLint *values) const {
    if (count > 0)
      glUniform1iv(glGetUniformLocation(m_id, name.c_str()), count, values);
  }

  void Shader::SetFloat(const std::string &name, GLfloat value) const {
      glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
  }

  void Shader::SetFloatArray(const std::string &name, GLsizei count, GLfloat *values) const {
    if (count > 0)
      glUniform1fv(glGetUniformLocation(m_id, name.c_str()), count, values);
  }

  void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const {
      glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
  }

  void Shader::SetVec2Array(const std::string &name, GLsizei count, const GLfloat *values) const {
    if (count > 0)
      glUniform2fv(glGetUniformLocation(m_id, name.c_str()), count, values);
  }

  void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const {
      glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
  }

  void Shader::SetVec3Array(const std::string &name, GLsizei count, const GLfloat *values) const {
    if (count > 0)
      glUniform3fv(glGetUniformLocation(m_id, name.c_str()), count, values);
  }

  void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const {
      glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
  }

  void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const {
      glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const {
      glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const {
      glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  void Shader::EnableAttribute(const std::string &name) const {
    glEnableVertexAttribArray(glGetAttribLocation(m_id, name.c_str()));
  }

  void Shader::DisableAttribute(const std::string &name) const {
    glDisableVertexAttribArray(glGetAttribLocation(m_id, name.c_str()));
  }

  void Shader::AttributePointer(
    const std::string &name,
    const GLint &size,
    const GLenum &type,
    const GLboolean &normalized,
    const GLsizei &stride,
    const GLvoid *pointer
  ) const {
    const GLint location = glGetAttribLocation(m_id, name.c_str());   // Get the location of the attribute

    if (location >= 0) {
      glVertexAttribPointer(
        location,
        size,
        type,
        normalized,
        stride,
        pointer
      );
    }
  }

  void Shader::AttributeDivisor(const std::string &name, const GLuint &divisor) const {
    glVertexAttribDivisor(glGetAttribLocation(m_id, name.c_str()), divisor);
  }

}