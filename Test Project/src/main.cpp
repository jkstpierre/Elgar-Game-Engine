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
#include "elgar/graphics/ShaderManager.hpp"
#include "elgar/core/IO.hpp"

#include "elgar/graphics/data/RGBA.hpp"

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

  // Unload resources from RAM
  delete engine;

  return 0;
}