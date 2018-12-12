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

  void AudioSource::SetPosition(float x, float y, float z) {
    Movable::SetPosition(x, y, z);  // Update the position

    alSource3f(m_source, AL_POSITION, x, y, z);
  }

  void AudioSource::ChangePosition(float dx, float dy, float dz) {
    Movable::ChangePosition(dx, dy, dz);

    const glm::vec3 &pos = GetPosition(); // Get the update position

    alSource3f(m_source, AL_POSITION, pos.x, pos.y, pos.z);
  }

  void AudioSource::Play() {
    alSourcePlay(m_source);
  }

  void AudioSource::Stop() {
    alSourceStop(m_source);
  }

  void AudioSource::Pause() {
    alSourcePause(m_source);
  }

  bool AudioSource::IsPlaying() {
    ALint status;

    alGetSourcei(m_source, AL_SOURCE_STATE, &status);

    return status == AL_PLAYING;
  }

  bool AudioSource::IsPaused() {
    ALint status;

    alGetSourcei(m_source, AL_SOURCE_STATE, &status);

    return status == AL_PAUSED;
  }

}