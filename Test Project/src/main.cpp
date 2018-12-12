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
  AudioSystem *audio_system = nullptr;

  if (engine) {
    audio_system = engine->GetAudioSystem();
  }

  audio_system->LoadAudioFile("Elgar_Cello_Concerto.ogg");

  AudioListener *listener = new AudioListener(0.0f, 0.0f, 0.0f);

  AudioSource *source = new AudioSource(audio_system->GetBufferData("Elgar_Cello_Concerto.ogg"));

  source->Play();

  SDL_Delay(30000);

  delete source;
  delete listener;

  Engine::Shutdown();

  return 0;
}