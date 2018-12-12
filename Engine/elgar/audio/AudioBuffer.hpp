/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_AUDIO_BUFFER_HPP_
#define _ELGAR_AUDIO_BUFFER_HPP_

// INCLUDES //

#include <AL/al.h>

namespace elgar {

  /**
   * @brief      An AudioBuffer is a C++ OOP wrapper for OpenAL buffers. It operates as a private class
   *             as all of its fields and methods are only accessible by other classes in the audio engine
   */
  class AudioBuffer {
  friend class AudioSystem; // Grant AudioSystem exclusive instantiation rights
  friend class AudioSource; // Grant AudioSource field viewing rights
  private:
    ALuint m_buffer_data; // Reference to the OpenAL buffer

  private:
    AudioBuffer();  // Default constructor

    AudioBuffer(const ALuint &handle);  // Construct AudioBuffer from handle

    virtual ~AudioBuffer(); // Default destructor

    /**
     * @brief      Fill the buffer with audio data
     *
     * @param[in]  format  The format (mono or stereo)
     * @param[in]  data    The byte data of the audio
     * @param[in]  size    The size in bytes of the audio data
     * @param[in]  freq    The sampling frequency
     *
     * @return     True on success, false on error
     */
    bool FillData(ALenum format, const ALvoid *data, ALsizei size, ALsizei freq);

    /**
     * @brief      Gets the handle to the buffer data
     *
     * @return     Handle to the OpenAL buffer
     */
    ALuint GetBufferData() const;
  };

}

#endif