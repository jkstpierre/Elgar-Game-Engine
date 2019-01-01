/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/physics/Rotatable.hpp"

namespace elgar {
  
  // FUNCTIONS //

  Rotatable::Rotatable() {
    SetRotation({0.0f, 0.0f, 0.0f});    // Set the roll, pitch and yaw
  }

  Rotatable::Rotatable(const glm::vec3 &rotation) {
    SetRotation(rotation);
  }

  void Rotatable::SetRotation(const glm::vec3 &rotation) {
    m_rotation = rotation;
  }

  void Rotatable::ChangeRotation(const glm::vec3 &delta) {
    m_rotation += delta;
  }

  const glm::vec3 &Rotatable::GetEulerAngles() const {
    return m_rotation;
  }

}