/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

/**
 * @file ASCII.hpp
 * @author Joseph St. Pierre
 * @brief 
 * @version 0.1
 * @date 2019-01-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _ELGAR_ASCII_HPP_
#define _ELGAR_ASCII_HPP_

// INCLUDES //

#include "elgar/graphics/data/Texture.hpp"

#include <glm/glm.hpp>

namespace elgar {

  /**
   * @brief The ASCII struct contains all relevant data OpenGL needs to render ASCII characters to the screen
   * 
   */
  struct ASCII {
    const Texture   *texture;   // The texture for the character
    glm::ivec2      size;       // The size of the glyph
    glm::ivec2      bearing;    // Offset from baseline to left/top of glyph
    GLuint          advance;    // Offset to advance to next glyph
  };

}

#endif