#version 330 core

in vec4 position;
uniform mat4 trans;

uniform vec4 ver_in_color;
out vec4 ver_out_color;

void main()
{
    ver_out_color = ver_in_color;
    gl_Position = trans*position ;
}
