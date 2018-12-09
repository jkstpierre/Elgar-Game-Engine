/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_UTILITIES_HPP_
#define _ELGAR_UTILITIES_HPP_

// INCLUDES //

#include <string>

namespace elgar {
  /**
   * @brief      Gets the file extension for a string
   *
   * @param[in]  str   The string to check extension for
   *
   * @return     The file extension of the string.
   */
  std::string getFileExtension(const std::string &str);
  
}

#endif