/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/timers/FrameTimer.hpp"
#include "elgar/core/Macros.hpp"

namespace elgar {

  // FUNCTIONS //

  FrameTimer::FrameTimer() : Singleton<FrameTimer>(this) {
    m_delta_time = 0.0f;
    m_time_scale = 1.0f;

    m_fixed_delta_time = 0.0f;
    m_fixed_time_scale = 1.0f;

    m_alpha = 0.0f;

    LOG("FrameTimer online...\n");
  }

  FrameTimer::~FrameTimer() {
    // Do nothing

    LOG("FrameTimer offline...\n");
  }

  void FrameTimer::SetDeltaTime(const float &dt) {
    m_delta_time = dt;
  }

  void FrameTimer::SetFixedDeltaTime(const float &fixed_dt) {
    m_fixed_delta_time = fixed_dt;
  }

  void FrameTimer::SetAlpha(const float &alpha) {
    m_alpha = alpha;
  }

  void FrameTimer::SetTimescale(const float &time_scale) {
    m_time_scale = time_scale;
  }

  void FrameTimer::SetFixedTimescale(const float &fixed_time_scale) {
    m_fixed_time_scale = fixed_time_scale;
  }

  float FrameTimer::GetDeltaTime() const {
    return m_delta_time * m_time_scale;
  }

  float FrameTimer::GetFixedDeltaTime() const {
    return m_fixed_delta_time * m_fixed_time_scale;
  }

  const float &FrameTimer::GetTimescale() const {
    return m_time_scale;
  }

  const float &FrameTimer::GetFixedTimescale() const {
    return m_fixed_time_scale;
  }

  const float &FrameTimer::GetAlpha() const {
    return m_alpha;
  }

  unsigned int FrameTimer::GetFPS() const {
    return (unsigned int)(1.f / m_delta_time);
  }

}