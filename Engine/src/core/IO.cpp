/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/core/IO.hpp"

#include "elgar/core/Macros.hpp"

namespace elgar {

  // KEYBOARD FUNCTIONS //

  Keyboard::Keyboard() : Singleton<Keyboard>(this) {
    LOG("Keyboard online...\n");
  }

  Keyboard::~Keyboard() {
    LOG("Keyboard offline...\n");
  }

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

  // MOUSE FUNCTIONS //

  Mouse::Mouse() : Singleton<Mouse>(this) {
    LOG("Mouse online...\n");
  }

  Mouse::~Mouse() {
    LOG("Mouse offline...\n");
  }

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