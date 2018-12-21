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

#include "elgar/core/InstanceCounter.hpp"
#include "elgar/graphics/Renderer.hpp"

namespace elgar {

  /**
   * @brief      The Window class handles construction, destruction, and
   *             management of SDL2 windows. Only one Window can exist at a time
   */
  class Window : public InstanceCounter<Window> {
  friend class Engine;  // Grant engine rights to private members
  private:
    SDL_Window *m_window; // Handle to the SDL2 window context
    Renderer *m_renderer; // Handle to the elgar rendering context

  public:
    /**
     * @brief      Constructs a new Window
     *
     * @param[in]  name    The name of the window
     * @param[in]  width   The width (in pixels)
     * @param[in]  height  The height (in pixels)
     * @param[in]  params  Additional SDL2 parameters
     */
    Window(const std::string &name, const int &width, const int &height, const Uint32 &params);

    /**
     * @brief      Destroys a Window
     */
    virtual ~Window();

    /**
     * @brief      Returns a handle to the rendering context of the Window
     *
     * @return     The appropriate rendering context
     */
    const Renderer *GetRenderingContext() const;

  private:
    /**
     * @brief      Draws all renderables to the window
     */
    void Present();

  };

}

#endif