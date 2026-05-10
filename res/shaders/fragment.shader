#version 330 core

in vec4 vertexColor;

out vec4 color;
uniform vec4 uColor;

void main(){
   //color = vec4(1.0, 0.0, 0.0, 1.0);
   color = vertexColor;
}