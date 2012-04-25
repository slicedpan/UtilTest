#version 330

layout(location=0) in vec2 coord;
layout(location=1) in vec2 texCoord;

uniform int text[256];
uniform int textLength;
uniform vec2 basePosition;
uniform vec4 colour;

void main()
{
	vec2 outPos = basePosition + texCoord.x * gl_InstanceID
}