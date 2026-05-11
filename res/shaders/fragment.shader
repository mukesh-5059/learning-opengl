#version 330 core

in vec4 vertexColor;
in vec2 textureCords;
uniform vec4 uColor;
uniform sampler2D u_Texture;

out vec4 color;

void main(){
   //color = vec4(1.0, 0.0, 0.0, 1.0);
   vec4 texColor = texture(u_Texture, textureCords);
   color = texColor * vertexColor;
}