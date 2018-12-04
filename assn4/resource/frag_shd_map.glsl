#version 330 core


// Ouput data
in vec3 vnormal;
in vec4 vpos;
in vec2 uv;


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

out vec4 color;

uniform sampler2D texsam;


mat3 ss(vec3 v)
{
	mat3 m;
	m[0] = vec3(0, -v[2], v[1]);
	m[1] = vec3(v[2], 0, -v[0]);
	m[2] = vec3(-v[1], v[0], 0);
	return m;
}
void main()
{
	color = ambient;

	vec3 samnorm = normalize(texture(texsam, uv).xyz);
	vec3 zv = vec3(0.43446, 0.43446, 0.78898);
	vec3 cv = cross(zv, vnormal);

	mat3 sm = ss(cv);
	mat3 R = mat3(1.0) + sm + sm*sm*(1.0/(1+dot(zv, vnormal)));

	samnorm = mat3(normaltrans)*R*samnorm;

	for(int i = 0; i < 3; i++)
	{
		vec4 xx = light[i].pos[3] == 0 ? light[i].pos : light[i].pos - vpos;
		vec3 L = normalize((xx).xyz); //vector of light
		vec3 E = normalize(-vpos.xyz); //vector of eye (since eye is in origin)
		vec3 R = normalize(-reflect(L,samnorm));
	

		float katt = light[i].pos[3] == 0 ? 1 : 5.0/length(light[i].pos- vpos);

		
		vec4 dif_r = vicolor * katt * max(dot(samnorm,L), 0.0); // NL is negative : backside
		vec4 spc_r = vicolor * katt * pow(max(dot(R,E), 0.0), 0.8);
		color += clamp(dif_r, 0.0, 1.0) + clamp(spc_r, 0.0, 0.5);
	}
	
	color = clamp(color, 0.0, 1.0);
	
	 

}
