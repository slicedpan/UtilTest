#version 330

out float output;
smooth in vec2 fragTexCoord;

uniform vec2 imageSize;
uniform sampler2D baseTex;
uniform float spaceStep;
uniform float timeStep;

float el(float xPos, float yPos)
{
	vec2 tc = vec2(xPos / imageSize.x, yPos / imageSize.y);
	return texture(baseTex, tc).x;
}

void main()
{	
	//out_colour = vec4(1.0, 0.0, 0.0, 1.0);
	float x = fragTexCoord.x * imageSize.x;
	float y = fragTexCoord.y * imageSize.y;
	
	float step = timeStep / (spaceStep * spaceStep);
	
	output = el(x, y) + step * (el(x +1, y) - 4 * el(x, y) + el(x - 1, y) + el(x, y + 1) + el(x, y - 1));	
	
}

