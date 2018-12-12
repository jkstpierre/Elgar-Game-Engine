/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_MOVABLE_HPP_
#define _ELGAR_MOVABLE_HPP_

// INCLUDES //

#include <glm/glm.hpp>

namespace elgar {

  /**
   * @brief      A base class for objects that have a position
   */
  class Movable {
  private:
    glm::vec3 m_position; // The position of the movable

  public:
    /**
     * @brief      Default constructor
     */
    Movable();

    /**
     * @brief      Constructs a Movable at (x, y, z) in 3D space
     *
     * @param[in]  x     The x Cartesian coordinate
     * @param[in]  y     The y Cartesian coordinate
     * @param[in]  z     The z Cartesian coordinate
     */
    Movable(float x, float y, float z);

    /**
     * @brief      Default destructor
     */
    virtual ~Movable();

    /**
     * @brief      Sets the position of the Movable in 3D space
     *
     * @param[in]  x     The x Cartesian coordinate
     * @param[in]  y     The y Cartesian coordinate
     * @param[in]  z     The z Cartesian coordinate
     */
    void SetPosition(float x, float y, float z);

    /**
     * @brief      Change the position of the Movable in 3D space by a delta
     *
     * @param[in]  dx    The change in the x Cartesian coordinate
     * @param[in]  dy    The change in the y Cartesian coordinate
     * @param[in]  dz    The change in the z Cartesian coordinate
     */
    void ChangePosition(float dx, float dy, float dz);

    /**
     * @brief      Change the position of the Movable in 3D space by a delta and delta time
     *
     * @param[in]  dx    The change in the x Cartesian coordinate
     * @param[in]  dy    The change in the y Cartesian coordinate
     * @param[in]  dz    The change in the z Cartesian coordinate
     * @param[in]  dt    The delta time to scale by
     */
    void ChangePosition(float dx, float dy, float dz, float dt);

    /**
     * @brief      Get the position of the Movable
     *
     * @return     The position of the Movable
     */
    const glm::vec3 &GetPosition() const;
  };
}

#endif