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
        Color = Color * lights[i].lightColor;
    }
    FragColor = Color; 
}