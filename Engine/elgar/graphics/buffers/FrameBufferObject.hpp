/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

#ifndef _ELGAR_FRAME_BUFFER_OBJECT_HPP_
#define _ELGAR_FRAME_BUFFER_OBJECT_HPP_

// INCLUDES //

#include <GL/glew.h>

namespace elgar {

  /**
   * @brief A FrameBufferObject allows for off-screen rendering so that post processing effects
   *        can be computed
   * 
   */
  class FrameBufferObject {
  private:
    GLuint m_id;  // The frame buffer id
    GLenum m_target;  // The frame buffer target

  public:
    /**
     * @brief Construct a new FrameBufferObject
     * 
     * @param target The binding point for the FrameBufferObject (defaults to GL_FRAMEBUFFER)
     */
    FrameBufferObject(const GLenum &target = GL_FRAMEBUFFER);

    /**
     * @brief Destroy the FrameBufferObject
     * 
     */
    virtual ~FrameBufferObject();

    /**
     * @brief Bind the FrameBufferObject to enable rendering to it
     * 
     */
    void Bind() const;

    /**
     * @brief Unbind the FrameBufferObject so scene can be drawn to screen
     * 
     */
    void Unbind() const;


  };

}

#endif