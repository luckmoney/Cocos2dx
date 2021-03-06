#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;
uniform vec3 viewPos;
uniform Material material;


void main()
{
	//环境光
	vec3 ambient = light.ambient * material.ambient;

	//漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//镜面光
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir ,norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0),material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0);


    // ambient
    // float ambientStrength = 0.1;
    // vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(lightPos - FragPos);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = diff * lightColor;

	// float specularStrength = 0.5;
	// vec3 viewDir = normalize(viewPos - FragPos);
	// vec3 reflectDir = reflect(-lightDir,norm);
	// float spec = pow(max(dot(viewDir,reflectDir),0.0),256);
	// vec3 specular = specularStrength * spec * lightColor;
            
    // vec3 result = (ambient + diffuse + specular) * objectColor;
    // FragColor = vec4(result, 1.0);
} 