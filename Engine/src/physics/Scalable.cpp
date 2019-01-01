/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/physics/Scalable.hpp"

namespace elgar {

  // FUNCTIONS //

  Scalable::Scalable() {
    SetScale({0.0f, 0.0f, 0.0f});
  }

  Scalable::Scalable(const glm::vec3 &scale) {
    SetScale(scale);
  }

  void Scalable::SetScale(const glm::vec3 &scale) {
    m_scale = scale;
  }

  void Scalable::ChangeScale(const glm::vec3 &delta) {
    m_scale += delta;
  }

  const glm::vec3 &Scalable::GetScale() const {
    return m_scale;
  }

}