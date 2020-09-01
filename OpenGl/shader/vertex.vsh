#version 330 core
layout(location = 0) in vec3 aPos;   // λ�ñ���������λ��ֵΪ 0 
layout(location = 1) in vec2 aTexCoord;

out vec3 ourColor; // ��Ƭ����ɫ�����һ����ɫ
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}