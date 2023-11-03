#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord; // Texture coordinates

out vec2 v_TexCoord; // Pass texture coordinates to the fragment shader

uniform mat4 u_MVP;
uniform float texCoordX; // Offset for sprite animation (in terms of frame number)

uniform float u_FrameCount; // The total number of frames
uniform float u_FrameWidth; // The width of a single frame in texture coordinates
uniform float u_FrameHeight; // The width of a single frame in texture coordinates

void main()
{
    gl_Position = u_MVP * position;

    // Calculate the current frame based on texCoordX
  
    float frameStart = texCoordX ;
    float frameEnd = texCoordX + u_FrameWidth;

    // Calculate the texture coordinates for the current frame
    v_TexCoord = texCoord * vec2(u_FrameWidth, u_FrameHeight) + vec2(texCoordX, 0);
    
}