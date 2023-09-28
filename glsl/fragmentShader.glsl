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

	float cutOff;
	float outerCutOff;
};

in vec2 oTexturePos;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


uniform Material material;
uniform Light light;

uniform sampler2D trippyTexture;
uniform sampler2D containerTexture;
uniform int useTexture = 0;
uniform vec3 lightPos;
uniform vec3 viewPos;

/*void main(){
	
	General display of lightings
	if(useTexture == 1){

		// Ambient
		vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, oTexturePos));
		
		// Diffuse
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.direction);
		float diffusion = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diffusion * vec3(texture(material.diffuseMap, oTexturePos));
				
		// Specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specularMap, oTexturePos));


		//float dist = length(light.position - FragPos);
		//float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist*dist));
		//ambient *= attenuation;
		//diffuse *= attenuation;
		//specular *= attenuation;		

		vec3 result = ambient + diffuse + specular;
		FragColor = vec4(result, 1.0);
		//FragColor = mix(texture(trippyTexture, oTexturePos), texture(containerTexture, oTexturePos), 0.50) * vec4(result, 1.0);
	}
}*/

// Flash light example
void main()
{
    vec3 lightDir = normalize(light.position - FragPos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.direction)); 
    
    if(theta > light.cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {    
        // ambient
        vec3 ambient = light.ambient * texture(material.diffuseMap, oTexturePos).rgb;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * texture(material.diffuseMap, oTexturePos).rgb;  
        
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * texture(material.specularMap, oTexturePos).rgb;  
        
        // attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branch
        diffuse   *= attenuation;
        specular *= attenuation;   
            
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
    else 
    {
        // else, use ambient light so scene isn't completely dark outside the spotlight.
        FragColor = vec4(light.ambient * texture(material.diffuseMap, oTexturePos).rgb, 1.0);
    }
} 
