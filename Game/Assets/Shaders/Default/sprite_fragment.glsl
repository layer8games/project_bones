#version 430 core

in vec2 fs_texCoord;

uniform sampler2D tex;
uniform bool has_texture;
uniform vec4 sprite_color;

out vec4 color;

void main()
{
	if(has_texture) 
	{
		color = sprite_color * texture(tex, fs_texCoord);
	}
	else
	{
		color = sprite_color;
	}
}