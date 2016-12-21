#version 330 core

layout (location = 0) in vec2 position;
layout (location = 2) in vec2 textureCoords;

out vec2 pass_textureCoords;

void main()
{
	gl_Position = vec4(position, 0.0f, 1.0f);
	pass_textureCoords = textureCoords;
}