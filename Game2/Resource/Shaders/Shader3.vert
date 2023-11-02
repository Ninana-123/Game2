#version 450 core

layout(location = 0) in vec4 position;
out vec2 v_TexCoord; // Pass texture coordinates to the fragment shader
uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(position.xy, 0.0, 1.0);
    v_TexCoord = position.zw;
}
