#version 450 core

layout(location = 0) in vec4 position; // Batched positions
layout(location = 1) in vec2 texCoord; // Batched texture coordinates
layout(location = 2) in vec4 color;    // Batched colors
layout(location = 3) in float texIndex; // Index of texture to be used for each vertex

out vec2 v_TexCoord; // Pass texture coordinates to the fragment shader
out vec4 v_Color;    // Pass color to the fragment shader
out float v_TexIndex;

uniform mat4 u_MVP;
uniform vec4 u_Color;

void main()
{
    v_Color = color;
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;
    gl_Position = u_MVP * position;
}