/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/core/Exception.hpp"

namespace elgar {

  // FUNCTIONS // 

  Exception::Exception(const std::string &message) noexcept {
    m_msg = message;  // Store the message
  }

  const char *Exception::what() const noexcept {
    return m_msg.c_str(); // Return message contents as a C-string
  }

}