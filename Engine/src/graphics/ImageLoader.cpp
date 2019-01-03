/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

// INCLUDES //

#include "elgar/graphics/ImageLoader.hpp"
#include "elgar/core/Macros.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "elgar/graphics/aux/stb_image.h"

namespace elgar {

  // FUNCTIONS //
  
  ImageLoader::ImageLoader() : Singleton<ImageLoader>(this) {
    LOG("ImageLoader online...\n");
  }

  ImageLoader::~ImageLoader() {
    // Delete all images
    for (auto it = m_images.begin(); it != m_images.end(); it++) {
      stbi_image_free(it->second.data);   // Free the image data
    }

    m_images.clear();

    LOG("ImageLoader offline...\n");
  }

  bool ImageLoader::LoadFromDisk(const std::string &filepath, const std::string &name) {
    // Check for naming collision
    if (name.empty() && m_images.find(filepath) != m_images.end()) {
      LOG("ERROR: Image already loaded in memory under the name: %s\n", filepath.c_str());
      return false;
    }
    else if (!name.empty() && m_images.find(name) != m_images.end()) {
      LOG("ERROR: Image already loaded in memory under the name: %s\n", name.c_str());
      return false;
    }

    Image new_image;  // The new image struct to load data into

    stbi_set_flip_vertically_on_load(true); // Flip image vertically

    // Read the byte data into the Image struct
    new_image.data = stbi_load(filepath.c_str(), &new_image.width, &new_image.height, &new_image.channels, 0);
    if (!new_image.data) {
      LOG("ERROR: Failed to load texture %s from disk!\n", filepath.c_str());
      return false;
    }

    if (new_image.channels != 3 && new_image.channels != 4) {
      LOG("ERROR: Unsupported image format!\n");
      return false;
    }

    // Generate image name
    std::string image_name = name;

    // Use default name
    if (name.empty())
      image_name = filepath;

    // Add the image into the table
    m_images.insert(std::pair<std::string, Image>(image_name, new_image));

    return true;
  }

  const Image *ImageLoader::Read(const std::string &name) const {
    if (m_images.find(name) != m_images.end())
      return &m_images.at(name);

    return nullptr;
  }
}