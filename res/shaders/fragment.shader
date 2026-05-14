#version 330 core

in vec4 vertexColor;
in vec2 textureCords;

uniform vec4 uColor;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

out vec4 color;

void main(){
   //color = vec4(1.0, 0.0, 0.0, 1.0);
   vec4 texColor = texture(u_Texture1, textureCords) * texture(u_Texture2, textureCords);
   color = texColor;
}