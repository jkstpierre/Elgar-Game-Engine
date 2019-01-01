/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_SCALABLE_HPP_
#define _ELGAR_SCALABLE_HPP_

// INCLUDES //

#include <glm/glm.hpp>

namespace elgar {

  /**
   * @brief A Scalable is an object that takes up space in the scene
   * 
   */
  class Scalable {
  private:
    glm::vec3 m_scale; // The scale of the Scalable

  public:
    /**
     * @brief Construct a new Scalable object with scale (0,0,0)
     * 
     */
    Scalable();

    /**
     * @brief Construct a new Scalable object
     * 
     * @param scale    The scale of the Scalable
     */
    Scalable(const glm::vec3 &scale);

    /**
     * @brief Set the scale of the Scalable
     * 
     * @param scale    The scale of the Scalable
     */
    void SetScale(const glm::vec3 &scale);

    /**
     * @brief   Change the scale of the Scalable by a delta
     * 
     * @param delta   The change in the scale
     */
    void ChangeScale(const glm::vec3 &delta);
    
    /**
     * @brief Get the scale of the Scalable
     * 
     * @return Reference to the scale vector
     */
    const glm::vec3 &GetScale() const;
  };

}

#endif