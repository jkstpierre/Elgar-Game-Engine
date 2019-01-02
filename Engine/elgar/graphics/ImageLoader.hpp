/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

#ifndef _ELGAR_IMAGE_LOADER_HPP_
#define _ELGAR_IMAGE_LOADER_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"

#include <unordered_map>
#include <string>

namespace elgar {

  /**
   * @brief The Image struct defines the relevant attributes for image data
   * 
   */
  struct Image {
    unsigned char *data;  // Pixel data
    unsigned int width;   // Width in pixels
    unsigned int height;  // Height in pixels
    unsigned int channels;  // Number of channels
  };

  /**
   * @brief The ImageLoader class handles the loading and storage of image data during
   *        program execution
   * 
   */
  class ImageLoader : public Singleton<ImageLoader> {
  friend class Engine;  // Allow Engine right to instantiate
  private:
    std::unordered_map<std::string, Image> m_images;  // Table of images

  private:
    /**
     * @brief Construct a new ImageLoader object
     * 
     */
    ImageLoader();

    /**
     * @brief Destroy the ImageLoader object
     * 
     */
    virtual ~ImageLoader();

  public:
    /**
     * @brief Loads an image from disk
     * 
     * @param filepath The path to the image on disk
     * @param name The name to store the image data under
     * @return true If load successful
     * @return false If load failed
     */
    bool LoadFromDisk(const std::string &filepath, const std::string &name = "");

    /**
     * @brief Read the image data from memory
     * 
     * @param name The name of the image
     * @return The image data
     */
    Image Read(const std::string &name);

  };

}

#endif