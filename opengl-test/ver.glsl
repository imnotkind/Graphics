#version 330 core

in vec4 position;
uniform mat4 trans;

void main()
{
    gl_Position = trans*position ;
}
