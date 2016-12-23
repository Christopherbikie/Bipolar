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

out vec4 color;

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;
uniform samplerCube skybox;

void main()
{
	// Get albedo, specular and gloss values from texture if they exist, otherwise from their vec3 / float
	vec3 albedoColour = material.albedo * (1.0f - material.usingAlbedoMap) + texture(material.albedoMap, pass_textureCoords).xyz * material.usingAlbedoMap;
	vec3 specularColour = material.specular * (1.0f - material.usingSpecularMap) + texture(material.specularMap, pass_textureCoords).xyz * material.usingSpecularMap;
	float gloss = material.gloss * (1.0f - material.usingGlossMap) + texture(material.glossMap, pass_textureCoords).x * material.usingGlossMap;

	vec3 ambient = light.ambient * albedoColour;

	vec3 normalisedNormal = normalize(pass_normal);
	vec3 lightDirection = normalize(light.position - fragmentPosition);
	float albedoIntensity = max(dot(normalisedNormal, lightDirection), 0.0f);
	vec3 albedo = albedoIntensity * light.colour * albedoColour;

	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalisedNormal);
	float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 20); // <- Random constant, will fix
	vec3 incomingDirection = fragmentPosition - cameraPosition;
	vec3 reflection = reflect(incomingDirection, pass_normal);
	vec3 reflectionColor = texture(skybox, reflection).xyz * specularColour;

	vec3 specular = specularIntensity * light.colour * specularColour;

	color = vec4(ambient + albedo + specular/* + reflectionColor*/, 1.0f);
}
