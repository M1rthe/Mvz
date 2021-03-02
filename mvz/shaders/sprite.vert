#version 120

attribute vec3 vertexPosition;
attribute vec2 vertexUV;
attribute vec3 spritePosition; //test

varying vec2 UV;

uniform mat4 MVP;
uniform vec2 UVoffset;

void main()
{
	gl_Position = MVP * vec4(vertexPosition + spritePosition, 1);
	UV = vertexUV + UVoffset;
}
