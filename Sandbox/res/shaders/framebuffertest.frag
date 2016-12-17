#version 330 core

in vec2 pass_textureCoords;

out vec4 color;
//layout(location = 0) out vec3 color;

uniform sampler2D screenTexture;

void main()
{
	color = texture(screenTexture, pass_textureCoords);
}