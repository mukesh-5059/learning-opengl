#version 330 core

layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 acolor;
layout(location = 2) in vec2 atex;

out vec4 vertexColor;
out vec2 textureCords;

void main(){
   textureCords = atex;
   vertexColor = vec4(acolor, 1.0);
   gl_Position = vec4(apos, 1.0);
}