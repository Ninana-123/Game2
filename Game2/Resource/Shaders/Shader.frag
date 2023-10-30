#version 450 core

layout(location = 0) out vec4 fragColor;

in vec4 v_Color;    // Received color from vertex shader
in vec2 v_TexCoord; // Received texture coordinates from vertex shader
in float v_TexIndex; // Received texture index from vertex shader

uniform sampler2D u_Texture[3];
uniform bool u_RenderTextured;

void main()
{
    if (u_RenderTextured)
    {
        int index = int(v_TexIndex);
        fragColor = texture(u_Texture[index], v_TexCoord);
    }
    else
    {
        fragColor = v_Color; // Render a basic square with vertex color
    }
}