/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/data/Vertex.hpp"

namespace elgar {

  // FUNCTIONS //

  Vertex::Vertex(
    const glm::vec3 &position, 
    const glm::vec2 &texture_coords,
    const RGBA &color) {
      SetPosition(position);
      SetUV(texture_coords);
      SetColor(color);
  }

  Vertex::~Vertex() {
    // Do nothing
  }

  const glm::vec3 &Vertex::GetPosition() const {
    return m_position;
  }

  const glm::vec2 &Vertex::GetUV() const {
    return m_tex_coords;
  }

  const RGBA &Vertex::GetColor() const {
    return m_color;
  }

  void Vertex::SetPosition(const glm::vec3 &position) {
    m_position = position;
  }

  void Vertex::SetUV(const glm::vec2 &uv) {
    m_tex_coords = uv;
  }

  void Vertex::SetColor(const RGBA &color) {
    m_color = color;
  }

  Vertex &Vertex::operator =(const Vertex &vertex) {
    this->SetPosition(vertex.GetPosition());
    this->SetUV(vertex.GetUV());
    this->SetColor(vertex.GetColor());

    return *this;
  }
}