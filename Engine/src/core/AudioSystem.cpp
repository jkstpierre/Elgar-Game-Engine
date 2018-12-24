/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include <AL/alut.h>

#include "elgar/core/AudioSystem.hpp"
#include "elgar/core/Exception.hpp"
#include "elgar/core/Macros.hpp"
#include "elgar/core/Utilities.hpp"

#include "elgar/audio/aux/stb_vorbis.h"

namespace elgar {

  // FUNCTIONS //

  AudioSystem::AudioSystem() : Singleton<AudioSystem>(this) {
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

    // Initialize OpenAL Utility Toolkit

    if(!alutInitWithoutContext(NULL, NULL)) {
      alcDestroyContext(m_context);
      alcCloseDevice(m_device);

      // Abort initialization
      throw Exception("ERROR: AudioSystem failed to initialize ALUT!");
    }

    // Clear alut's error code
    alutGetError(); 

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

    alutExit(); // Shutdown ALUT

    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);

    LOG("AudioSystem offline...\n");
  }

  bool AudioSystem::LoadAudioFile(const std::string &filepath) {
    // Check if file has already been loaded into main memory
    if (m_buffers.find(filepath) != m_buffers.end()) {
      LOG("WARNING: %s already exists in memory!\n", filepath.c_str());
      return false;
    }

    // Build an OpenAL buffer from the requested file
    ALuint buffer = alutCreateBufferFromFile(filepath.c_str()); 

    // Assume success
    ALboolean success = AL_TRUE;

    // Check if something went wrong
    if (buffer == AL_NONE) {
      ALenum error = alutGetError();  // Find out what went wrong

      success = AL_FALSE;

      if (error == ALUT_ERROR_OUT_OF_MEMORY) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: Out of memory!\n");
      }
      else if (error == ALUT_ERROR_INVALID_OPERATION) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: OpenAL has not been initialized!\n");
      }
      else if (error == ALUT_ERROR_NO_CURRENT_CONTEXT) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: OpenAL has no current context!\n");
      }
      else if (error == ALUT_ERROR_AL_ERROR_ON_ENTRY) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: Prior unresolved error exists!\n");
      }
      else if (error == ALUT_ERROR_ALC_ERROR_ON_ENTRY) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: Prior unresolved error exists in context!\n");
      }
      else if (error == ALUT_ERROR_GEN_BUFFERS) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: Failed to generate buffer!\n");
      }
      else if (error == ALUT_ERROR_BUFFER_DATA) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: Failed to send data to buffer!\n");
      }
      else if (error == ALUT_ERROR_IO_ERROR) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: Failed to read file on disk!\n");
      }
      else if (error == ALUT_ERROR_UNSUPPORTED_FILE_TYPE) {
        /*
         *  TODO: Add handmade alternative file loading method here
         */

        // Get the filepath extension
        std::string ext = getFileExtension(filepath);

        if (ext == "ogg") {
          ALshort *data;
          ALint channels;
          ALint sample_rate;
          ALint samples;

          // Load the audio data from disk
          samples = stb_vorbis_decode_filename(filepath.c_str(), &channels, &sample_rate, &data);

          // If loaded successfully
          if (samples >= 0) {
            // Generate a new OpenAL buffer
            alGenBuffers(1, &buffer);

            // Check out the format
            ALenum format = AL_FORMAT_MONO16;

            if (channels == 2)
              format = AL_FORMAT_STEREO16;

            // Send the data to OpenAL
            alBufferData(buffer, format, data, samples * channels * sizeof(ALshort), sample_rate);

            // If something went wrong
            if (alGetError() != AL_NO_ERROR) {
              // Destroy the buffer
              alDeleteBuffers(1, &buffer);
              buffer = AL_NONE;
            }
            else {
              // Success!
              success = AL_TRUE;
            }
          }

          free(data); // Free the data from stb_vorbis
        }

        // If still failed to load file
        if (buffer == AL_NONE) {
          LOG("ERROR: Failed to load %s!\n", filepath.c_str());
          LOG("\tReason: File type not supported!\n");
        }
      }
      else if (ALUT_ERROR_UNSUPPORTED_FILE_SUBTYPE) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: File mode not supported!\n");
      }
      else if (ALUT_ERROR_CORRUPT_OR_TRUNCATED_DATA) {
        LOG("ERROR: Failed to load %s!\n", filepath.c_str());
        LOG("\tReason: File is corrupted!\n");
      }
    }

    // If everything checks out
    if (success) {
      // We can now successfully create an AudioBuffer
      AudioBuffer *new_buffer = new AudioBuffer(buffer);

      // Insert the buffer into memory
      m_buffers.insert(std::pair<std::string, AudioBuffer *>(filepath, new_buffer));

      LOG("AudioSystem loaded %s successfully!\n", filepath.c_str());
    }

    return success;
  }

  size_t AudioSystem::GetBufferCount() const {
    return m_buffers.size();
  }

  const AudioBuffer *AudioSystem::GetBufferData(const std::string &filepath) const {
    const AudioBuffer *buffer = nullptr;

    if (m_buffers.find(filepath) != m_buffers.end()) 
      buffer = m_buffers.at(filepath);  // Get handle to the required buffer

    // Return the buffer
    return buffer;
  }

}