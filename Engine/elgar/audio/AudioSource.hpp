/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_AUDIO_SOURCE_HPP_
#define _ELGAR_AUDIO_SOURCE_HPP_

// INCLUDES //

#include <AL/al.h>

#include "elgar/audio/AudioBuffer.hpp"

namespace elgar {

  /**
   * @brief      An AudioSource emits sound from a point in 3D space by reading from a buffer
   */
  class AudioSource {
  private:
    ALuint m_source;  // The reference to the OpenAL source

  public:
    /**
     * @brief      Default constructor for building a new AudioSource
     */
    AudioSource();

    /**
     * @brief      Builds an AudioSource with an associated buffer
     *
     * @param[in]  buffer  Handle to the buffer to read audio data from
     */
    AudioSource(const AudioBuffer *buffer);

    /**
     * @brief      Destroys the AudioSource
     */
    ~AudioSource();

    /**
     * @brief      Sets the buffer data for the AudioSource
     *
     * @param[in]  buffer  Handle to the buffer
     *
     * @return     True on success, false on error
     */
    bool SetBufferData(const AudioBuffer *buffer);
  };

}

#endif