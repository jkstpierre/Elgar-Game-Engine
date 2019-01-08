/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

/**
 * @file MeshRenderer.hpp
 * @author Joseph St. Pierre
 * @brief 
 * @version 0.1
 * @date 2019-01-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _ELGAR_MESH_RENDERER_HPP_
#define _ELGAR_MESH_RENDERER_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"
#include "elgar/graphics/data/Mesh.hpp"

#include "elgar/graphics/buffers/VertexArrayObject.hpp"
#include "elgar/graphics/buffers/BufferObject.hpp"
#include "elgar/graphics/data/RGBA.hpp"

// DEFINES //


namespace elgar {

  /**
   * @brief The MeshRenderer class handles the drawing of meshes to the screen
   * 
   */
  class MeshRenderer : public Singleton<MeshRenderer> {
  friend class Engine;    // Allow Engine to instantiate
  private:
    VertexArrayObject m_vao;    // The Mesh VAO
    BufferObject      m_vbo;    // The vertex buffer object
    BufferObject      m_ebo;    // The element array buffer object

  private:
    /**
     * @brief Construct a new MeshRenderer object
     * 
     */
    MeshRenderer();

    /**
     * @brief Destroy the MeshRenderer object
     * 
     */
    virtual ~MeshRenderer();

    /**
     * @brief Helper function for registering mesh data with the GPU
     * 
     * @param mesh The Mesh to register
     */
    void RegisterMesh(const Mesh &mesh) const;

  public:
    /**
     * @brief Draw a Mesh to the screen using a given shader and model matrix
     * 
     * @param mesh    The mesh to draw
     * @param shader  The shader program to draw the mesh with
     * @param color   The color of the mesh
     * @param model   The model matrix to translate mesh by
     */
    void Draw(const Mesh &mesh, const Shader &shader, const RGBA &color, const glm::mat4 &model) const;

    /**
     * @brief Draw a Mesh repeatedly using instanced rendering
     * 
     * @param mesh    The mesh to draw using instanced rendering
     * @param shader  The shader program to use
     * @param color   The colors of the mesh
     * @param models  The set of matrices to use
     */
    void DrawInstanced(const Mesh &mesh, const Shader &shader, const RGBA &color, const std::vector<glm::mat4> &models) const;
    
  };

}

#endif