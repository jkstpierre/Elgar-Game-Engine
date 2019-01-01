/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

// INCLUDES //

#include "elgar/graphics/ShaderManager.hpp"
#include "elgar/core/Macros.hpp"

#include <fstream>
#include <streambuf>

// STRUCTS //

struct ShaderSource {
  std::string name;
  std::string vertex_code;
  std::string fragment_code;
  std::string geometry_code;
};

// DEFAULT SHADER PROGRAMS //

ShaderSource default_basic_shader = {
  BASIC_SHADER_PROGRAM,
  {
    #include "elgar/graphics/shaders/Basic.vert"
  },
  {
    #include "elgar/graphics/shaders/Basic.frag"
  },
  ""    // NO GEOMETRY SHADER
};

namespace elgar {

  // FUNCTIONS //

  ShaderManager::ShaderManager() : Singleton<ShaderManager>(this) {
    BuildDefaultShaders();  // Build the default shader programs

    LOG("ShaderManager online...\n");
  }

  ShaderManager::~ShaderManager() {
    // Delete all shader programs
    for(auto it = m_shaders.begin(); it != m_shaders.end(); it++) {
      Shader *shader = it->second;

      delete shader;
    }

    m_shaders.clear();

    LOG("ShaderManager offline...\n");
  }

  void ShaderManager::BuildDefaultShaders() {
    LOG("Building shader programs...\n");

    // Create the shader
    Shader *basic_shader = new Shader(
      default_basic_shader.vertex_code.c_str(), 
      default_basic_shader.fragment_code.c_str()
    );

    LOG("Shader %s compiled and linked...\n", default_basic_shader.name.c_str());

    // Add the shader
    m_shaders.insert(std::pair<std::string, Shader *>(default_basic_shader.name, basic_shader));
  }

  bool ShaderManager::CreateShader(
    const std::string &name,
    const std::string &vertex_path, 
    const std::string &fragment_path,
    const std::string &geometry_path
  ) {
    // Check for name collision
    if (m_shaders.find(name) != m_shaders.end()) {
      LOG("ERROR: Shader %s already exists!\n", name.c_str());
      return false;
    }

    // Load sources from disk

    ShaderSource src; // Source struct to read code into

    std::ifstream in_stream;  // Input file stream

    // Open the vertex shader
    in_stream.open(vertex_path);
    if (in_stream.is_open()) {
      src.vertex_code = std::string(
        (std::istreambuf_iterator<char>(in_stream)),
        std::istreambuf_iterator<char>()
      );

      in_stream.close();
    }
    else {
      LOG("ERROR: Failed to open vertex shader %s!\n", vertex_path.c_str());
      return false;
    }

    // Open the fragment shader
    in_stream.open(fragment_path);
    if (in_stream.is_open()) {
      src.fragment_code = std::string(
        (std::istreambuf_iterator<char>(in_stream)),
        std::istreambuf_iterator<char>()
      );

      in_stream.close();
    }
    else {
      LOG("ERROR: Failed to open vertex shader %s!\n", fragment_path.c_str());
      return false;
    }

    // If a geometry shader has been provided
    if (!geometry_path.empty()) {

      // Open the geometry shader
      in_stream.open(geometry_path);
      if (in_stream.is_open()) {
        src.geometry_code = std::string(
          (std::istreambuf_iterator<char>(in_stream)),
          std::istreambuf_iterator<char>()
        );

        in_stream.close();
      }
      else {
        LOG("ERROR: Failed to open geometry shader %s!\n", geometry_path.c_str());
        return false;
      }
    }
    else {
      src.geometry_code = ""; // No geometry code by default
    }

    // Create a new shader program
    Shader *program;

    if (src.geometry_code.empty())
      program = new Shader(src.vertex_code.c_str(), src.fragment_code.c_str());
    else
      program = new Shader(
        src.vertex_code.c_str(), 
        src.fragment_code.c_str(), 
        src.geometry_code.c_str()
      );

    // Add the shader to the shader table
    m_shaders.insert(std::pair<std::string, Shader *>(name, program));

    // Success!
    return true;
  }

  void ShaderManager::DestroyShader(const std::string &name) {
    if (m_shaders.find(name) != m_shaders.end()) {
      delete m_shaders.at(name);
      m_shaders.erase(name);
      LOG("Shader destroyed!\n");
    }
    else {
      LOG("Shader does not exist!\n");
    }
  }

  const Shader *ShaderManager::GetShader(const std::string &name) const {
    if (m_shaders.find(name) != m_shaders.end())
      return m_shaders.at(name);

    return nullptr;
  }
}