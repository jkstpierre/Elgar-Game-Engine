/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_INSTANCE_COUNTER_HPP_
#define _ELGAR_INSTANCE_COUNTER_HPP_

// INCLUDES //

#include <cstdlib>

namespace elgar {

  /**
   * @brief      An InstanceCounter tracks the number of instantiated objects of a type in memory
   */
  template <typename T>
  class InstanceCounter {
  private:
    static size_t m_count;  // Number of objects in memory

  public:
    /**
     * @brief      Constructs an InstanceCounter
     */
    InstanceCounter() {
      m_count++;
    }

    /**
     * @brief      Destroys an InstanceCounter
     */
    virtual ~InstanceCounter() {
      --m_count;
    }

    /**
     * @brief      Get the number of objects instantiated
     *
     * @return     The number of objects instantiated
     */
    static size_t GetCount() {
      return m_count;
    }
  };

  // Initialize static field
  template <typename T> size_t InstanceCounter<T>::m_count(0);
}

#endif