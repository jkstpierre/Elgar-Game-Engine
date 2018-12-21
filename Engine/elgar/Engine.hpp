/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_GAME_ENGINE_HPP_
#define _ELGAR_GAME_ENGINE_HPP_

// INCLUDES //

#include "elgar/core/AudioSystem.hpp"
#include "elgar/core/Window.hpp"

// DEFINES //

#define DEFAULT_PHYS_STEPS_PER_SECOND   50  // Number of physics cycles per second

namespace elgar {

  /**
   * @brief      The Engine class oversees all core functionalities of the Elgar pipeline. Every program 
   *             using Elgar must utilize this class. (Note: Follows the singleton class design pattern)
   */
  class Engine {
  private:
    static Engine *m_instance; // Instance of the engine class

  private:
    AudioSystem *m_audio_system;  // Instance of the audio system
    Window *m_window; // Handle to the window context

    bool m_running; // Track whether engine is running or not

  private:
    Engine(); // Default constructor
    virtual ~Engine();  // Default destructor

  public:
    /**
     * @brief      Initializes Elgar and its subsystems and creates an instance of the engine
     */
    static void Init();

    /**
     * @brief      Shuts down Elgar and its subsystems and destroys the engine instance
     */
    static void Shutdown();

    /**
     * @brief      Returns the Elgar Engine instance
     *
     * @return     The singleton instance of the engine, or nullptr if engine not initialized.
     */
    static Engine *GetInstance();

    /**
     * @brief      Run the application loop
     *
     * @param[in]  update        The update function (called every frame)
     * @param[in]  fixed_update  The fixed update function (called every phys step)
     * @param[in]  render        The render function (called every frame)
     */
    void Run(void (*update)(), void (*fixed_update)(), void (*render)() = nullptr);

    /**
     * @brief      Checks if the engine is running or not
     *
     * @return     True if running, False otherwise.
     */
    bool IsRunning() const;

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