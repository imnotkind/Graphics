#version 330 core
in vec4 position;
in vec3 normal;
in vec2 tex;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 normaltrans; // supposed to be rotation only from viewtrans
uniform vec4 vicolor;


struct SLight
{
	vec4 pos;
	vec4 diffuse;
	vec4 specular;
};
uniform vec4 ambient;

uniform SLight light[3];

out vec4 ocolor;

void main()
{
    vec3 vnormal = normalize(normaltrans * vec4(normal, 0.0)).xyz;
	vec4 vpos = modelview * position;
    gl_Position = projection * vpos;

	ocolor = ambient;

	for(int i = 0; i < 3; i++)
	{
		vec4 xx = light[i].pos[3] == 0 ? light[i].pos : light[i].pos - vpos;
		vec3 L = normalize((xx).xyz); //vector of light
		vec3 E = normalize(-vpos.xyz); //vector of eye (since eye is in origin)
		vec3 R = normalize(-reflect(L,vnormal));
	

		float katt = light[i].pos[3] == 0 ? 1 : 5.0/length(light[i].pos- vpos);

		
		vec4 dif_r = vicolor*light[i].diffuse * katt * max(dot(vnormal,L), 0.0); // NL is negative : backside
		vec4 spc_r = vicolor*light[i].specular * katt * pow(max(dot(R,E), 0.0), 0.8);
		ocolor += clamp(dif_r, 0.0, 1.0) + clamp(spc_r, 0.0, 0.5);
	}
	
	ocolor = clamp(ocolor, 0.0, 1.0);
	
}

