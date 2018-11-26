#version 330 core

in vec4 vocolor;
in vec2 UV;
// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;

void main()
{

	// Output color
	//color = vocolor;
	color = texture(myTextureSampler, UV);

}
