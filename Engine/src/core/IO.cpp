/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/core/IO.hpp"

namespace elgar {

  // KEYBOARD STATIC FIELDS //

  std::unordered_map<SDL_Keycode, bool> Keyboard::m_keys;

  // KEYBOARD FUNCTIONS //

  void Keyboard::PressKey(const SDL_Keycode &key) {
    m_keys[key] = true;
  }

  void Keyboard::ReleaseKey(const SDL_Keycode &key) {
    m_keys[key] = false;
  }

  bool Keyboard::IsKeyPressed(const SDL_Keycode &key) {
    if (m_keys.find(key) == m_keys.end())
      return false;

    return m_keys[key];
  }

  // MOUSE STATIC FIELDS //

  glm::vec2 Mouse::m_pos;

  unsigned char Mouse::m_buttons;

  // MOUSE FUNCTIONS //

  void Mouse::PressButton(const MouseButton &button) {
    m_buttons |= (unsigned char)button;
  }

  void Mouse::ReleaseButton(const MouseButton &button) {
    m_buttons &= ~(unsigned char)button;
  }

  bool Mouse::IsButtonPressed(const MouseButton &button) {
    return (m_buttons & (unsigned char)button) != 0;
  }

  void Mouse::SetPosition(const glm::vec2 &pos) {
    m_pos = pos;
  }

  glm::vec2 Mouse::GetPosition() {
    return m_pos;
  }

}