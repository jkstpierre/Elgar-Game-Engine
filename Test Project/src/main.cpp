/*
  OceanBlack Game
  Author: Joseph St. Pierre
  Year: 2018
*/

#include "elgar/Engine.hpp"
#include "elgar/audio/AudioSource.hpp"
#include "elgar/audio/AudioListener.hpp"

#include <SDL2/SDL.h>

#include <stdio.h>
#include <iostream>
#include <typeinfo>

using namespace elgar;

int main() {
  // Create new instance of Elgar
  Engine *engine = new Engine();

  // Give elgar a window to manage
  engine->SetWindow(new Window("Hello World", 800, 600, FULLSCREEN));

  SDL_Delay(1000);

  // Unload resources from RAM
  delete engine;

  return 0;
}