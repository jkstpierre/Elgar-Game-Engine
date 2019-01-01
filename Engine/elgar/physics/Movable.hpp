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
   * @brief      A Movable is a base class for objects that have a position
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
     * @brief Construct a new Movable object from a glm::vec3
     * 
     * @param position    The xyz coordinates of the Movable
     */
    Movable(const glm::vec3 &position);

    /**
     * @brief      Default destructor
     */
    virtual ~Movable();

    /**
     * @brief Set the Position of the Movable
     * 
     * @param position  The position of the Movable
     */
    void SetPosition(const glm::vec3 &position);

    /**
     * @brief Change the position of the Movable by a delta vector
     * 
     * @param delta_position  The change in the position of the movable
     */
    void ChangePosition(const glm::vec3 &delta);

    /**
     * @brief      Get the position of the Movable
     *
     * @return     The position of the Movable
     */
    const glm::vec3 &GetPosition() const;
  };
}

#endif