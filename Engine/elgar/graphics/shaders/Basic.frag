R""(

/*
    Elgar Game Engine
    Author: Joseph St. Pierre
    Year: 2018
*/

/*
    Basic Fragment Shader
*/

#version 430 core       // Target OpenGL 4.3

layout (location = 0) out vec4 fragment_color;        // Output pixel color


// Fragment uniforms
uniform sampler2D   texture_sampler;        // The texture to sample from
uniform bool        use_texture;    // If true, sample from texture
uniform vec4        color;          // RGBA color to use    

// Inputs from vertex shader
in vec2         fragment_uv;        // UV for sampling texture

void main() {
    vec4 texture_color = color;

    // Texture the fragment if flag set
    if (use_texture) 
        texture_color *= texture(texture_sampler, fragment_uv);
    
    // Output color
    fragment_color = texture_color;
} 

)""