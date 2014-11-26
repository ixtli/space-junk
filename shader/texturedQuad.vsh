#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 v_pos;
in vec2 v_texCoord;

out vec2 tex_coord;

void main()
{
	tex_coord = v_texCoord;
	gl_Position = modelViewProjectionMatrix * v_pos;
}