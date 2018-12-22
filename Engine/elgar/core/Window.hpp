/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_WINDOW_HPP_
#define _ELGAR_WINDOW_HPP_

// INCLUDES //

#include <SDL2/SDL.h>
#include <string>
#include <glm/glm.hpp>

#include "elgar/core/InstanceCounter.hpp"

namespace elgar {

  /**
   * @brief      Enumerations for describing appropriate setup of a Window object
   */
  enum WindowFlags {
    NONE = 0x00,        // No flags
    FULLSCREEN = 0x01,  // The window starts in fullscreen mode at specified resolution
    FULLSCREEN_DESKTOP = 0x02,  // The window starts in fullscreen mode at screen resolution
    BORDERLESS = 0x04,  // The window is borderless
    MINIMIZED = 0x08,   // The windows starts out minimized
    MAXIMIZED = 0x10,   // The window starts out maximized
    RESIZABLE = 0x20    // The window can be scaled
  };

  /**
   * @brief      The Window class handles construction, destruction, and
   *             management of SDL2 windows. Only one Window can exist at a time
   */
  class Window : public InstanceCounter<Window> {
  friend class Engine;  // Grant engine rights to private members
  private:
    SDL_Window *m_window; // Handle to the SDL2 window context
    SDL_GLContext m_context;  // Handle to the OpenGL context

    glm::vec2 m_dimensions; // The dimensions of the window

  public:
    /**
     * @brief      Constructs a new Window
     *
     * @param[in]  name    The name of the window
     * @param[in]  width   The width (in pixels)
     * @param[in]  height  The height (in pixels)
     * @param[in]  flags   Specific window flags
     */
    Window(const std::string &name, const int &width, const int &height, const unsigned char &flags);

    /**
     * @brief      Destroys a Window
     */
    virtual ~Window();

  public:
    /**
     * @brief      Sets whether or not to use vertical sync (i.e. framerate capped to refresh rate)
     *
     * @param[in]  value  The value to set vsync to (true to enable, false to disable)
     */
    void SetVerticalSync(const bool &value) const;

    /**
     * @brief      Get the screen dimensions
     *
     * @return     The dimensions as a 2D vector
     */
    glm::vec2 GetDimensions() const;

  private:
    /**
     * @brief      Initializes OpenGL specs
     *
     * @return     True on success, false on failure
     */
    bool InitGL();

    /**
     * @brief      Draws all renderables to the window
     */
    void Present();

  };

}

#endif