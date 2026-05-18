#version 330 core

struct Material{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct Light{
   vec3 pos;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

in vec2 textureCords;
in vec3 normal;
in vec4 fragPos;


uniform vec3 u_CameraPos;
uniform Material material;
uniform Light light;

out vec4 FragColor;

void main(){
   vec4 lightDir = normalize(vec4(light.pos, 1.0) - fragPos);
   float diff = max(dot(lightDir.xyz, normal), 0.0);

   vec3 viewDir = normalize(u_CameraPos - fragPos.xyz);
   vec3 reflectDir = reflect(-lightDir.xyz, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

   vec3 ambient  = light.ambient * material.ambient;
   vec3 diffuse  = light.diffuse * (diff * material.diffuse);
   vec3 specular = light.specular * (spec * material.specular); 

   FragColor = vec4(ambient + diffuse + specular, 1.0);
}