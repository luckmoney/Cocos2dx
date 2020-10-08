#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec2 TexCoords;
in vec4 OcamPos;
in vec3 FragPos;

uniform sampler2D texture_diffuse_map;
uniform sampler2D texture_normal_map;
uniform sampler2D texture_metallic_map;


struct Light{
    int type;
    float intensity;
    int CurveType;
    int lightCastShadow;
    vec4 lightPos;
    vec4 lightColor;
    vec4 lightDirection;
    vec4 lightDistAttenCurveParams[2];
}; 


const int MaxLights = 10;
layout (std140) uniform  LightInfo{
	Light lights[MaxLights];
};

void main()
{
    vec4 Color = texture(texture_diffuse_map,TexCoords);  
    for(int i = 0; i < 2; i++){
        vec4 LightColor = lights[i].lightColor;
        vec4 lightPos = lights[i].lightPos;

        float ambient = 0.5;
        vec4 ambientColor = ambient * LightColor;

        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(lightPos.xyz - FragPos.xyz);
        float diff = max(dot(norm,lightDir),0.0);
        vec4 diffuseColor = diff *LightColor;

        float specular = 0.5;
        vec3 viewDir = normalize(OcamPos.xyz - FragPos.xyz);
        vec3 reflectDir = reflect(-lightDir,norm);
        float spec = pow(max(dot(OcamPos.xyz,reflectDir),0.0),32);
        vec4 specularColor = specular *spec *LightColor;

        Color = Color * (ambientColor + diffuseColor + specularColor);
    }
    FragColor = Color; 
}