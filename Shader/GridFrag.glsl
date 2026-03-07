#version 330 core

out vec4 FragColor;

uniform vec4 u_Color; // line color

void main()
{
    FragColor = u_Color;
}

