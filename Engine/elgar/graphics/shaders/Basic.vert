R""(

/*
    Elgar Game Engine
    Author: Joseph St. Pierre
    Year: 2018
*/

/*
    Basic Vertex Shader
*/

#version 430 core   // Target OpenGL 4.3

layout (location = 0) in vec3 vertex_pos;           // The position of the vertex
layout (location = 1) in vec2 vertex_uv;            // The texture uv for the vertex
layout (location = 2) in mat4 vertex_model_matrix;  // The model matrix (for instancing only)

// Vertex uniforms
uniform mat4 projection_matrix;     // Screen specifications 
uniform mat4 view_matrix;           // Camera translations / rotations
uniform mat4 model_matrix;          // Model translations / rotations
uniform bool use_instancing;        // Are we instance rendering?

// Output to fragment shader
out vec3 fragment_normal;
out vec2 fragment_uv;

void main() {
    mat4 model = model_matrix;
    if (use_instancing)
        model = vertex_model_matrix;

    // Compute vertex position
    gl_Position = projection_matrix * view_matrix * model * vec4(vertex_pos, 1.0); 

    // Send the uvs to the fragment
    fragment_uv = vertex_uv;
}

)""