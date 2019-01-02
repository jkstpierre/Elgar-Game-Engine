/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/buffers/VertexArrayObject.hpp"

namespace elgar {

  // FUNCTIONS //

  VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &m_id);
  }

  VertexArrayObject::~VertexArrayObject() {
    glDeleteVertexArrays(1, &m_id);
  }

  void VertexArrayObject::Bind() const {
    glBindVertexArray(m_id);
  }

  void VertexArrayObject::Unbind() const {
    glBindVertexArray(0);
  }

  void VertexArrayObject::EnableAttribute(const GLuint &attrib_id) const {
    glEnableVertexAttribArray(attrib_id);
  }

  void VertexArrayObject::DisableAttribute(const GLuint &attrib_id) const {
    glDisableVertexAttribArray(attrib_id);
  }

  void VertexArrayObject::AttributePointer(
    const GLuint &index,
    const GLint &size,
    const GLenum &type,
    const GLboolean &normalized,
    const GLsizei &stride,
    const GLvoid *pointer) const {
    glVertexAttribPointer(
      index,
      size,
      type,
      normalized,
      stride,
      pointer
    );
  }

  void VertexArrayObject::AttributeDivisor(const GLuint &index, const GLuint &divisor) const {
    glVertexAttribDivisor(index, divisor);
  }

}