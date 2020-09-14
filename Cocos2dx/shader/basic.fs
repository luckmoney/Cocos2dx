#version 330 core
out vec4 FragColor;

in vec4 pos;
in vec3 normal;


void main()
{
    vec3 color = pos.xyz;// * max(dot(pos.xyz,normalize(normal)),0.0); 
    FragColor =  vec4(color,1.0);
}