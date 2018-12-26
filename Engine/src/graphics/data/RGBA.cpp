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

  RGBA &RGBA::operator =(const RGBA &color) {
    this->m_red = color.m_red;
    this->m_green = color.m_green;
    this->m_blue = color.m_blue;
    this->m_alpha = color.m_alpha;

    return *this;
  }

  RGBA &RGBA::operator +(const RGBA &color) {
    this->m_red += color.m_red;
    this->m_green += color.m_green;
    this->m_blue += color.m_blue;
    this->m_alpha += color.m_alpha;

    return *this;
  }

  RGBA &RGBA::operator -(const RGBA &color) {
    this->m_red -= color.m_red;
    this->m_green -= color.m_green;
    this->m_blue -= color.m_blue;
    this->m_alpha -= color.m_alpha;

    return *this;
  }

  RGBA &RGBA::operator *(const RGBA &color) {
    this->m_red *= color.m_red;
    this->m_green *= color.m_green;
    this->m_blue *= color.m_blue;
    this->m_alpha *= color.m_alpha;

    return *this;
  }

  RGBA &RGBA::operator +=(const RGBA &color) {
    return (*this + color);
  }

  RGBA &RGBA::operator -=(const RGBA &color) {
    return (*this - color);
  }

  RGBA &RGBA::operator *=(const RGBA &color) {
    return (*this * color);
  }
  
}