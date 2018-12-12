/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/audio/AudioBuffer.hpp"
#include "elgar/core/Macros.hpp"

namespace elgar {

  // FUNCTIONS //

  AudioBuffer::AudioBuffer() {
    alGenBuffers(1, &m_buffer_data);  // Generate the OpenAL buffer
  }

  AudioBuffer::AudioBuffer(const ALuint &handle) {
    m_buffer_data = handle; // Copy the handle
  }

  AudioBuffer::~AudioBuffer() {
    alDeleteBuffers(1, &m_buffer_data); // Delete the OpenAL buffer
  }

  bool AudioBuffer::FillData(ALenum format, const ALvoid *data, ALsizei size, ALsizei freq) {
    alBufferData(m_buffer_data, format, data, size, freq);  // Fill the buffer with audio data

    return alGetError() == AL_NO_ERROR;
  }

  ALuint AudioBuffer::GetBufferData() const {
    return m_buffer_data; // Return handle to the buffer
  }

}