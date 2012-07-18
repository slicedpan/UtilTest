#version 330

layout(location=0) in vec2 coord;
layout(location=1) in vec2 texCoord;

const int masks[4] = int[4] (0x000000ff,  0x0000ff00, 0x00ff0000, 0xff000000);

uniform vec2 basePosition;
uniform vec4 colour = vec4(1.0, 0.0, 0.0, 1.0);
uniform vec2 screenSize;
uniform int text[64];

smooth out vec4 inColour;
smooth out vec2 fragTexCoord;

void main()
{
	inColour = colour;
	vec2 outPos = basePosition + vec2(gl_InstanceID * 16 + (16 * texCoord.x), texCoord.y * -32);	
	outPos /= screenSize;
	//pick out character
	
	int arrayPos = gl_InstanceID / 4;

	int character = (text[arrayPos] & masks[gl_InstanceID % 4]) >> (8 * (gl_InstanceID % 4));	

	//character = 70 + gl_InstanceID;
	
	fragTexCoord = vec2((texCoord.x + character) / 256.0, texCoord.y);;
	//fragTexCoord = vec2(texCoord.x / 64, texCoord.y);
	
	
	
	gl_Position = vec4(outPos.x, outPos.y, 0.0, 1.0);
}