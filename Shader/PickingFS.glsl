#version 330 core
uniform vec3 u_IDColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(u_IDColor, 1.0);
}
