/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_MESH_MANAGER_HPP_
#define _ELGAR_MESH_MANAGER_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"
#include "elgar/graphics/data/Mesh.hpp"

#include <unordered_map>

// DEFINES //

#define MESH_MANAGER_BASIC_QUAD   "MM_BASIC_QUAD"     // Default 2D quad
#define MESH_MANAGER_BASIC_CUBE   "MM_BASIC_CUBE"     // Default 3D cube

namespace elgar {

  /**
   * @brief The MeshManager class handles the storage of meshes
   * 
   */
  class MeshManager : public Singleton<MeshManager> {
  friend class Engine;
  private:
    std::unordered_map<std::string, const Mesh *> m_mesh_table;   // The table of meshes in memory

  private:
    /**
     * @brief Construct a new Mesh Manager object
     * 
     */
    MeshManager();

    /**
     * @brief Destroy the Mesh Manager object
     * 
     */
    virtual ~MeshManager();

  public:
    /**
     * @brief         Register a Mesh against a given name
     * 
     * @param mesh    The Mesh to register
     * @return true if mesh successfully registered, false otherwise
     */
    bool Register(const std::string &name, const Mesh *mesh);

    /**
     * @brief Get a Mesh by a given name
     * 
     * @param name          The name of the mesh
     * @return Pointer to the requested Mesh or nullptr if not found 
     */
    const Mesh *GetMesh(const std::string &name) const;
    
  };

}

#endif