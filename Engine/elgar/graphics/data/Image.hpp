/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

#ifndef _ELGAR_IMAGE_HPP_
#define _ELGAR_IMAGE_HPP_

namespace elgar {

  /**
   * @brief The Image struct defines the relevant attributes for image data
   * 
   */
  struct Image {
    unsigned char *data;  // Pixel data
    int width;   // Width in pixels
    int height;  // Height in pixels
    int channels;  // Number of channels
  };

}

#endif