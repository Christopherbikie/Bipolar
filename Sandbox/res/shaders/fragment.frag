#version 330 core

in vec2 pass_textureCoords;

out vec4 color;

uniform sampler2D diffuseTexture1;
uniform sampler2D diffuseTexture2;

void main()
{
	color = mix(texture(diffuseTexture1, pass_textureCoords), texture(diffuseTexture2, pass_textureCoords), 0.5f);
} 