/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_RGBA_HPP_
#define _ELGAR_RGBA_HPP_

// INCLUDES //

#include <GL/glew.h>

namespace elgar {

  /**
   * @brief The RGBA class represents a 32-bit rgba encoded color
   * 
   */
  class RGBA {
  private:
    GLubyte m_red;  // The red channel
    GLubyte m_green;  // The green channel
    GLubyte m_blue;   // The blue channel
    GLubyte m_alpha;  // The alpha channel

  public:
    /**
     * @brief Construct a new RGBA object
     * 
     * @param r The red color channel
     * @param g The greem color channel
     * @param b The blue color channel
     * @param a The alpha color channel
     */
    RGBA(
      const GLubyte &r = 0, 
      const GLubyte &g = 0, 
      const GLubyte &b = 0, 
      const GLubyte &a = 0
    );

    /**
     * @brief Destroy the RGBA object
     * 
     */
    virtual ~RGBA();

    /**
     * @brief Get the red color channel
     * 
     * @return The red color channel
     */
    const GLubyte &GetRedChannel() const;

    /**
     * @brief Get the green color channel
     * 
     * @return The green color channel
     */
    const GLubyte &GetGreenChannel() const;

    /**
     * @brief Get the blue color channel
     * 
     * @return The blue color channel
     */
    const GLubyte &GetBlueChannel() const;

    /**
     * @brief Get the alpha color channel
     * 
     * @return The alpha color channel
     */
    const GLubyte &GetAlphaChannel() const;

    /**
     * @brief Set this color object equal to another
     * 
     * @param color The color to equal
     * @return An updated reference to the RGBA object
     */
    RGBA &operator =(const RGBA &color);

    /**
     * @brief Add one color to another color to make a new color
     * 
     * @param color The color to add
     * @return An updated reference to the RGBA object
     */
    RGBA &operator +(const RGBA &color);

    /**
     * @brief Subtract one color from another color to make a new color
     * 
     * @param color The color to subtract by
     * @return An updated reference to the RGBA object
     */
    RGBA &operator -(const RGBA &color);
 
    /**
     * @brief Multiply one color by another color to make a new color
     * 
     * @param color The color to multiply by
     * @return An updated reference to the RGBA object
     */
    RGBA &operator *(const RGBA &color);

    /**
     * @brief Add another color to this color
     * 
     * @param color The color to add by
     * @return An updated reference to the RGBA object
     */
    RGBA &operator +=(const RGBA &color);

    /**
     * @brief Subtract another color from this color
     * 
     * @param color The color to subtract by
     * @return An updated reference to the RGBA object
     */
    RGBA &operator -=(const RGBA &color);

    /**
     * @brief Multiply this color by another color
     * 
     * @param color The color to multiply by
     * @return An updated reference to the RGBA object
     */
    RGBA &operator *=(const RGBA &color);
  };

}

#endif