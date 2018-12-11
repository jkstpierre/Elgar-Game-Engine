/*
  OceanBlack Game
  Author: Joseph St. Pierre
  Year: 2018
*/

#include "elgar/Engine.hpp"

#include <stdio.h>
#include <iostream>
#include <typeinfo>

using namespace elgar;

int main() {
  Engine::Init();

  Engine *engine = Engine::GetInstance();

  if (engine) {
    engine->GetAudioSystem()->LoadAudioFile("explosion.wav");
  }

  Engine::Shutdown();

  return 0;
}