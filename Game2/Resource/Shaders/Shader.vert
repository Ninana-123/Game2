#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord; // Texture coordinates

out vec2 v_TexCoord;                   // Pass texture coordinates to the fragment shader

uniform mat4  u_MVP;
uniform float texCoordX;               // Offset for sprite animation (in terms of frame number)

uniform int   u_BatchSize;             // Number of vertices in the batch
uniform vec2  u_BatchTexCoords[200];   // Adjust the array size based on MAX_BATCH_SIZE

uniform float u_FrameWidth;            // The width of a single frame in texture coordinates
uniform float u_FrameHeight;           // The height of a single frame in texture coordinates

void main()
{
    gl_Position = u_MVP * position;

    // Calculate the texture coordinates for the current vertex in the batch
    vec2 baseTexCoord = u_BatchTexCoords[gl_VertexID % u_BatchSize];
    v_TexCoord = baseTexCoord * vec2(u_FrameWidth, u_FrameHeight) + vec2(texCoordX, 1.0 - texCoord.y);
}