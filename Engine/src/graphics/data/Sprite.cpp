/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

// INCLUDES //

#include "elgar/graphics/data/Sprite.hpp"

namespace elgar {

  // FUNCTIONS //

  Sprite::Sprite(const Texture *texture, const RGBA &color, const std::vector<glm::vec2> uv_array) {
    m_texture = texture;
  }

}