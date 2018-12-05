#version 330 core


// Ouput data
flat in vec4 ocolor;
out vec4 color;

void main()
{
	color = ocolor;
}
