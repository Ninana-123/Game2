#version 450 core

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

// Placeholder declarations to avoid warnings
uniform float texCoordX;
uniform float u_FrameWidth;
uniform float u_FrameHeight;
uniform mat4 u_MVP;
uniform bool u_RenderTextured;
uniform vec4 u_Color;

void main()
{
    gl_Position = vec4(vertex.x, vertex.y, 0.0, 1.0);
    TexCoords = vertex.zw;
}