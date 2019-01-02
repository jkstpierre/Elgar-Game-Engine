/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_INTERPOLATED_HPP_
#define _ELGAR_INTERPOLATED_HPP_

// INCLUDES //

#include "elgar/physics/Movable.hpp"
#include "elgar/physics/Scalable.hpp"
#include "elgar/physics/Rotatable.hpp"

namespace elgar {

  /**
   * @brief An Interpolated is an object with position, scale, and orientation that utilizes
   *        fixed update physics steps and computes interpolated states for smooth rendering
   * 
   */
  class Interpolated : public Movable, public Scalable, public Rotatable {
  private:
    glm::vec3 m_prev_pos;   // Position to interpolate
    glm::vec3 m_prev_scale; // Scale to interpolate from
    glm::vec3 m_prev_rot;   // Rotation to interpolate from

  public:
    /**
     * @brief Construct a new Interpolated object
     * 
     * @param position    The position of the Interpolated
     * @param scale       The scale of the Interpolated
     * @param rotation    The rotation of the Interpolated
     */
    Interpolated(
      const glm::vec3 &position = {0.0f, 0.0f, 0.0f}, 
      const glm::vec3 &scale    = {1.0f, 1.0f, 1.0f}, 
      const glm::vec3 &rotation = {0.0f, 0.0f, 0.0f}
    );

    /**
     * @brief Set the position of the Interpolated
     * 
     * @param position The position to set
     */
    void SetPosition(const glm::vec3 &position);

    /**
     * @brief Set the scale of the Interpolated
     * 
     * @param scale The scale to set
     */
    void SetScale(const glm::vec3 &scale);

    /**
     * @brief Set the rotation of the Interpolated
     * 
     * @param rotation The Euler angles to set
     */
    void SetRotation(const glm::vec3 &rotation);

    /**
     * @brief Change the position of the Interpolated by a delta
     * 
     * @param delta The vector to change position by
     */
    void ChangePosition(const glm::vec3 &delta);

    /**
     * @brief Change the scale of the Interpolated by a delta
     * 
     * @param delta The vector to change scale by
     */
    void ChangeScale(const glm::vec3 &delta);

    /**
     * @brief Change the Rotation of the Interpolated by a delta
     * 
     * @param delta The vector to change rotation by
     */
    void ChangeRotation(const glm::vec3 &delta);

    /**
     * @brief Compute the Interpolated position for smooth rendering
     * 
     * @return The Interpolated position vector
     */
    glm::vec3 GetInterpolatedPosition();

    /**
     * @brief Compute the Interpolated scale for smooth rendering
     * 
     * @return The Interpolated scale vector
     */
    glm::vec3 GetInterpolatedScale();

    /**
     * @brief Compute the Interpolated rotation for smooth rendering
     * 
     * @return The Interpolated rotation vector
     */
    glm::vec3 GetInterpolatedEulerAngles();

    /**
     * @brief Store all the translaions, scalars, and rotations into a single matrix
     * 
     * @return The matrix
     */
    glm::mat4 GetMatrix();

  };

}

#endif