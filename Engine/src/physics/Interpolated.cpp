/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "elgar/physics/Interpolated.hpp"
#include "elgar/timers/FrameTimer.hpp"

namespace elgar {

  // FUNCTIONS //

  Interpolated::Interpolated(
    const glm::vec3 &position,
    const glm::vec3 &scale,
    const glm::vec3 &rotation
  ) : Movable(position), Scalable(scale), Rotatable(rotation) {
    m_prev_pos = GetPosition();
    m_prev_scale = GetScale();
    m_prev_rot = GetEulerAngles();
  }

  void Interpolated::SetPosition(const glm::vec3 &position) {
    m_prev_pos = position;
    Movable::SetPosition(position);
  }

  void Interpolated::SetScale(const glm::vec3 &scale) {
    m_prev_scale = scale;
    Scalable::SetScale(scale);
  }

  void Interpolated::SetRotation(const glm::vec3 &rotation) {
    m_prev_rot = rotation;
    Rotatable::SetRotation(rotation);
  }

  void Interpolated::ChangePosition(const glm::vec3 &delta) {
    m_prev_pos = GetPosition(); // Update the previous position
    Movable::ChangePosition(delta); // Update the current position
  }

  void Interpolated::ChangeScale(const glm::vec3 &delta) {
    m_prev_scale = GetScale();
    Scalable::ChangeScale(delta);
  }

  void Interpolated::ChangeRotation(const glm::vec3 &delta) {
    m_prev_rot = GetEulerAngles();
    Rotatable::ChangeRotation(delta);
  }

  glm::vec3 Interpolated::GetInterpolatedPosition() {
    glm::vec3 curr_pos = GetPosition();

    float alpha = 0.0f;

    // Get the frame timer and get the alpha if possible
    FrameTimer *frame_timer = FrameTimer::GetInstance();
    if (frame_timer)
      alpha = frame_timer->GetAlpha();

    glm::vec3 interpolated = curr_pos * alpha + m_prev_pos * (1.0f - alpha);

    return interpolated;
  }

  glm::vec3 Interpolated::GetInterpolatedScale() {
    glm::vec3 curr_scale = GetScale();

    float alpha = 0.0f;

    // Get the frame timer and get the alpha if possible
    FrameTimer *frame_timer = FrameTimer::GetInstance();
    if (frame_timer)
      alpha = frame_timer->GetAlpha();

    glm::vec3 interpolated = curr_scale * alpha + m_prev_scale * (1.0f - alpha);

    return interpolated;
  }

  glm::vec3 Interpolated::GetInterpolatedEulerAngles() {
    glm::vec3 curr_rot = GetEulerAngles();

    float alpha = 0.0f;

    // Get the frame timer and get the alpha if possible
    FrameTimer *frame_timer = FrameTimer::GetInstance();
    if (frame_timer)
      alpha = frame_timer->GetAlpha();

    glm::vec3 interpolated = curr_rot * alpha + m_prev_rot * (1.0f - alpha);

    return interpolated;
  }

  glm::mat4 Interpolated::GetMatrix() {
    glm::mat4 model_matrix;   // The model matrix for the Interpolated

    // Translate the model matrix by the position
    model_matrix = glm::translate(model_matrix, GetInterpolatedPosition());

    // Scale the matrix
    model_matrix = glm::scale(model_matrix, GetInterpolatedScale());

    // Create quaternion for rotation
    glm::quat quaternion(GetInterpolatedEulerAngles()); // Create a quaternion from angles

    // Rotate the model matrix
    return model_matrix * glm::toMat4(quaternion);
  }

}