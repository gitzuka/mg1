#version 330 core

out vec4 FragColor;

//uniform vec3 diffuse;
//uniform vec3 ambient;
//uniform vec3 specular;
//uniform float shininess;

in vec3 vNormal;
in vec3 vFragPos;
in vec3 vColor;   // extra in variable, since we need the light position in view space we calculate this in the vertex shader
in vec2 vTexCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;
//uniform vec3 objectColor;
uniform sampler2D texture;

void main()
{
	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * vColor;

	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(lightPos - vFragPos);  

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;	

	vec3 result = (ambient + diffuse) * vColor;
	//FragColor = vec4(result, 1);
	FragColor = texture2D(texture, vTexCoord) * vec4(result, 1);
	//FragColor = texture2D(texture, vTexCoord);
}