#version 330 core

in vec2 pass_textureCoords;
in vec3 pass_normal;
in vec3 fragmentPosition;

out vec4 color;

uniform sampler2D diffuseMap0;
uniform vec3 lightPosition;
uniform vec3 lightColour;
uniform vec3 cameraPosition;

const float ambientStrength = 0.1f;
const float specularStrength = 0.8f;

void main()
{
	vec4 objectColour = texture(diffuseMap0, pass_textureCoords);

	vec3 ambient = ambientStrength * lightColour;

	vec3 normalisedNormal = normalize(pass_normal);
	vec3 lightDirection = normalize(lightPosition - fragmentPosition);  
	float difference = max(dot(normalisedNormal, lightDirection), 0.0f);
	vec3 diffuse = difference * lightColour;

	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normalisedNormal);
	float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
	vec3 specular = specularStrength * specularIntensity * lightColour;

	color = vec4((ambient + diffuse + specular), 1.0f) * objectColour;
} 