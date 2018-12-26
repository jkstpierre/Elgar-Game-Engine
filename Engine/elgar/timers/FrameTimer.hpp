/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_FRAME_TIMER_HPP_
#define _ELGAR_FRAME_TIMER_HPP_

// INCLUDES //

namespace elgar {

  /**
   * @brief      The FrameTimer keeps track of the delta time between frames as well as the current
   *             simulation time scale. (Static singleton class)
   */
  class FrameTimer {
  friend class Engine;  // Give elgar exclusive access to private fields
  private:
    static float m_delta_time;  // Time between frames in seconds
    static float m_time_scale;  // Scalar to multiply time by
    static float m_fixed_delta_time;  // Time in seconds between physics steps
    static float m_fixed_time_scale;  // Scalar to multiply fixed time by
    static float m_alpha; // Interpolated alpha from phys steps

  private:
    static void SetDeltaTime(const float &dt); // Record the delta time
    static void SetFixedDeltaTime(const float &fixed_dt);  // Record the fixed delta time
    static void SetAlpha(const float &alpha); // Set the alpha

  public:
    /**
     * @brief      Set the time scale to multiply delta time by (useful for changing simulation speed)
     *
     * @param[in]  time_scale  The time scale
     */
    static void SetTimescale(const float &time_scale);

    /**
     * @brief      Set the fixed time scale to multiply fixed delta time by
     *
     * @param[in]  fixed_time  The fixed time scale
     */
    static void SetFixedTimescale(const float &fixed_time_scale);

    /**
     * @brief      Get the delta time elapsed since last frame
     *
     * @return     The delta time.
     */
    static float GetDeltaTime();

    /**
     * @brief      Get the fixed delta time elapsed since last frame
     *
     * @return     The fixed delta time.
     */
    static float GetFixedDeltaTime();

    /**
     * @brief      Get the time scale
     *
     * @return     The time scale.
     */
    static float GetTimescale();

    /**
     * @brief      Get the fixed time scale
     *
     * @return     The fixed time scale.
     */
    static float GetFixedTimescale();

    /**
     * @brief      Get the alpha value for interpolated (smooth) rendering
     *
     * @return     The alpha value
     */
    static float GetAlpha();
  };

}

#endif