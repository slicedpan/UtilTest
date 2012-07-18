#version 330

out float out_colour;
smooth in vec2 fragTexCoord;

uniform vec2 pixSize;
uniform sampler2D baseTex;

void main()
{	
	//out_colour = vec4(1.0, 0.0, 0.0, 1.0);
	out_colour = length(texture(baseTex, fragTexCoord).rgb);	
}

