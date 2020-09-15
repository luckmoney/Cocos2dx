#version 330 core

out vec4 FragColor;

in vec3 TexCoords;
uniform samplerCube  skybox;

void main()
{
    FragColor = vec4(TexCoords,1.0);
    FragColor = texture(skybox, TexCoords,0);
}