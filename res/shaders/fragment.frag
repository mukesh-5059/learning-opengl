#version 330 core

in vec4 vertexColor;
in vec2 textureCords;

uniform vec4 uColor;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

out vec4 FragColor;

void main(){
   vec4 texColor = mix(texture(u_Texture1, textureCords), texture(u_Texture2, textureCords), 0.4);
   FragColor = texColor;
}