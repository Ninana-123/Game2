#version 450 core

layout(location = 0) out vec4 fragColor;
in vec2 v_TexCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 sampled = texture(u_Texture, v_TexCoord);
    fragColor = vec4(u_Color.rgb, 1.0) * sampled;
}
