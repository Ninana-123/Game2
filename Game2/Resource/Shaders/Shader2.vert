#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 v_Normal; // Example: add a normal attribute

uniform mat4 u_MVP;
uniform float texCoordX;
uniform float u_FrameWidth;
uniform float u_FrameHeight;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord * vec2(u_FrameWidth, u_FrameHeight) + vec2(texCoordX, 0);
    
    // Example: Compute a fake normal based on vertex position
    v_Normal = vec3(position.x, position.y, position.z);
}