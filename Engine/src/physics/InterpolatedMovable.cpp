/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/physics/InterpolatedMovable.hpp"
#include "elgar/timers/FrameTimer.hpp"

namespace elgar {

  // FUNCTIONS //

  InterpolatedMovable::InterpolatedMovable() {
    SetPosition(0.0f, 0.0f, 0.0f);
  }

  InterpolatedMovable::InterpolatedMovable(const float &x, const float &y, const float &z) 
  : Movable(x,y,z) {
    SetPosition(x, y, z);
  }

  InterpolatedMovable::InterpolatedMovable(const glm::vec3 &position) : Movable(position) {
    SetPosition(position);
  }

  void InterpolatedMovable::SetPosition(const glm::vec3 &position) {
    m_prev_position = position;       
    Movable::SetPosition(position);
  }

  void InterpolatedMovable::SetPosition(const float &x, const float &y, const float &z) {
    SetPosition({x, y, z});
  }

  void InterpolatedMovable::ChangePosition(const glm::vec3 &delta_position) {
    m_prev_position = GetPosition();  // Update the previous position

    Movable::ChangePosition(delta_position);  // Change the current position
  }

  void InterpolatedMovable::ChangePosition(const float &dx, const float &dy, const float &dz) {
    ChangePosition({dx, dy, dz});
  }

  glm::vec3 InterpolatedMovable::GetInterpolatedPosition() const {
    const float alpha = FrameTimer::GetAlpha();
    return GetPosition() * alpha + m_prev_position * (1.0f - alpha);
  }
}