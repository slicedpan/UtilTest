#version 330

uniform sampler2D fontTexture;

out vec4 colour;
smooth in vec4 inColour;

smooth in vec2 fragTexCoord;

void main()
{		
	colour = inColour * texture(fontTexture, fragTexCoord).a;
	//colour = inColour;
}