#version 150

in vec2 tex_coord;

out vec4 frag_color;

uniform sampler2D sampler;

void main()
{
	frag_color = texture(sampler, tex_coord);
}