/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/core/Window.hpp"
#include "elgar/core/Exception.hpp"
#include "elgar/core/Macros.hpp"

#include "elgar/graphics/sdl/RendererSDL.hpp"
#include "elgar/graphics/gl/RendererGL.hpp"

namespace elgar {

  // FUNCTIONS //

  Window::Window(const std::string &name, const int &width, const int &height, const Uint32 &params) {
    if (InstanceCounter<Window>::GetCount() > 1) {
      InstanceCounter<Window>::SetCount(1);

      throw Exception("ERROR: Window instance already exists!");
    }

    m_window = SDL_CreateWindow(
                name.c_str(), // The name of the window
                SDL_WINDOWPOS_CENTERED, // Center the window on the screen
                SDL_WINDOWPOS_CENTERED, // Center the window on the screen
                width,  // The width of the window (in pixels)
                height, // The height of the window (in pixels)
                params  // The SDL2 window params
              );

    if (!m_window) {
      throw Exception("ERROR: Failed to create window! SDL_Error: " + std::string(SDL_GetError()));
    }

    /*
     *  Instantiate proper renderer instance here
     */
    if (params & SDL_WINDOW_OPENGL) {
      // Initialize OpenGL Renderer
    }
    else {
      // Initialize default SDL Renderer
      m_renderer = new RendererSDL();
    }

    if (!m_renderer) {
      SDL_DestroyWindow(m_window);
      throw Exception("ERROR: Failed to create rendering context! SDL_Error: " + std::string(SDL_GetError()));
    }

    LOG("Window successfully created!\n");
  }

  Window::~Window() {
    delete m_renderer;

    SDL_DestroyWindow(m_window);  // Destroy the window

    LOG("Window destroyed!\n");
  }

  void Window::Present() {

  }

}