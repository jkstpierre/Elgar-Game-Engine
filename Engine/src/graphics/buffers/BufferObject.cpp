/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/buffers/BufferObject.hpp"

namespace elgar {

  // FUNCTIONS //

  BufferObject::BufferObject(const GLenum &target) {
    glGenBuffers(1, &m_id);

    m_target = target;
  }

  BufferObject::~BufferObject() {
    glDeleteBuffers(1, &m_id);
  }

  void BufferObject::Bind() const {
    glBindBuffer(m_target, m_id);
  }

  void BufferObject::Unbind() const {
    glBindBuffer(m_target, 0);
  }

  void BufferObject::FillData(
    const GLvoid *data, 
    const GLsizeiptr &size, 
    const GLenum &usage) const {
    glBufferData(m_target, size, data, usage);
  }

  void BufferObject::FillSubData(
    const GLvoid *data, 
    const GLsizeiptr &size, 
    const GLintptr &offset) const {
    glBufferSubData(m_target, offset, size, data);
  }

  GLvoid *BufferObject::Map(const GLenum &access) const {
    return glMapBuffer(m_target, access);
  }

  void BufferObject::Unmap() const {
    glUnmapBuffer(m_target);
  }
}