#version 330 core

struct Material{
   sampler2D diffuse_map;
   sampler2D specular_map;
   sampler2D emmision_map;
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

   vec4 ambient  = vec4(light.ambient, 1.0) * texture(material.diffuse_map, textureCords);
   vec4 diffuse  = vec4(light.diffuse, 1.0) * diff * texture(material.diffuse_map, textureCords);
   vec4 specular = vec4(light.specular, 1.0) * spec * texture(material.specular_map, textureCords); 

   FragColor = ambient + diffuse + specular + texture(material.emmision_map, textureCords);
}