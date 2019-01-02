/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace elgar {

  // FUNCTIONS //

  Camera::Camera(const glm::mat4 &projection, const glm::mat4 &view) {
    SetProjectionMatrix(projection);
    SetViewMatrix(view);
  }

  Camera::~Camera() {
    // Do nothing
  }

  void Camera::SetProjectionMatrix(const glm::mat4 &projection) {
    m_projection_matrix = projection;
  }

  void Camera::SetViewMatrix(const glm::mat4 &view) {
    m_view_matrix = view;
  }

  void Camera::SetPosition(const glm::vec3 &position) {
    m_view_matrix = glm::translate(glm::mat4(), -position);
  }

  void Camera::ChangePosition(const glm::vec3 &delta) {
    m_view_matrix = glm::translate(m_view_matrix, -delta);
  }

  const glm::mat4 &Camera::GetProjectionMatrix() const {
    return m_projection_matrix;
  }

  const glm::mat4 &Camera::GetViewMatrix() const {
    return m_view_matrix;
  }

  void Camera::Draw(const Shader &shader) const {
    shader.Use();   // Use the shader program

    // Set projection and view matrices for the shader
    shader.SetMat4("projection_matrix", m_projection_matrix);
    shader.SetMat4("view_matrix", m_view_matrix);
  }

}