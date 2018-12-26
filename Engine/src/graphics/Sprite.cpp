/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/Sprite.hpp"

namespace elgar {

  // FUNCTIONS //
  Sprite::Sprite(const GLfloat &width, const GLfloat &height, const Texture *texture) {
    SetDimensions(width, height);
    SetTexture(texture);
    UpdateDimensions();
  }

  Sprite::~Sprite() {
    // Do nothing
  }

  void Sprite::SetColor(const RGBA &color) {
    for (int i = 0; i < SPRITE_VERTEX_COUNT; i++) {
      Vertex &v = m_vertices[i];
      v.SetColor(color);
    }
  }

  void Sprite::ChangeColor(const RGBA &delta_color) {
    for (int i = 0; i < SPRITE_VERTEX_COUNT; i++) {
      Vertex &v = m_vertices[i];
      RGBA temp = v.GetColor();
      v.SetColor(temp + delta_color);
    }
  }

  void Sprite::SetTexture(const Texture *texture) {
    m_texture = texture;
  }

  void Sprite::SetDimensions(const float &width, const float &height) {
    m_dimensions = {width, height, 0.0f};
    UpdateDimensions();
  }

  void Sprite::ChangeDimensions(const float &delta_width, const float &delta_height) {
    m_dimensions += glm::vec3(delta_width, delta_height, 0.0f);
    UpdateDimensions();
  }

  void Sprite::UpdateDimensions() {
    // Set the vertices for the Sprite
    for (int i = 0; i < SPRITE_VERTEX_COUNT; i++) {
      Vertex &v = m_vertices[i];
      v.SetPosition(v.GetPosition() * m_dimensions);
    }
  }

}