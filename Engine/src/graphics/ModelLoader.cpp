/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

// INCLUDES //

#include "elgar/graphics/ModelLoader.hpp"
#include "elgar/core/Macros.hpp"

namespace elgar {

  // FUNCTIONS //

  ModelLoader::ModelLoader() : Singleton<ModelLoader>(this) {
    LOG("ModelLoader online...\n");
  }

  ModelLoader::~ModelLoader() {
    // Destroy all models
    for (auto it = m_models.begin(); it != m_models.end(); it++) {
      delete it->second;
    }

    m_models.clear();

    LOG("ModelLoader offline...\n");
  }

  const Model *ModelLoader::Load(const std::string &path) {
    if (m_models.find(path) != m_models.end())
      return m_models.at(path);

    static Assimp::Importer import;   // Assimp importer
    
    // Read file contents
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // Check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      LOG("ERROR: Failed to load model %s from disk! Error: %s\n", path.c_str(), import.GetErrorString());
      return nullptr;   // Failed to load model
    }

    // Build our model
    Model *new_model = BuildModel(scene->mRootNode, scene); 

    // Add the model to memory
    m_models.insert(std::pair<std::string, Model *>(path, new_model));

    // Return the model
    return new_model;
  }

  Model *ModelLoader::BuildModel(aiNode *node, const aiScene *scene) {
    Model *model = new Model(); // Build a new model

    ProcessNode(*model, node, scene);

    // Return the model
    return model;
  }

  void ModelLoader::ProcessNode(Model &model, aiNode *node, const aiScene *scene) {
    // Process all meshes of the node
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      model.m_meshes.push_back(ProcessMesh(mesh, scene));
    }

    // Process all meshes of each child
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
      ProcessNode(model, node->mChildren[i], scene);
    }
  }

  Mesh ModelLoader::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<const Texture *> textures;

    // Process the mesh

    // Process each vertex
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      Vertex vertex;

      // Positions
      vertex.pos.x = mesh->mVertices[i].x;
      vertex.pos.y = mesh->mVertices[i].y;
      vertex.pos.z = mesh->mVertices[i].z;

      // Normals
      vertex.normal.x = mesh->mNormals[i].x;
      vertex.normal.y = mesh->mNormals[i].y;
      vertex.normal.z = mesh->mNormals[i].z;

      // Texture coordinates
      if (mesh->mTextureCoords[0]) {
        vertex.uv.x = mesh->mTextureCoords[0][i].x;
        vertex.uv.y = mesh->mTextureCoords[0][i].y;
      }
      else
        vertex.uv = glm::vec2(0.0f, 0.0f);

      // TODO: Handle tangent and bitangent
    }

    // Process each index
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace &face = mesh->mFaces[i];

      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }

    // TODO: Handle materials loading

    return Mesh(vertices, indices, textures);
  }

}