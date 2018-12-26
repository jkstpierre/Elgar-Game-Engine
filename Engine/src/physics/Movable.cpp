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

  Movable::Movable(const float &x, const float &y, const float &z) {
    SetPosition(x, y, z);
  }

  Movable::Movable(const glm::vec3 &position) {
    SetPosition(position);
  }

  Movable::~Movable() {

  }

  void Movable::SetPosition(const glm::vec3 &position) {
    m_position = position;
  }

  void Movable::SetPosition(const float &x, const float &y, const float &z) {
    SetPosition({x, y, z});
  }

  void Movable::ChangePosition(const glm::vec3 &delta_position) {
    m_position += delta_position;
  }

  void Movable::ChangePosition(const float &dx, const float &dy, const float &dz) {
    ChangePosition({dx, dy, dz});
  }

  const glm::vec3 &Movable::GetPosition() const {
    return m_position;
  }
}