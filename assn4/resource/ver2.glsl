#version 330 core
in vec4 position;
in vec3 fnormal;
in vec3 normal;
in vec2 tex;

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 normaltrans; // supposed to be rotation only from viewtrans
uniform vec4 vicolor;

out vec3 vnormal;
out vec4 vpos;
out vec2 uv;

void main()
{
    vnormal = normalize(normal);
	uv = tex;
	vpos = modelview * position;
    gl_Position = projection * vpos;
	
}

