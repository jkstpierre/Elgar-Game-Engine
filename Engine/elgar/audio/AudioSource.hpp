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
#include "elgar/physics/Movable.hpp"

namespace elgar {

  /**
   * @brief      An AudioSource emits sound from a point in 3D space by reading from a buffer
   */
  class AudioSource : public Movable {
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
    virtual ~AudioSource();

    /**
     * @brief      Sets the buffer data for the AudioSource
     *
     * @param[in]  buffer  Handle to the buffer
     *
     * @return     True on success, false on error
     */
    bool SetBufferData(const AudioBuffer *buffer);

    /**
     * @brief      Set the position of the AudioSource
     *
     * @param[in]  x     The x Cartesian coordinate
     * @param[in]  y     The y Cartesian coordinate
     * @param[in]  z     The z Cartesian coordinate
     */
    void SetPosition(float x, float y, float z);

    /**
     * @brief      Change the position of the AudioSource
     *
     * @param[in]  dx    The change in x
     * @param[in]  dy    The change in y
     * @param[in]  dz    The change in z
     */
    void ChangePosition(float dx, float dy, float dz);

    /**
     * @brief      Play the AudioSource
     */
    void Play();

    /**
     * @brief      Stop the AudioSource
     */
    void Stop();

    /**
     * @brief      Pause the AudioSource
     */
    void Pause();

    /**
     * @brief      Checks if the AudioSource is playing
     *
     * @return     True if playing, False otherwise.
     */
    bool IsPlaying();

    /**
     * @brief      Checks if the AudioSource is paused
     *
     * @return     True if paused, False otherwise.
     */
    bool IsPaused();
  };

}

#endif