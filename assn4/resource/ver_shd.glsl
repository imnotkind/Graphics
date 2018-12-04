#version 330 core
in vec4 position;
in vec3 normal;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 normaltrans; // supposed to be rotation only from viewtrans
uniform vec4 vicolor;

out vec3 vnormal;
out vec4 vpos;

void main()
{
    vnormal = normalize(normaltrans * vec4(normal, 0.0)).xyz;

	vpos = modelview * position;
    gl_Position = projection * vpos;
	
}
