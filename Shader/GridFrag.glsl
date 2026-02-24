#version 330 core
out vec4 FragColor;

uniform vec3 u_GridColor = vec3(0.5,0.5,0.5); // grey lines

void main()
{
    FragColor = vec4(u_GridColor, 1.0);
}
