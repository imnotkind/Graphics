#version 330 core

in vec4 position;
in vec2 uv;
uniform mat4 trans;
uniform vec4 vicolor;

out vec4 vocolor;
out vec2 UV;

void main()
{
	vocolor = vicolor;
    gl_Position = trans*position ;
	//UV = position.xy * 0.01;
	UV = uv;
}
