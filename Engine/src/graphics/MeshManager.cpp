/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/MeshManager.hpp"
#include "elgar/core/Macros.hpp"

namespace elgar {

  // FUNCTIONS // 

  MeshManager::MeshManager() : Singleton<MeshManager>(this) {
    // Create default meshes

    Mesh *basic_2d_quad = new Mesh(
      {
        {
          {-0.5f, -0.5f, 0.0f},   // Bottom left vertex
          {0.0f, 0.0f, 1.0f},     // Normal
          {0.0f, 0.0f}            // UV
        },
        {
          {0.5f, -0.5f, 0.0f},    // Bottom right vertex
          {0.0f, 0.0f, 1.0f},     // Normal
          {1.0f, 0.0f}            // UV
        },
        {
          {0.5f, 0.5f, 0.0f},     // Top right vertex
          {0.0f, 0.0f, 1.0f},     // Normal
          {1.0f, 1.0f}            // UV 
        },
        {
          {-0.5f, 0.5f, 0.0f},    // Top left vertex
          {0.0f, 0.0f, 1.0f},     // Normal
          {0.0f, 1.0f}            // UV
        }
      },
      {
        0, 1, 2, 0, 2, 3          // Element indices
      },         
      {
        // No texture
      }
    );

    Register(MESH_MANAGER_BASIC_QUAD, basic_2d_quad);   // Register the quad

    LOG("MeshManager online...\n");
  }

  MeshManager::~MeshManager() {
    // Delete all the meshes
    for (auto it = m_mesh_table.begin(); it != m_mesh_table.end(); it++) {
      delete it->second;
    }

    LOG("MeshManager offline...\n");
  }

  bool MeshManager::Register(const std::string &name, const Mesh *mesh) {
    if (m_mesh_table.find(name) != m_mesh_table.end()) {
      LOG("Error: Failed to register mesh %s due to name collision!\n", name.c_str());
      return false;
    }

    if (!mesh) {
      LOG("Error: Cannot register null mesh!\n");
      return false;
    }

    // Add the mesh to the table
    m_mesh_table.insert(std::pair<std::string, const Mesh *>(name, mesh));

    return true;
  }

  const Mesh *MeshManager::GetMesh(const std::string &name) const {
    if (m_mesh_table.find(name) == m_mesh_table.end())
      return nullptr;

    return m_mesh_table.at(name);
  }

}