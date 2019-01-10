/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

#ifndef _ELGAR_MODEL_LOADER_HPP_
#define _ELGAR_MODEL_LOADER_HPP_

// INCLUDES //

#include "elgar/core/Singleton.hpp"
#include "elgar/graphics/data/Model.hpp"

#include <unordered_map>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace elgar {

  /**
   * @brief The ModelLoader class handles the loading of models from disk using the assimp library (NOTE: This class must be initialized after TextureStorage)
   * 
   */
  class ModelLoader : public Singleton<ModelLoader> {
  friend class Engine;    // Only let Engine instantiate
  private:
    std::unordered_map<std::string, Model*> m_models;  // Set of models in memory
    std::string m_curr_directory;   // The current directory the ModelLoader is loading from

  private:
    /**
     * @brief Construct a new ModelLoader object
     * 
     */
    ModelLoader();

    /**
     * @brief Destroy the ModelLoader object
     * 
     */
    virtual ~ModelLoader();

    /**
     * @brief Builds a new Model from an assimp object
     * 
     * @param node    The node to build model from
     * @param scene   The scene of the model
     * @return        Pointer to new model
     */
    Model *BuildModel(aiNode *node, const aiScene *scene);

    /**
     * @brief Processes an assimp model's node
     * 
     * @param model   The model to build
     * @param node    The node to process
     * @param scene   The scene the node inhabits
     */
    void ProcessNode(Model &model, aiNode *node, const aiScene *scene);

    /**
     * @brief Builds an OpenGL Mesh
     * 
     * @param mesh    The assimp mesh
     * @param scene   The scene the assimp mesh inhabits
     * @return A new OpenGL Mesh
     */
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

    /**
     * @brief Load the textures from a given material
     * 
     * @param material    Reference to the material
     * @param type        The assimp material type
     * @param gl_type     The Elgar3D texture type
     * @return Vector containing const pointers to each texture
     */
    std::vector<const Texture *> LoadMaterialTextures(aiMaterial *material, const aiTextureType &type, const TextureType &gl_type);

  public:
    /**
     * @brief Loads a model from disk or from memory if already loaded
     * 
     * @param path          Path to the model to load
     * @return Const pointer to the requested model, or nullptr if does not exist
     */
    const Model *Load(const std::string &path);

  };

}

#endif