#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 v_Normal; // Example: add a normal attribute

uniform mat4 u_MVP;
uniform vec4 u_Color;
uniform float u_TextureOffset; // Offset for sprite animation

void main()
{
    gl_Position = u_MVP * position;
     v_TexCoord = texCoord + vec2(u_TextureOffset, 0.0);
    
    // Example: Compute a fake normal based on vertex position
    v_Normal = vec3(position.x, position.y, position.z);
}