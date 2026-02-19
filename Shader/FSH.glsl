#version 330 core

in vec2 v_UV;

uniform sampler2D u_Texture;  // your MaterialAsset texture
uniform vec4 u_Tint = vec4(1.0); // optional tint color

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(u_Texture, v_UV);
    FragColor = texColor * u_Tint;
}
