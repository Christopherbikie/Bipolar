#version 330 core

struct Material
{
	sampler2D diffuseMap;
	sampler2D specularMap;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

	bool useSpecMap;
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

void main()
{
	vec3 diffuseColour = texture(material.diffuseMap, pass_textureCoords).xyz * material.diffuse;
	vec3 specularColour;
	if (material.useSpecMap)
		specularColour = texture(material.specularMap, pass_textureCoords).xyz * material.specular;
	else
		specularColour = material.specular;

	vec3 ambient = light.ambient * diffuseColour;

	vec3 normalisedNormal = normalize(pass_normal);
	vec3 lightDirection = normalize(light.position - fragmentPosition);  
	float diffuseIntensity = max(dot(normalisedNormal, lightDirection), 0.0f);
	vec3 diffuse = diffuseIntensity * light.colour * diffuseColour;

	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalisedNormal);
	float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess / 16);
	vec3 specular = specularIntensity * light.colour * specularColour;

	color = vec4(ambient + diffuse + specular, 1.0f);
} 