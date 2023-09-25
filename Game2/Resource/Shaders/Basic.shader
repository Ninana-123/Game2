#shader vertex
#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 v_Position;
uniform mat4 u_MVP;
uniform vec4 u_Color;

void main()
{
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
    v_Position = position;
};

#shader fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Position;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform bool u_RenderTextured; // Flag to indicate rendering with texture or not

void main()
{
    if (u_RenderTextured)
    {
        vec4 texColor = texture(u_Texture, v_TexCoord);
        color = texColor ;
    }
    else
    {
        
        color = u_Color; // Render a basic square with no texture
    }
}
