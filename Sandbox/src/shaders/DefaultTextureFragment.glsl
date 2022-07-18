#version 330 core

in vec2 v_TextureCoord;

out vec4 o_Color;

uniform sampler2D u_Texture;

void main()
{
	vec4 textureColor = texture(u_Texture, v_TextureCoord);
	if (textureColor.a < 0.1) discard;
	o_Color = textureColor;
}