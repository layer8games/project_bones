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
		vec4 texColor = sprite_color * texture(tex, fs_texCoord);
		if(texColor.a < 0.01)
		{
			discard;
		}
		color = texColor;
	}
	else
	{
		if(sprite_color.a < 0.01)
		{
			discard;
		}
		color = sprite_color;
	}
}