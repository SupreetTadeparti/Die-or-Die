#include "Text.hpp"

namespace Moon
{
    FT_Library Text::s_Library;
    HashMap<Font, HashMap<Char, Character>> Text::s_Fonts;

	Int Text::Init()
	{
		s_Library;
		if (FT_Init_FreeType(&s_Library))
		{
			MoonLogCritical("Could not initialize FreeType Library");
			return -1;
		}
        return 0;
	}

	Int Text::InitFont(Font font)
	{
		FT_Face face;

		if (FT_New_Face(s_Library, ("./src/fonts/" + font.name + ".ttf").c_str(), 0, &face))
		{
			MoonLogError("Failed to load font " + font.name);
            return -1;
		}

        FT_Set_Pixel_Sizes(face, 0, font.size);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        HashMap<Char, Character> characters;

        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                MoonLogError("Failed to Load Glyph");
                continue;
            }

            Uint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);
            
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };

            characters[c] = character;
        }

        s_Fonts[font] = characters;

        FT_Done_Face(face);

        return 0;
	}

	Text::Text(Int64 x, Int64 y, const String& text, const String& fontName, Uint fontSize)
	{
        Font font = { fontName, fontSize };
        if (s_Fonts.find(font) == s_Fonts.end())
		{
            InitFont(font);
		}

        Model* model = Models::Rect(text, Shader::GenerateDefaultText(), 30.0f, 30.0f);

        for (const Char& c : text)
        {
            Character ch = s_Fonts[font][c];

            Float xpos = x + ch.Bearing.x;
            Float ypos = y - (ch.Size.y - ch.Bearing.y);

            Float w = ch.Size.x;
            Float h = ch.Size.y;

            Entity* entity = new Entity(model, Vec3(xpos, ypos, 0), Vec3(), Vec3(1, -1, 1));
            entity->SetMaterial(new Material(MaterialType::Texture, new Texture(ch.TextureID)));
            m_Characters.push_back(entity);

            x += ch.Advance >> 6;
        }
    }
}