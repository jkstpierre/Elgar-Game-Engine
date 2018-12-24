/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/core/Window.hpp"
#include "elgar/core/Exception.hpp"
#include "elgar/core/Macros.hpp"

#include <GL/glew.h>

namespace elgar {

  // FUNCTIONS //

  Window::Window(
    const std::string &name, 
    const int &width, 
    const int &height, 
    const unsigned char &flags
  ) : Singleton<Window>(this) {

    Uint32 params = 0;  // SDL2 window params

    // Handle error cases

    if ((flags & FULLSCREEN) && (flags & FULLSCREEN_DESKTOP))
      throw Exception("ERROR: Window cannot be both fullscreen and fullscreen_dekstop!");

    if ((flags & MINIMIZED) && (flags & MAXIMIZED))
      throw Exception("ERROR: Window cannot be both minimized and maximized!");

    if (flags & FULLSCREEN)
      params |= SDL_WINDOW_FULLSCREEN;
    else if (flags & FULLSCREEN_DESKTOP)
      params |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (flags & MINIMIZED)
      params |= SDL_WINDOW_MINIMIZED;
    else if (flags & MAXIMIZED)
      params |= SDL_WINDOW_MAXIMIZED;
    if (flags & BORDERLESS)
      params |= SDL_WINDOW_BORDERLESS;
    if (flags & RESIZABLE)
      params |= SDL_WINDOW_RESIZABLE;

    // Set OpenGL Context flags

    // Set major and minor versions and request core profile
    SDL_GL_SetAttribute(
      SDL_GL_CONTEXT_MAJOR_VERSION,
      DEFAULT_GL_MAJOR_VERSION
    );
    SDL_GL_SetAttribute(
      SDL_GL_CONTEXT_MINOR_VERSION, 
      DEFAULT_GL_MINOR_VERSION
    );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Enable 4x Anti-Aliasing
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Forward compatibility with macs
    #ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    #endif

    m_dimensions = glm::vec2(width, height);  // Store the screen dimensions

    m_window = SDL_CreateWindow(
      name.c_str(), // The name of the window
      SDL_WINDOWPOS_CENTERED, // Center the window on the screen
      SDL_WINDOWPOS_CENTERED, // Center the window on the screen
      width,  // The width of the window (in pixels)
      height, // The height of the window (in pixels)
      params | SDL_WINDOW_OPENGL // The SDL2 window params
    );

    if (!m_window) {
      throw Exception("ERROR: Failed to create window! SDL_Error: " + std::string(SDL_GetError()));
    }

    m_context = SDL_GL_CreateContext(m_window); // Create an OpenGL context for the window

    if (!m_context) {
      SDL_DestroyWindow(m_window);

      throw Exception("ERROR: Failed to create OpenGL context! SDL_Error: " + std::string(SDL_GetError()));
    }

    // Initialize OpenGL here

    if (!InitGL()) {
      SDL_GL_DeleteContext(m_context);
      SDL_DestroyWindow(m_window);

      throw Exception("ERROR: Failed to initialize OpenGL!");
    }

    LOG("Window successfully created!\n");
  }

  Window::~Window() {
    SDL_GL_DeleteContext(m_context); // Destroy the OpenGL context
    SDL_DestroyWindow(m_window);  // Destroy the window

    LOG("Window destroyed!\n");
  }

  void Window::Present(void (*render)()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     *  Draw things in here
     */

    // Call rendering function if possible
    if (render)
      render();

    SDL_GL_SwapWindow(m_window);
  }

  bool Window::InitGL() {
    SetVerticalSync(true);  // Enable V-sync by default

    // Initialize glew
    glewExperimental = true;
    GLenum code = glewInit();

    if (code != GLEW_OK) {
      LOG("ERROR: Failed to initialize GLEW!\n");
      LOG("OpenGL_Error: %s\n", glewGetErrorString(code));
      return false;
    }

    glGetError(); // Clear the error flag

    // Set the viewport size
    glViewport(0, 0, m_dimensions.x, m_dimensions.y);

    code = glGetError();
    if (code != GL_NO_ERROR) {
      LOG("ERROR: Failed to set viewport!\n");
      LOG("OpenGL_Error: %s\n", glewGetErrorString(code));
      return false;
    }

    // Set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    code = glGetError();
    if (code != GL_NO_ERROR) {
      LOG("ERROR: Failed to set clear color!\n");
      LOG("OpenGL_Error: %s\n", glewGetErrorString(code));
      return false;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    code = glGetError();
    if (code != GL_NO_ERROR) {
      LOG("ERROR: Failed to enable depth testing!\n");
      LOG("OpenGL_Error: %s\n", glewGetErrorString(code));
      return false;
    }

    // Enable multisampling
    glEnable(GL_MULTISAMPLE);

    code = glGetError();
    if (code != GL_NO_ERROR) {
      LOG("ERROR: Failed to enable multisampling!\n");
      LOG("OpenGL_Error: %s\n", glewGetErrorString(code));
      return false;
    }

    // Enable vertex culling
    glEnable(GL_CULL_FACE);

    code = glGetError();
    if (code != GL_NO_ERROR) {
      LOG("ERROR: Failed to enable vertex culling!\n");
      LOG("OpenGL_Error: %s\n", glewGetErrorString(code));
      return false;
    }

    return true;
  }

  void Window::SetVerticalSync(const bool &value) const {
    if (value) {
      if (SDL_GL_SetSwapInterval(1) < 0) {
        LOG("Warning: Failed to enable vertical sync!\n");
        LOG("SDL_Error: %s\n", SDL_GetError());
        SDL_ClearError();
      }
    }
    else
      SDL_GL_SetSwapInterval(0);
  }

  glm::vec2 Window::GetDimensions() const {
    return m_dimensions;
  }

}