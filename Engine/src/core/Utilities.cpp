/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/core/Utilities.hpp"

namespace elgar {

  // FUNCTIONS //

  std::string getFileExtension(const std::string &str) {
    size_t i = str.rfind('.', str.length());

    if (i != std::string::npos) {
      return (str.substr(i + 1, str.length() - i));
    }

    return ("");
  }

}