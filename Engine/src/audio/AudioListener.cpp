/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include <AL/al.h>

#include "elgar/audio/AudioListener.hpp"

namespace elgar {

  // FUNCTIONS //

  AudioListener::AudioListener() {
    SetPosition(0.0f, 0.0f, 0.0f);  
  }

  AudioListener::AudioListener(float x, float y, float z) {
    SetPosition(x, y, z);
  }

  AudioListener::~AudioListener() {

  }

  void AudioListener::SetPosition(float x, float y, float z) {
    Movable::SetPosition(x, y, z);

    alListener3f(AL_POSITION, x, y, z);
  }

  void AudioListener::ChangePosition(float dx, float dy, float dz) {
    Movable::ChangePosition(dx, dy, dz);

    const glm::vec3 &pos = GetPosition();

    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
  }
}