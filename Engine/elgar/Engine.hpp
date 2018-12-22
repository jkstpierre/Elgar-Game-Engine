/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_GAME_ENGINE_HPP_
#define _ELGAR_GAME_ENGINE_HPP_

// INCLUDES //

#include "elgar/core/InstanceCounter.hpp"
#include "elgar/core/AudioSystem.hpp"
#include "elgar/core/Window.hpp"

// DEFINES //

#define DEFAULT_PHYS_STEPS_PER_SECOND   50  // Number of physics cycles per second

namespace elgar {

  /**
   * @brief      The Engine class oversees all core functionalities of the Elgar pipeline. Every program 
   *             using Elgar must utilize this class. (Note: Can only be created once)
   */
  class Engine : public InstanceCounter<Engine> {
  private:
    AudioSystem *m_audio_system;  // Instance of the audio system
    Window *m_window; // Handle to the window context

    bool m_running; // Track whether engine is running or not

  public:
    /**
     * @brief      Create a new instance of Elgar
     */
    Engine();

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
     * @param[in]  render        The render function (called every frame) (completely optional)
     */
    void Run(void (*update)(), void (*fixed_update)(), void (*render)() = nullptr);

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

  public:
    /**
     * @brief      Gets a handle to the audio system
     *
     * @return     A handle to the audio system
     */
    AudioSystem *GetAudioSystem();

    /**
     * @brief      Set the window for the Engine
     *
     * @param[in]  window  The window instance
     */
    void SetWindow(Window *window);

    /**
     * @brief      Returns the window instance
     *
     * @return     The window.
     */
    const Window *GetWindow();
  };

}

#endif