/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/audio/AudioSource.hpp"
#include "elgar/core/Exception.hpp"

namespace elgar {

  // FUNCTIONS //

  AudioSource::AudioSource() {
    alGenSources(1, &m_source); // Generate an OpenAL audio source
  }

  AudioSource::AudioSource(const AudioBuffer *buffer) {
    alGenSources(1, &m_source);

    if (!SetBufferData(buffer)) {
      alDeleteSources(1, &m_source);
      throw Exception("ERROR: Failed to set buffer data for AudioSource!");
    }
  }

  AudioSource::~AudioSource() {
    alDeleteSources(1, &m_source);
  }

  bool AudioSource::SetBufferData(const AudioBuffer *buffer) {
    alSourcei(m_source, AL_BUFFER, buffer->GetBufferData());  // Set the buffer for the source

    return alGetError() == AL_NO_ERROR;
  }

}