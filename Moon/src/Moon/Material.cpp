#include "Material.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace Moon
{
	Material::Material(MaterialType mt, Texture* texture) : m_MaterialType(mt)
	{
		if (mt != MaterialType::Texture)
		{
			MoonLogError("Material Type Does Not Match With Given Material!");
		}
		m_Color = nullptr;
		m_Texture = texture;
	}

	Material::Material(MaterialType mt, Color* color) : m_MaterialType(mt)
	{
		if (mt != MaterialType::Color)
		{
			MoonLogError("Material Type Does Not Match With Given Material");
		}
		m_Color = color;
		m_Texture = nullptr;
	}

	Texture::Texture(Uint textureID) : m_TextureID(textureID)
	{
	}

	Texture::Texture(const String& textureFile) : m_TextureID(0)
	{
		stbi_set_flip_vertically_on_load(1);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(("./src/textures/" + textureFile).c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);

		m_Width = width;
		m_Height = height;

		if (data)
		{
			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else
		{
			MoonLogError("Failed to Load Texture!");
		}

		stbi_image_free(data);
	}

	void Texture::Bind(Uint slot) const
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID); 
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	Color::Color(Vec4 color) : m_Color(Vec4(color.r / 255, color.g / 255, color.b / 255, color.a))
	{
	}

	Color::Color(Float r, Float g, Float b, Float a)
	{
		m_Color = Vec4(r / 255, g / 255, b / 255, a);
	}
}