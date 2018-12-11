/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/physics/Movable.hpp"

namespace elgar {

  // FUNCTIONS //

  Movable::Movable() {
    SetPosition(0.0f, 0.0f, 0.0f);
  }

  Movable::Movable(float x, float y, float z) {
    SetPosition(x, y, z);
  }

  Movable::~Movable() {

  }

  void Movable::SetPosition(float x, float y, float z) {
    m_position = glm::vec3(x, y, z);
  }

  void Movable::ChangePosition(float dx, float dy, float dz) {
    m_position += glm::vec3(dx, dy, dz);
  }

  void Movable::ChangePosition(float dx, float dy, float dz, float dt) {
    m_position += dt * glm::vec3(dx, dy, dz);
  }

  const glm::vec3 &Movable::GetPosition() const {
    return m_position;
  }
}