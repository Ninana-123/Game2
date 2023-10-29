#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord; // Texture coordinates

out vec2 v_TexCoord; // Pass texture coordinates to the fragment shader

uniform mat4 u_MVP;
uniform vec4 u_Color;
uniform float u_TextureOffset; // Offset for sprite animation

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord + vec2(u_TextureOffset, 0.0);
}
