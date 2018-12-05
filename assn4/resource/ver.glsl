#version 330 core
in vec4 position;
in vec3 fnormal;
in vec3 normal;
in vec2 tex;

uniform mat4 projection;
uniform mat4 modelview;
uniform vec4 vicolor;


out vec4 vocolor;

void main()
{

    vocolor = vicolor;// * texcoord[0] * texcoord[1];
    gl_Position = projection * modelview * position ;
}
