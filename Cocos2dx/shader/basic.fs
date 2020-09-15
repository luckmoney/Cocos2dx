#version 330 core

out vec4 FragColor;

in vec3 normal;

in vec2 TexCoords;

uniform sampler2D texture_diffuse_map;
uniform sampler2D texture_normal_map;
uniform sampler2D texture_metallic_map;


void main()
{
    FragColor = texture(texture_diffuse_map,TexCoords);
}