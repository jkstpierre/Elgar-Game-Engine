/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_VERTEX_HPP_
#define _ELGAR_VERTEX_HPP_

// INCLUDES //

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace elgar {

  /**
   * @brief A Vertex contains the raw vertex data to be sent to the GPU
   * 
   */
  struct Vertex {
    glm::vec3 m_pos;          // The position of the vertex
    glm::vec3 m_normal;       // The normal map (used for lighting)
    glm::vec2 m_uv;           // The texture coordinates for the vertex
  };

};

#endif