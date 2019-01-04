R""(

/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2019
*/

/*
  Text Rendering fragment shader
*/

#version 430 core   // Target OpenGL 4.3

// Fragment attributes
layout (location = 0) out vec4 fragment_color;        // Output pixel color

// Fragment uniforms
uniform sampler2D   texture_sampler;        // The texture to sample from
uniform vec4        color;                  // RGBA color to use    

// Inputs from vertex shader
in vec2         fragment_uv;        // UV for sampling texture

void main() {
  fragment_color = vec4(color.xyz, 1.0) * vec4(1.0, 1.0, 1.0, texture(texture_sampler, fragment_uv).r);
}

)""