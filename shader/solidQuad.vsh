#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 v_pos;
in vec4 v_color;

out vec4 color;

void main()
{
	color = v_color;
	gl_Position = modelViewProjectionMatrix * v_pos;
}