/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/data/RGBA.hpp"

namespace elgar {

  // FUNCTIONS //

  RGBA::RGBA(const GLubyte &r, const GLubyte &g, const GLubyte &b, const GLubyte &a) {
    m_red = r;
    m_green = g;
    m_blue = b;
    m_alpha = a;
  }

  RGBA::~RGBA() {
    // Do nothing
  }

  const GLubyte &RGBA::GetRedChannel() const {
    return m_red;
  }

  const GLubyte &RGBA::GetGreenChannel() const {
    return m_green;
  }

  const GLubyte &RGBA::GetBlueChannel() const {
    return m_blue;
  }

  const GLubyte &RGBA::GetAlphaChannel() const {
    return m_alpha;
  }

  GLuint RGBA::GetPackedData() const {
    return  ((GLuint) m_alpha) << 24 |
            ((GLuint) m_blue) << 16 |
            ((GLuint) m_green) << 8 |
            ((GLuint) m_red);
  }

  glm::vec4 RGBA::GetData() const {
    return {m_red / 255.f, m_green / 255.f, m_blue / 255.f, m_alpha / 255.f};
  }

  RGBA &RGBA::operator =(const RGBA &color) {
    this->m_red = color.m_red;
    this->m_green = color.m_green;
    this->m_blue = color.m_blue;
    this->m_alpha = color.m_alpha;

    return *this;
  }

  RGBA operator +(const RGBA &c1, const RGBA &c2) {
    return RGBA(c1.m_red + c2.m_red, 
                c1.m_green + c2.m_green,
                c1.m_blue + c2.m_blue,
                c1.m_alpha + c2.m_alpha);
  }

  RGBA operator -(const RGBA &c1, const RGBA &c2) {
    return RGBA(c1.m_red - c2.m_red,
                c1.m_green - c2.m_green,
                c1.m_blue - c2.m_blue,
                c1.m_alpha - c2.m_alpha);
  }

  RGBA operator *(const RGBA &c1, const RGBA &c2) {
    return RGBA(c1.m_red * c2.m_red,
                c1.m_green * c2.m_green,
                c1.m_blue * c2.m_blue,
                c1.m_alpha * c2.m_alpha);
  }

  RGBA &RGBA::operator +=(const RGBA &color) {
    this->m_red += color.m_red;
    this->m_green += color.m_green;
    this->m_blue += color.m_blue;
    this->m_alpha += color.m_alpha;

    return *this;
  }

  RGBA &RGBA::operator -=(const RGBA &color) {
    this->m_red -= color.m_red;
    this->m_green -= color.m_green;
    this->m_blue -= color.m_blue;
    this->m_alpha -= color.m_alpha;

    return *this;
  }

  RGBA &RGBA::operator *=(const RGBA &color) {
    this->m_red *= color.m_red;
    this->m_green *= color.m_green;
    this->m_blue *= color.m_blue;
    this->m_alpha *= color.m_alpha;

    return *this;
  }
  
}