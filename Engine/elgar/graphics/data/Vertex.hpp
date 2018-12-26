/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_VERTEX_HPP_
#define _ELGAR_VERTEX_HPP_

// INCLUDES //

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "elgar/graphics/data/RGBA.hpp"

namespace elgar {

  /**
   * @brief      A Vertex is a point in 3D space used for constructing polygons
   */
  class Vertex {
  private:
    glm::vec3 m_position;     // The 3D coordinate of the vertex
    glm::vec2 m_tex_coords;   // The 2D texture coordinates of the vertex
    RGBA m_color;             // The color of the vertex

  public:
    /**
     * @brief      Creates a new Vertex
     *
     * @param[in]  position        The position of the Vertex in 3D space
     * @param[in]  texture_coords  The texture coordinates
     * @param[in]  color           The color of the vertex
     */
    Vertex(const glm::vec3 &position, const glm::vec2 &texture_coords, const RGBA &color);

    /**
     * @brief      Destroys the Vertex
     */
    virtual ~Vertex();

    /**
     * @brief      Get the 3D position of the Vertex
     *
     * @return     The position.
     */
    const glm::vec3 &GetPosition() const;

    /**
     * @brief      Get the UV texture coords of the Vertex
     *
     * @return     The uv.
     */
    const glm::vec2 &GetUV() const;

    /**
     * @brief      Get the color of the Vertex
     *
     * @return     The color.
     */
    const RGBA &GetColor() const;

    /**
     * @brief Set the Position of the Vertex
     * 
     * @param position The position to set
     */
    void SetPosition(const glm::vec3 &position);

    /**
     * @brief Set the UV texture coordinates of the Vertex
     * 
     * @param uv The vertex coordinates
     */
    void SetUV(const glm::vec2 &uv);

    /**
     * @brief Set the RGBA color of the Vertex
     * 
     * @param color The color of the vertex
     */
    void SetColor(const RGBA &color);

    /**
     * @brief Set the vertex equal to another vertex
     * 
     * @param vertex The vertex to equal with
     * @return An updated reference of the Vertex
     */
    Vertex &operator =(const Vertex &vertex);
  };

};

#endif