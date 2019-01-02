/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

// INCLUDES //

#include "elgar/graphics/buffers/FrameBufferObject.hpp"

namespace elgar {

  // FUNCTIONS //

  FrameBufferObject::FrameBufferObject(const GLenum &target) {
    glGenFramebuffers(1, &m_id);  // Generate the fbo

    m_target = target;
  }

  FrameBufferObject::~FrameBufferObject() {
    glDeleteFramebuffers(1, &m_id);
  }

  void FrameBufferObject::Bind() const {
    glBindFramebuffer(m_target, m_id);
  }

  void FrameBufferObject::Unbind() const {
    glBindFramebuffer(m_target, 0);
  }

}