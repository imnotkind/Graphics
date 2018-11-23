#version 330 core


// Ouput data
in vec3 vnormal;
in vec4 vpos;

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;

uniform vec4 light1;

out vec4 color;

void main()
{

	vec3 L = normalize((light1 - vpos).xyz); //vector of light
	vec3 E = normalize(-vpos); //vector of eye
	vec3 R = normalize(-reflect(L,vnormal));

	vec4 amb_r = ambient;
	vec4 dif_r = diffuse * 

	color = vocolor;

}
