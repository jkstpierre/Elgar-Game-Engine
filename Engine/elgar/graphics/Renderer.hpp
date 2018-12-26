/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_RENDERER_HPP_
#define _ELGAR_RENDERER_HPP_

// INCLUDES //

namespace elgar {

  /**
   * @brief      A Renderer is an abstract base class to be implemented by specific graphics renderers
   */
  class Renderer {
  friend class Window;  // Grant window access to private members
  public:
    Renderer();

    virtual ~Renderer();

  protected:
    
  };

}

#endif