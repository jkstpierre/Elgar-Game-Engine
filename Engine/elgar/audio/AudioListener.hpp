/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_AUDIO_LISTENER_HPP_
#define _ELGAR_AUDIO_LISTENER_HPP_

// INCLUDES //

#include "elgar/physics/Movable.hpp"

namespace elgar {

  /**
   * @brief      An AudioListener represents the player's auditory perspective in 3D space (i.e. their ears)
   */
  class AudioListener : public Movable {
  private:


  public:
    /**
     * @brief      Default constructor
     */
    AudioListener();

    /**
     * @brief      Construct an AudioListener at (x,y,z)
     *
     * @param[in]  x     The x Cartesian coordinate
     * @param[in]  y     The y Cartesian coordinate
     * @param[in]  z     The z Cartesian coordinate
     */
    AudioListener(float x, float y, float z);

    /**
     * @brief      Default destructor
     */
    virtual ~AudioListener();

    /**
     * @brief      Set the position of the AudioListener
     *
     * @param[in]  x     The x Cartesian coordinate
     * @param[in]  y     The y Cartesian coordinate
     * @param[in]  z     The z Cartesian coordinate
     */
    void SetPosition(float x, float y, float z);

    /**
     * @brief Set the position of the AudioListener
     * 
     * @param position The position vector
     */
    void SetPosition(const glm::vec3 &position);

    /**
     * @brief      Change the position of the AudioListener
     *
     * @param[in]  dx    The change in the x coordinate
     * @param[in]  dy    The change in the y coordinate 
     * @param[in]  dz    The change in the z coordinate
     */
    void ChangePosition(float dx, float dy, float dz);

    /**
     * @brief Change the position of the AudioListener by a delta
     * 
     * @param delta The vector to change position by
     */
    void ChangePosition(const glm::vec3 &delta);
  };

}

#endif