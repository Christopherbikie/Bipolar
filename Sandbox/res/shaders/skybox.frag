#version 330 core

in vec3 pass_textureCoords;

out vec4 color;

uniform samplerCube skybox;

void main()
{    
    color = texture(skybox, pass_textureCoords);
}