#version 330 core

layout(location = 0) in vec3 apos;
layout(location = 1) in vec3 anormal;
layout(location = 2) in vec2 atex;

uniform mat4 u_MVP;
uniform mat4 u_ModelMatrix;
uniform mat4 u_LookAt;

out vec2 textureCords;
out vec3 normal;
out vec4 fragPos;

void main(){
   textureCords = atex;
   normal = mat3(transpose(inverse(u_ModelMatrix))) * anormal;
   fragPos = u_ModelMatrix * vec4(apos, 1.0);
   gl_Position = u_MVP * u_LookAt * fragPos;
}