/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_VERTEX_ARRAY_OBJECT_HPP_
#define _ELGAR_VERTEX_ARRAY_OBJECT_HPP_

// INCLUDES //

#include <GL/glew.h>

namespace elgar {

  /**
   * @brief      A VertexArrayObject is a simple wrapper for implementing OpenGL VAO's
   */
  class VertexArrayObject {
  private:
    GLuint    m_id;  // The id of the vao

  public:
    /**
     * @brief      Create a new VertexArrayObject
     */
    VertexArrayObject();

    /**
     * @brief      Destroys a VertexArrayObject
     */
    virtual ~VertexArrayObject();

    /**
     * @brief      Bind the VertexArrayObject
     */
    void Bind() const;

    /**
     * @brief      Unbind the VertexArrayObject
     */
    void Unbind() const;

    /**
     * @brief      Enable a vertex attribute for the currently bound shader
     *
     * @param[in]  attrib_id  The attribute's id to enable
     */
    void EnableAttribute(const GLuint &attrib_id) const;

    /**
     * @brief      Disable a vertex attribute for the currently bound shader
     *
     * @param[in]  attrib_id  The attribute's id to disable
     */
    void DisableAttribute(const GLuint &attrib_id) const;

    /**
     * @brief      Tell the VAO how to format currently bound buffer's data
     *
     * @param[in]  index       The attribute index in the shader
     * @param[in]  size        The number of items per vertex attribute
     * @param[in]  type        The data type of each item in the vertex attribute
     * @param[in]  normalized  Should OpenGL normalize the data?
     * @param[in]  stride      The number of bytes between instances of the vertex attribute
     * @param[in]  pointer     The offset in bytes from the beginning of the vertex data 
     *                         to the attribute
     */
    void AttributePointer(
      const GLuint &index,
      const GLint &size,
      const GLenum &type,
      const GLboolean &normalized,
      const GLsizei &stride,
      const GLvoid *pointer) const;

    /**
     * @brief Set the divisor for instancing
     * 
     * @param index       The index of the attribute
     * @param divisor     The number of instances to use the attribute
     */
    void AttributeDivisor(const GLuint &index, const GLuint &divisor) const;

  };

}

#endif