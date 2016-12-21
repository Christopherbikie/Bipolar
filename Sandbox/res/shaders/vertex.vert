#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoords;

out vec2 pass_textureCoords;
out vec3 pass_normal;
out vec3 fragmentPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	pass_textureCoords = textureCoords;
	fragmentPosition = (model * vec4(position, 1.0f)).xyz;
	pass_normal = normal;
}