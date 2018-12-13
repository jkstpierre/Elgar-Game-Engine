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
  Engine::Init();

  Engine *engine = Engine::GetInstance();
  
  if (engine) {
    engine->Run(nullptr, nullptr);
  }

  Engine::Shutdown();

  return 0;
}