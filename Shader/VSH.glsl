#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;

uniform mat4 u_Model;
uniform mat4 u_VP;

out vec2 v_WorldPos;
out vec2 v_UV;

void main(){
    v_UV = vec2(aUV.x, 1.0 - aUV.y);
    gl_Position = u_VP * u_Model * vec4(aPos, 0.0, 1.0);
}
