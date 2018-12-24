/*
  Test Project
  Author: Joseph St. Pierre
  Year: 2018
*/

#include "elgar/Engine.hpp"
#include "elgar/audio/AudioSource.hpp"
#include "elgar/audio/AudioListener.hpp"
#include "elgar/core/AudioSystem.hpp"
#include "elgar/core/Window.hpp"
#include "elgar/core/IO.hpp"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <iostream>
#include <typeinfo>

using namespace elgar;

Engine *engine = nullptr;

void update() {
  if (Keyboard::IsKeyPressed(SDLK_ESCAPE))
    engine->SetRunning(false);

}

int main() {
  // Create new instance of Elgar
  engine = new Engine("StarLight", 1024, 768, NONE);

  AudioSystem *audio_sys = AudioSystem::GetInstance();

  if (audio_sys) {
    std::cout << "Have audio system handle!\n";
  }

  Window *window = Window::GetInstance();

  if (window) {
    std::cout << "Have window handle!\n";
  }

  engine->Run(update, NULL);

  // Unload resources from RAM
  delete engine;

  return 0;
}