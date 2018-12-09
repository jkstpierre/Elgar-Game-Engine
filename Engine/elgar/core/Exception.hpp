/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_EXCEPTION_HPP_
#define _ELGAR_EXCEPTION_HPP_

// INCLUDES //

#include <exception>
#include <string>

namespace elgar {

  /**
   * @brief      The Exception class is a generic "catch-all" exception that is thrown during emergencies.
   *             It also serves as a base class for more specific exceptions to inherit from.
   */ 
  class Exception : public std::exception {
  private:
    std::string m_msg;  // The error message for the exception

  public:
    /**
     * @brief      Builds an exception containing an error message
     *
     * @param[in]  message  The error message to store
     */
    Exception(const std::string &message) noexcept;

    /**
     * @brief      Returns the contents of the error message
     *
     * @return     A C-string containing the error message
     */
    const char *what() const noexcept;
  };

}

#endif