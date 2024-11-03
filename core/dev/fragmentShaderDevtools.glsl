#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	sampler2D diffuseMap;
	sampler2D specularMap;
	vec3 specular;
	float dissolve;
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
in vec4 bColor;

out vec4 FragColor;


uniform Material material;
uniform Light light;

uniform sampler2D trippyTexture;
uniform sampler2D containerTexture;
uniform int useTexture = 0;
uniform vec3 lightPos;
uniform vec3 lightColor = vec3(1, 1, 1);
uniform vec3 testColor = vec3(.5, .25, 1);
uniform vec3 viewPos;

void main(){
	//vec3 ambient = light.ambient * vec3(texture(material.diffuseMap, oTexturePos));
		float ambientStrength = 0.1;
		vec3 ambient = material.ambient * (lightColor*0.1);

                // Diffuse
                vec3 norm = normalize(Normal);
                vec3 lightDir = normalize(lightPos - FragPos);
                float diffusion = max(dot(norm, lightDir), 0.0);
                //vec3 diffuse = (material.diffuse*diffusion) * lightColor;
                vec3 diffuse =  material.ambient * (diffusion * lightColor);

		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = (lightColor*spec*0.5);


		vec3 result = (ambient+diffuse+specular);
		if(useTexture == 1){

	                result *= vec3(texture(material.diffuseMap, oTexturePos));
		}else{
	                //FragColor = vec4((ambient + diffuse) * vec3(bColor.x, bColor.y, bColor.z), 1);
			result *= vec3(bColor.x, bColor.y, bColor.z);
		}
		FragColor = vec4(result, material.dissolve);
}
