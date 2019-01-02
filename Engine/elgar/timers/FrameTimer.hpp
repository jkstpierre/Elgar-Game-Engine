/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_FRAME_TIMER_HPP_
#define _ELGAR_FRAME_TIMER_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"

namespace elgar {

  /**
   * @brief      The FrameTimer keeps track of the delta time between frames as well as the current
   *             simulation time scale. (Singleton class)
   */
  class FrameTimer : public Singleton<FrameTimer> {
  friend class Engine;  // Give elgar exclusive access to private fields
  private:
    float m_delta_time;  // Time between frames in seconds
    float m_time_scale;  // Scalar to multiply time by
    float m_fixed_delta_time;  // Time in seconds between physics steps
    float m_fixed_time_scale;  // Scalar to multiply fixed time by
    float m_alpha; // Interpolated alpha from phys steps

  private:
    void SetDeltaTime(const float &dt); // Record the delta time
    void SetFixedDeltaTime(const float &fixed_dt);  // Record the fixed delta time
    void SetAlpha(const float &alpha); // Set the alpha

  private:
    /**
     * @brief Construct a new FrameTimer object
     * 
     */
    FrameTimer();

    /**
     * @brief Destroy the FrameTimer object
     * 
     */
    virtual ~FrameTimer();

  public:
    /**
     * @brief      Set the time scale to multiply delta time by (useful for changing simulation speed)
     *
     * @param[in]  time_scale  The time scale
     */
    void SetTimescale(const float &time_scale);

    /**
     * @brief      Set the fixed time scale to multiply fixed delta time by
     *
     * @param[in]  fixed_time  The fixed time scale
     */
    void SetFixedTimescale(const float &fixed_time_scale);

    /**
     * @brief      Get the delta time elapsed since last frame
     *
     * @return     The delta time.
     */
    float GetDeltaTime() const;

    /**
     * @brief      Get the fixed delta time elapsed since last frame
     *
     * @return     The fixed delta time.
     */
    float GetFixedDeltaTime() const;

    /**
     * @brief      Get the time scale
     *
     * @return     The time scale.
     */
    const float &GetTimescale() const;

    /**
     * @brief      Get the fixed time scale
     *
     * @return     The fixed time scale.
     */
    const float &GetFixedTimescale() const;

    /**
     * @brief      Get the alpha value for interpolated (smooth) rendering
     *
     * @return     The alpha value
     */
    const float &GetAlpha() const;

    /**
     * @brief Compute the current frames per second
     * 
     * @return The frames per second
     */
    unsigned int GetFPS() const;
  };

}

#endif