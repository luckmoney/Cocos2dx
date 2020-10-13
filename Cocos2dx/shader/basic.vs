#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;


layout (std140) uniform  PerFrameConstants{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    vec4 camPos;
    int  numLights;
};

uniform mat4 view;

out vec3 normal;
out vec2 TexCoords;
out vec4 OcamPos;
out int OnumLights;
out vec3 FragPos;

void main()
{
    FragPos = aPos;
	gl_Position = projectionMatrix*viewMatrix * vec4(aPos, 1.0);
	normal = aNormal;
	TexCoords = aTexCoords;
    OnumLights = numLights;
    OcamPos = camPos;
}
