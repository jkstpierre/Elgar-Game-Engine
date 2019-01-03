/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_IO_HPP_
#define _ELGAR_IO_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <unordered_map>

namespace elgar {

  /**
   * @brief      The Keyboard captures all key events during application runtime
   */
  class Keyboard : public Singleton<Keyboard> {
  friend class Engine;    // Grant the Engine exclusive instantiation rights
  private:
    std::unordered_map<SDL_Keycode, bool> m_keys;  // The key table

  private:
    /**
     * @brief Construct a new Keyboard object
     * 
     */
    Keyboard();

    /**
     * @brief Destroy the Keyboard object
     * 
     */
    virtual ~Keyboard();

  public:
    /**
     * @brief      Presses a key on the keyboard
     *
     * @param[in]  key   The key
     */
    void PressKey(const SDL_Keycode &key);

    /**
     * @brief      Releases a key on the keyboard
     *
     * @param[in]  key   The key
     */
    void ReleaseKey(const SDL_Keycode &key);

    /**
     * @brief      Determines if a given key is pressed
     *
     * @param[in]  key   The key
     *
     * @return     True if key pressed, False otherwise.
     */
    bool IsKeyPressed(const SDL_Keycode &key);

  };

  /**
   * @brief      Mouse Button Enumerations
   */
  enum MouseButton {
    LEFT = 0x01,
    RIGHT = 0x02,
    MIDDLE = 0x04
  };

  /**
   * @brief      The Mouse captures all mouse events during application runtime
   */
  class Mouse : public Singleton<Mouse> {
  friend class Engine;      // Grant the engine exclusive instantiation rights
  private:
    glm::vec2 m_pos; // The 2D position of the cursor

    unsigned char m_buttons;  // Track button presses

  private:
    /**
     * @brief Construct a new Mouse object
     * 
     */
    Mouse();

    /**
     * @brief Destroy the Mouse object
     * 
     */
    virtual ~Mouse();

  public:
    /**
     * @brief      Press a MouseButton down
     *
     * @param[in]  button  The button
     */
    void PressButton(const MouseButton &button);

    /**
     * @brief      Release a MouseButton
     *
     * @param[in]  button  The button
     */
    void ReleaseButton(const MouseButton &button);

    /**
     * @brief      Check if a given MouseButton is pressed
     *
     * @param[in]  button  The button
     */
    bool IsButtonPressed(const MouseButton &button);

    /**
     * @brief      Set the position of the mouse
     *
     * @param[in]  pos   The position
     */
    void SetPosition(const glm::vec2 &pos);

    /**
     * @brief      Get the position of the mouse
     *
     * @return     The position.
     */
    glm::vec2 GetPosition();
  };

}

#endif