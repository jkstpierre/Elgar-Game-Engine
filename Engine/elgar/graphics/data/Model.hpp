/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_MODEL_HPP_
#define _ELGAR_MODEL_HPP_

// INCLUDES //

#include "elgar/graphics/data/Mesh.hpp"
#include "elgar/graphics/TextureStorage.hpp"

#include <string>

namespace elgar {

  /**
   * @brief The Model struct contains a collection of Mesh's that compose a single 3D model
   * 
   */
  class Model {
  friend class ModelLoader;   // Give ModelLoader access to private members
  private:
    std::vector<Mesh> m_meshes;   // The meshes of the model

  public:
    /**
     * @brief Construct a new Model object
     * 
     */
    Model();

    /**
     * @brief Destroy the Model object
     * 
     */
    virtual ~Model();

  };
  
}

#endif