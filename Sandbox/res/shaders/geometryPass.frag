#version 330 core

struct Material
{
	float usingAlbedoMap;
	float usingGlossMap;
	float usingNormalMap;
	float usingSpecularMap;

	sampler2D albedoMap;
	sampler2D glossMap;
	sampler2D normalMap;
	sampler2D specularMap;

	vec3 albedo;
	vec3 specular;
	float gloss;
};

struct Light
{
	vec3 position;
	vec3 colour;
	vec3 ambient;
};

in vec2 pass_textureCoords;
in vec3 pass_normal;
in vec3 fragmentPosition;

layout (location = 0) out vec3 worldPosOut;
layout (location = 1) out vec3 normalOut;
layout (location = 2) out vec3 albedoOut;
layout (location = 3) out vec3 specularOut;

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;
uniform samplerCube skybox;

void main()
{
	worldPosOut = fragmentPosition;
	normalOut = pass_normal;
	albedoOut = material.albedo * (1.0f - material.usingAlbedoMap) + texture(material.albedoMap, pass_textureCoords).xyz * material.usingAlbedoMap;
	specularOut = material.specular * (1.0f - material.usingSpecularMap) + texture(material.specularMap, pass_textureCoords).xyz * material.usingSpecularMap;
}
