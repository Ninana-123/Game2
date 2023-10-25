#version 450 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal; // Example: receive the normal attribute from the vertex shader

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform bool u_RenderTextured;

void main()
{
    // Example: Use the normal attribute in fragment shader logic
    vec3 normal = normalize(v_Normal);
    
    // Example: Apply a simple lighting effect based on the normal
    float lightIntensity = dot(normal, vec3(0.0, 0.0, 1.0)); // Simple directional light along z-axis
    lightIntensity = clamp(lightIntensity, 0.2, 1.0); // Clamp the intensity
    
    vec4 finalColor;
    if (u_RenderTextured)
    {
        vec4 texColor = texture(u_Texture, v_TexCoord);
        finalColor = texColor * vec4(lightIntensity, lightIntensity, lightIntensity, 1.0);
    }
    else
    {
        finalColor = u_Color * vec4(lightIntensity, lightIntensity, lightIntensity, 1.0);
    }

    color = finalColor;
}