#version 330 core
struct Material{
        vec3 ambient;
        vec3 diffuse;
        sampler2D diffuseMap;
        sampler2D specularMap;
        vec3 specular;
        float shininess;
};

struct Light{
        vec3 position;
        vec3 direction;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
	float constant;
        float linear;
        float quadratic;
};

in vec2 GTexturePos;
in vec3 Normalized;
in vec3 FragPos;

out vec4 FragColor;

uniform Material material;
uniform Light light;

uniform sampler2D cobbleTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
	vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, GTexturePos));	
	
	vec3 norm = normalize(Normalized);
        vec3 lightDir = normalize(light.position-FragPos);
        float diffusion = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diffusion * vec3(texture(material.diffuseMap, GTexturePos));

	vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture(material.diffuseMap, GTexturePos));

	float dist = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist*dist));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
	
	vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
}
