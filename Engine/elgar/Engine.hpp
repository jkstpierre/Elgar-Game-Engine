/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

/*! \mainpage
 *
 * \htmlonly <style>div.image img[src="elgar.jpg"]{width:200px;}</style> \endhtmlonly 
 * @image html elgar.jpg "Sir Edward Elgar"
 * 
 * \section intro_sec Introduction
 *
 * Welcome to Elgar3D's documentation page. This site should serve as a reference manual for any
 * would be developers seeking to build games using Elgar3D.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Installing dependencies
 *  
 */

#ifndef _ELGAR_GAME_ENGINE_HPP_
#define _ELGAR_GAME_ENGINE_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"
#include <string>

// DEFINES //

#define DEFAULT_PHYS_STEPS_PER_SECOND   50  // Number of physics cycles per second

namespace elgar {

  /**
   * @brief      The Engine class oversees all core functionalities of the Elgar pipeline. Every program 
   *             using Elgar must utilize this class. (Is a Singleton class)
   */
  class Engine : public Singleton<Engine> {
  private:
    bool m_running; // Track whether engine is running or not

  public:
    /**
     * @brief      Initialize a new instance of Elgar
     *
     * @param[in]  window_name    The name of the window
     * @param[in]  window_width   The window width (in pixels)
     * @param[in]  window_height  The window height (in pixels)
     * @param[in]  window_flags   The window flags (window enumeration flags)
     */
    Engine(
      const std::string &window_name, 
      const int &window_width, 
      const int &window_height, 
      const unsigned char &window_flags
    );

    /**
     * @brief      Destroys this instance of Elgar
     */
    virtual ~Engine();

  public:
    /**
     * @brief      Run the application loop
     *
     * @param[in]  update        The update function (called every frame)
     * @param[in]  fixed_update  The fixed update function (called every phys step)
     * @param[in]  render        The render function (called every frame)
     */
    void Run(void (*update)(), void (*fixed_update)(), void (*render)());

    /**
     * @brief      Checks if the engine is running or not
     *
     * @return     True if running, False otherwise.
     */
    bool IsRunning() const;

    /**
     * @brief      Sets whether or not the application loop is running
     *
     * @param[in]  running  The value to see running to
     */
    void SetRunning(const bool &running);

  };

}

#endif
