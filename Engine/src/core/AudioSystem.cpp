/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/core/AudioSystem.hpp"
#include "elgar/core/Exception.hpp"
#include "elgar/core/Macros.hpp"
#include "elgar/core/Utilities.hpp"

#include "elgar/audio/aux/stb_vorbis.h"

#define   DR_WAV_IMPLEMENTATION
#include  "elgar/audio/aux/dr_wav.h"

#define   DR_MP3_IMPLEMENTATION
#include  "elgar/audio/aux/dr_mp3.h"

namespace elgar {

  // FUNCTIONS //

  AudioSystem::AudioSystem() {
    // Open the default audio device
    m_device = alcOpenDevice(NULL);

    // If something went wrong
    if (!m_device) {
      // Abort audiosystem initialization
      throw Exception("ERROR: AudioSystem failed to lock audio device!");
    }

    // Create an audio context for the locked device
    m_context = alcCreateContext(m_device, NULL);

    // If something went wrong
    if (!m_context) {
      // Close the opened device
      alcCloseDevice(m_device);

      // Abort audiosystem initialization
      throw Exception("ERROR: AudioSystem failed to create audio context!");
    }

    // Setup the current ALcontext
    alcMakeContextCurrent(m_context);

    // Clear the error code
    alGetError();

    // Create log message concerning successful init
    LOG("AudioSystem online...\n");
  }

  AudioSystem::~AudioSystem() {
    // Shutdown OpenAL

    LOG("AudioSystem deleting buffers...\n");

    // Delete all buffers
    for (auto it = m_buffers.begin(); it != m_buffers.end(); it++) {
      AudioBuffer *buffer = it->second;
      delete buffer;
    }

    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);

    LOG("AudioSystem offline...\n");
  }

  bool AudioSystem::LoadAudioFile(const std::string &filepath) {
    // Get the file extension of the filepath
    std::string ext = getFileExtension(filepath);

    // If the file is neither .wav or .ogg 
    if (ext != "wav" && ext != "ogg" && ext != "mp3") {
      LOG("ERROR: Attempted to load invalid audio file %s!\n", filepath.c_str());
      return false;
    }

    // Check if file exists
    FILE *file = fopen(filepath.c_str(), "rb");
    if (!file) {
      LOG("ERROR: %s does not exist on disk!\n", filepath.c_str());
      return false;
    }

    fclose(file); // Close the audio file to prevent memory leak

    // Check if file has already been loaded into main memory
    if (m_buffers.find(filepath) != m_buffers.end()) {
      LOG("WARNING: %s already exists in memory!\n", filepath.c_str());
      return false;
    }

    // Generate a new buffer for the file data
    AudioBuffer *new_buffer = new AudioBuffer();

    ALenum format = AL_FORMAT_MONO16; // Assume mono data by default

    bool success = true;  // Temp var to track success

    // Load audio file

    if (ext == "wav") {
      // Load wav file into program memory
      
      unsigned int channels;  // Number of channels (i.e. mono or stereo)
      unsigned int sample_rate;
      uint64_t sample_count;

      // Read raw wav data from disk
      int32_t *data = drwav_open_and_read_file_s32(filepath.c_str(), &channels, &sample_rate, &sample_count);

      // Check for error
      if (!data) {
        LOG("ERROR: Failed to read %s!\n", filepath.c_str());
        return false;
      }

      if (channels == 2) {
        format = AL_FORMAT_STEREO16;  // Switch to stereo format
      }

      // Send the data to the new AudioBuffer
      success = new_buffer->FillData(format, data, sample_count * channels * sizeof(ALshort), sample_rate);

      // Check for error
      if (!success) {
        LOG("ERROR: Failed to create an audio buffer for %s!\n", filepath.c_str());

        // Delete the buffer
        delete new_buffer;
        new_buffer = nullptr;
      }

      // Free the temp wav data
      drwav_free(data);
    }
    else if (ext == "mp3") {
      // Load mp3 file into program memory

    }
    else {
      // Load ogg file into program memory

    }

    if (success) {
      // Store the audio buffer into memory
      m_buffers.insert(std::pair<std::string, AudioBuffer *>(filepath, new_buffer));

      LOG("AudioSystem loaded %s successfully!\n", filepath.c_str());
    }

    // Indicate success
    return success;
  }

  const AudioBuffer *AudioSystem::GetBufferData(const std::string &filepath) const {
    const AudioBuffer *buffer = nullptr;

    if (m_buffers.find(filepath) != m_buffers.end()) 
      buffer = m_buffers.at(filepath);  // Get handle to the required buffer

    // Return the buffer
    return buffer;
  }
}