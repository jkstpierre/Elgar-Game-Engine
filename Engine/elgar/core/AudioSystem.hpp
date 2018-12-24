/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_AUDIO_SYSTEM_HPP_
#define _ELGAR_AUDIO_SYSTEM_HPP_

// INCLUDES //

#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <unordered_map>

#include "elgar/audio/AudioBuffer.hpp"
#include "elgar/core/Singleton.hpp"

namespace elgar {

  /**
   * @brief      The AudioSystem class manages and stores all sound and music for Elgar.
   *             (Is a Singleton class)
   */
  class AudioSystem : public Singleton<AudioSystem> {
  friend class Engine;  // Grant the Engine exclusive instantiation rights
  private:
    ALCdevice *m_device;    // Handle to the audio device
    ALCcontext *m_context;  // Handle to the audio context
    
    std::unordered_map <std::string, AudioBuffer *> m_buffers;   // Hashtable of audio buffers

  private:
    AudioSystem();  // Default constructor
    virtual ~AudioSystem(); // Default destructor

  public:
    /**
     * @brief      Loads an audio file into program memory (.wav, .mp3, or .ogg).
     *
     * @param      filepath  The filepath to the audio file
     *
     * @return     True on successful load, false on error
     */
    bool LoadAudioFile(const std::string &filepath);

    /**
     * @brief      Gets the number of buffers loaded in memory
     *
     * @return     The number of loaded buffers
     */
    size_t GetBufferCount() const;

    /**
     * @brief      Retrieve an audio buffer containing the data for a given audio file
     *
     * @param[in]  filepath  The loaded filepath of the buffer (corresponds to the one given to LoadAudioFile)
     *
     * @return     Pointer to the audio buffer or nullptr if buffer does not exist
     */
    const AudioBuffer *GetBufferData(const std::string &filepath) const;
  };

}

#endif