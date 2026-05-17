#version 330 core

in vec4 vertexColor;
in vec2 textureCords;
in vec3 normal;
in vec4 fragPos;

uniform vec4 uColor;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

uniform vec3 u_LightColor;
uniform float u_AmbientStrength;
uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;
uniform float u_SpecularStrength;

out vec4 FragColor;

void main(){
   vec4 objectcolor = mix(texture(u_Texture1, textureCords), texture(u_Texture2, textureCords), 0.4);

   vec4 lightDir = normalize(vec4(u_LightPos, 1.0) - fragPos);
   float diff = max(dot(lightDir.xyz, normal), 0.0);

   vec3 viewDir = normalize(u_CameraPos - fragPos.xyz);
   vec3 reflectDir = reflect(-lightDir.xyz, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

   vec4 specular = vec4(u_LightColor, 1.0) * spec * u_SpecularStrength;
   vec4 diffuse = vec4(u_LightColor, 1.0) * diff;
   vec4 ambient = vec4(u_LightColor, 1.0) * u_AmbientStrength;
   FragColor = objectcolor * (ambient + diffuse + specular);
}