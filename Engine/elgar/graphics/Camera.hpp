/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

#ifndef _ELGAR_CAMERA_HPP_
#define _ELGAR_CAMERA_HPP_

// INCLUDES //

#include <glm/glm.hpp>

#include "elgar/graphics/Shader.hpp"

namespace elgar {

  /**
   * @brief A Camera stores information regarding the projection fustrum as well as
   *        its position in the world to render the scene from
   * 
   */
  class Camera {
  private:
    glm::mat4 m_projection_matrix;    // The projection fustrum
    glm::mat4 m_view_matrix;          // Where in the world is the camera

  public:
    /**
     * @brief Construct a new Camera object
     * 
     * @param projection The projection matrix for the camera
     * @param view       The view matrix (defaults to the identity matrix)
     */
    Camera(const glm::mat4 &projection, const glm::mat4 &view = glm::mat4());

    /**
     * @brief Destroy the Camera object
     * 
     */
    virtual ~Camera();

    /**
     * @brief Set the projection matrix for the Camera
     * 
     * @param projection The projection matrix to set
     */
    void SetProjectionMatrix(const glm::mat4 &projection);

    /**
     * @brief Set the view matrix for the Camera
     * 
     * @param view The view matrix to set
     */
    void SetViewMatrix(const glm::mat4 &view);

    /**
     * @brief Set the Camera position
     * 
     * @param position The position of the camera in 3D space
     */
    void SetPosition(const glm::vec3 &position);

    /**
     * @brief Change the Camera position
     * 
     * @param delta The change in the position of the camera
     */
    void ChangePosition(const glm::vec3 &delta);

    /**
     * @brief Get the projection matrix for the Camera
     * 
     * @return Reference to the Camera's projection matrix
     */
    const glm::mat4 &GetProjectionMatrix() const;

    /**
     * @brief Get the view matrix for the Camera
     * 
     * @return Reference to the Camera's view matrix
     */
    const glm::mat4 &GetViewMatrix() const;

    /**
     * @brief Draw the Camera using a Shader program
     * 
     * @param shader Reference to the Shader program to use
     */
    void Draw(const Shader &shader) const;
  };

}

#endif