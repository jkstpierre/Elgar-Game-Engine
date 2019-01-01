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

layout (location = 0) in vec3 vertex_pos;       // The position of the vertex
layout (location = 1) in vec2 vertex_uv;        // The texture uv for the vertex

// Vertex uniforms
uniform mat4 projection_matrix;     // Screen specifications 
uniform mat4 view_matrix;           // Camera translations / rotations
uniform mat4 model_matrix;          // Model translations / rotations

// Output to fragment shader
out vec3 fragment_normal;
out vec2 fragment_uv;

void main() {
    gl_Position = model_matrix * vec4(vertex_pos, 1.0); // Compute vertex position
    
    // Send the uvs to the fragment
    fragment_uv = vertex_uv;
}

)""