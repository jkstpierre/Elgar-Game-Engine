/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_RENDERER_SDL_HPP_
#define _ELGAR_RENDERER_SDL_HPP_

// INCLUDES //

#include <SDL2/SDL.h>
#include "elgar/graphics/Renderer.hpp"

namespace elgar {

  /**
   * @brief      Handles graphics rendering using SDL's graphics library
   */
  class RendererSDL : public Renderer {
  friend class Window;
  private:
    SDL_Renderer *m_renderer; // Handle to the rendering context

  private:
    /**
     * @brief    Constructs a new RendererSDL instance
     */
    RendererSDL();

    /**
     * @brief      Destroys a RendererSDL instance
     */
    virtual ~RendererSDL();

  private:
    /**
     * @brief      Present the contents of the renderer to the screen
     */
    void Present();
  };

}

#endif