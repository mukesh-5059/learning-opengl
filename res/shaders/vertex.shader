#version 330 core

layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 acolor;

out vec4 vertexColor;

void main(){
   vertexColor = vec4(acolor, 1.0);
   gl_Position = vec4(apos, 1.0);
}