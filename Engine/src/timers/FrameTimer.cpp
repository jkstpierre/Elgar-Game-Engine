/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/timers/FrameTimer.hpp"

namespace elgar {

  // STATIC FIELDS //

  float FrameTimer::m_delta_time = 0.0f;  
  float FrameTimer::m_time_scale = 1.0f;  
  float FrameTimer::m_fixed_delta_time = 0.0f;  
  float FrameTimer::m_fixed_time_scale = 1.0f;
  float FrameTimer::m_alpha = 0.0f;

  // FUNCTIONS //

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

  const float FrameTimer::GetDeltaTime() {
    return m_delta_time * m_time_scale;
  }

  const float FrameTimer::GetFixedDeltaTime() {
    return m_fixed_delta_time * m_fixed_time_scale;
  }

  const float FrameTimer::GetTimescale() {
    return m_time_scale;
  }

  const float FrameTimer::GetFixedTimescale() {
    return m_fixed_time_scale;
  }

  const float FrameTimer::GetAlpha() {
    return m_alpha;
  }
}