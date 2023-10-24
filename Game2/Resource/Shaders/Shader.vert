#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord; //texture coordinates

out vec2 v_TexCoord; //pass texture coordinates to the fragment shader

uniform mat4 u_MVP;
uniform vec4 u_Color;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
};