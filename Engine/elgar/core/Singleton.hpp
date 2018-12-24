/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_SINGLETON_HPP_
#define _ELGAR_SINGLETON_HPP_

// INCLUDES //

#include "elgar/core/Exception.hpp"

namespace elgar {

  /**
   * @brief      The Singleton class is a simple base class for objects that can only be
   *             instantiated once.
   *
   * @tparam     T     { description }
   */
  template<typename T>
  class Singleton {
  private:
    static T *m_instance;  // The singleton instance

  public:
    /**
     * @brief      Builds new singleton instance
     */
    Singleton(T *instance) {
      // If singleton has already been instantiated
      if (m_instance) {
        throw Exception("ERROR: Cannot have multiple instances of singleton class!");
      }

      m_instance = instance;  // Set the instance
    };

    /**
     * @brief      Destroys the singleton instance
     */
    virtual ~Singleton() {
      m_instance = nullptr; // Nullify the static reference
    };

    /**
     * @brief      Returns a handle to the Singleton instance
     *
     * @return     The Singleton instance or nullptr if not initialized
     */
    static T *GetInstance() {
      return m_instance;
    };

    /**
     * @brief      Sets the Singleton instance
     *
     * @param      instance  The instance to set
     */
    static void SetInstance(T *instance) {
      if (!m_instance)
        m_instance = instance;
    };

  };

  // STATIC FIELD //

  template<typename T> T *Singleton<T>::m_instance = nullptr;  // Uninitialized to begin with

}

#endif