/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_BUFFER_OBJECT_HPP_
#define _ELGAR_BUFFER_OBJECT_HPP_

// INCLUDES //

#include <GL/glew.h>

namespace elgar {

  /**
   * @brief      The BufferObject class operates as a wrapper for OpenGL buffers
   */
  class BufferObject {
  private:
    GLuint m_id;  // The id of the OpenGL BufferObject

    GLenum m_target;  // The binding point of the BufferObject

  public:
    /**
     * @brief      Constructs a BufferObject
     *
     * @param[in]  target  The binding point for the BufferObject
     */
    BufferObject(const GLenum &target);  
    
    /**
     * @brief      Delete the BufferObject
     */
    virtual ~BufferObject();

    /**
     * @brief      Bind the BufferObject
     */
    void Bind() const;

    /**
     * @brief      Unbind the BufferObject
     */
    void Unbind() const;

    /**
     * @brief      Fill the BufferObject with vertex data
     *
     * @param[in]  data   The data to fill BufferObject with
     * @param[in]  size   The size in bytes of the data
     * @param[in]  usage  Tell OpenGL how to use the data (Ex: GL_STATIC_DRAW, GL_DYNAMIC_DRAW, ...)
     */
    void FillData(const GLvoid *data, const GLsizeiptr &size, const GLenum &usage) const;

    /**
     * @brief      Fill a subset of the BufferObject with vertex data
     *
     * @param[in]  data   The data to fill BufferObject with
     * @param[in]  size   The size in bytes of the data
     * @param[in]  offset The offset in bytes in the BufferObject to start writing
     */
    void FillSubData(const GLvoid *data, const GLsizeiptr &size, const GLintptr &offset) const;

    /**
     * @brief      Map the BufferObject's address space for direct editing
     *
     * @param[in]  access  Tell OpenGL how the BufferObject's data will be accessed
     *
     * @return     Pointer to the data
     */
    GLvoid *Map(const GLenum &access) const;

    /**
     * @brief      Unmap the BufferObject if it is mapped, must be done before drawing
     */
    void Unmap() const;
  };

}

#endif