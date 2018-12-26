/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_INTERPOLATED_MOVABLE_HPP_
#define _ELGAR_INTERPOLATED_MOVABLE_HPP_

// INCLUDES //

#include "elgar/physics/Movable.hpp"

namespace elgar {

  /**
   * @brief An InterpolatedMovable is an entity that can interpolate its approximate
   *        position between two known points according to an alpha value. This is especially
   *        useful for smooth rendering of objects that employ fixed updates.
   * 
   */
  class InterpolatedMovable : public Movable {
  private:
    glm::vec3 m_prev_position;  // The previous of position of the movable

  public:
    /**
     * @brief Construct a new Interpolated Movable object
     * 
     */
    InterpolatedMovable();

    /**
     * @brief Construct a new Interpolated Movable object at a specific 3D point
     * 
     * @param x   The x coordinate
     * @param y   The y coordinate
     * @param z   The z coordinate
     */
    InterpolatedMovable(const float &x, const float &y, const float &z);

    /**
     * @brief Construct a new Interpolated Movable object
     * 
     * @param position    A glm::vec3 containing the xyz coordinates
     */
    InterpolatedMovable(const glm::vec3 &position);

    /**
     * @brief Set the position of the InterpolatedMovable
     * 
     * @param position The position to set
     */
    void SetPosition(const glm::vec3 &position);

    /**
     * @brief Set the position of the InterpolatedMovable
     * 
     * @param x   The x coordinate
     * @param y   The y coordinate
     * @param z   The z coordinate
     */
    void SetPosition(const float &x, const float &y, const float &z);

    /**
     * @brief Change the position of the InterpolatedMovable
     * 
     * @param delta_position The change in position
     */
    void ChangePosition(const glm::vec3 &delta_position);

    /**
     * @brief Change the position of the InterpolatedMovable
     * 
     * @param dx    The change in the x coordinate
     * @param dy    The change in the y coordinate
     * @param dz    The change in the z coordinate
     */
    void ChangePosition(const float &dx, const float &dy, const float &dz);

    /**
     * @brief Compute the interpolated position and return it
     * 
     * @return The interpolated position
     */
    glm::vec3 GetInterpolatedPosition() const;
  };

}

#endif