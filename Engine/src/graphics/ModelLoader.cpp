/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

// INCLUDES //

#include "elgar/graphics/ModelLoader.hpp"
#include "elgar/core/Macros.hpp"
#include "elgar/graphics/TextureStorage.hpp"
#include "elgar/graphics/ImageLoader.hpp"
#include "elgar/core/Exception.hpp"

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

    // Set the current directory
    m_curr_directory = path.substr(0, path.find_last_of('/'));

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

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];   // Grab pointer to material

    // Get diffuse maps
    std::vector<const Texture *> diffuse_maps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TEXTURE_DIFFUSE);
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

    // Get specular maps
    std::vector<const Texture *> specular_maps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TEXTURE_SPECULAR);
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

    // Get normal maps
    std::vector<const Texture *> normal_maps = LoadMaterialTextures(material, aiTextureType_HEIGHT, TEXTURE_HEIGHT);
    textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());

    // Get height maps
    std::vector<const Texture *> height_maps = LoadMaterialTextures(material, aiTextureType_AMBIENT, TEXTURE_AMBIENT);
    textures.insert(textures.end(), height_maps.begin(), height_maps.end());

    // Build the mesh and return it
    return Mesh(vertices, indices, textures);
  }

  std::vector<const Texture *> ModelLoader::LoadMaterialTextures(aiMaterial *material, const aiTextureType &type, const TextureType &gl_type) {
    std::vector<const Texture *> textures;
    TextureStorage *texture_storage = TextureStorage::GetInstance();
    ImageLoader *image_loader = ImageLoader::GetInstance();

    // If texture storage has not been setup!
    if (!texture_storage) {
      throw Exception("ERROR: ModelLoader attempted to load a model prior to TextureStorage class initialization!");
    }

    // If image loader has not been setup!
    if (!image_loader) {
      throw Exception("ERROR: ModelLoader attempted to load a model prior to ImageLoader class initialization!");
    }

    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
      aiString str;   
      material->GetTexture(type, i, &str);    // Get the name of the texture

      // Build absolute path to texture
      std::string path = m_curr_directory + '/' + std::string(str.C_Str());

      const Texture *tex = texture_storage->Load(path); // Attempt to load texture from memory
      if (tex) {
        textures.push_back(tex);    // Add texture
      }
      else {
        // Create a new image
        if (!image_loader->LoadFromDisk(path)) {
          throw Exception("ERROR: ImageLoader failed to load image " + path + " for ModelLoader!");
        }

        const Image *image = image_loader->Read(path);  // Get the new image
        if (!image) {
          throw Exception("ERROR: ImageLoader failed to retrieve image " + path + " for ModelLoader!");
        }

        // Create new texture
        const Texture *new_texture = new Texture(*image, gl_type, {GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR});

        // Save the texture to the texture storage
        texture_storage->Save(path, new_texture);

        // Add the texture
        textures.push_back(new_texture);
      }
    }

    // Return the material textures
    return textures;
  }

}