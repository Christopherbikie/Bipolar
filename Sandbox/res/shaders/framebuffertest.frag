#version 330 core

in vec2 pass_textureCoords;

out vec4 color;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300;

void main()
{
	vec2 offsets[9] = vec2[] (
		vec2(-offset, offset),
		vec2(0.0f,	offset),
		vec2(offset,  offset),
		vec2(-offset, 0.0f),
		vec2(0.0f,	0.0f),
		vec2(offset,  0.0f),
		vec2(-offset, -offset),
		vec2(0.0f,	-offset),
		vec2(offset,  -offset)
	);

	float kernel[9] = float[] (
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1
	);

	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
		sampleTex[i] = vec3(texture(screenTexture, pass_textureCoords.st + offsets[i]));

	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++)
		col += sampleTex[i] * kernel[i];

	color = vec4(col, 1.0);

	//color = texture(screenTexture, pass_textureCoords);
}