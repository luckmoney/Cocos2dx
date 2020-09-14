#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 view;

out vec4 pos;
out vec3 normal;

void main()
{
	gl_Position = view * vec4(aPos, 1.0);
	pos = gl_Position;
	normal = aNormal;
}
