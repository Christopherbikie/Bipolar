#version 330 core

in vec2 pass_textureCoords;

out vec4 color;

uniform sampler2D diffuseMap0;

void main()
{
	color = texture(diffuseMap0, pass_textureCoords);
} 