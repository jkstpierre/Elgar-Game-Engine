/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_ROTATABLE_HPP_
#define _ELGAR_ROTATABLE_HPP_

// INCLUDES //

#include <glm/glm.hpp>

namespace elgar {

  /**
   * @brief A Rotatable is an object that has an orientation (in degrees) in 3D space
   * 
   */
  class Rotatable {
  private:
    glm::vec3 m_rotation; // The orientation of the rotatable (roll, pitch, yaw)

  public:
    /**
     * @brief Construct a new Rotatable object
     * 
     */
    Rotatable();

    /**
     * @brief Construct a new Rotatable object
     * 
     * @param rotation  The orientation
     */
    Rotatable(const glm::vec3 &rotation);

    /**
     * @brief Set the rotation
     * 
     * @param rotation    The orientation
     */
    void SetRotation(const glm::vec3 &rotation);

    /**
     * @brief Change the rotation of the Rotatable by a delta
     * 
     * @param delta   The delta to rotate by
     */
    void ChangeRotation(const glm::vec3 &delta);

    /**
     * @brief Get the Euler angles for the Rotatable
     * 
     * @return Reference to the Euler angles
     */
    const glm::vec3 &GetEulerAngles() const;

  };

}

#endif