#pragma once

#include "Core.h"
#include "Models.hpp"
#include "Entity.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H

namespace Moon
{
	struct Character
	{
		Uint TextureID;
		Vec2 Size;
		Vec2 Bearing;
		Int64 Advance;
	};

	struct Font
	{
		String name;
		Uint size;
		bool operator == (const Font& other) const
		{
			return name == other.name && size == other.size;
		}
	};

	class Text
	{
	public:
		MOON_API Text(Int64 x, Int64 y, const String& text, const String& font, Uint fontSize);
		MOON_API inline List<Entity*> const GetCharacters() const { return m_Characters; }
		MOON_API static Int Init();
		MOON_API static Int InitFont(Font font);
	private:
		List<Entity*> m_Characters;
		static FT_Library s_Library;
		static HashMap<Font, HashMap<Char, Character>> s_Fonts;
	};
}

namespace std
{
	template <>
	struct hash<Moon::Font>
	{
		std::size_t operator()(const Moon::Font& f) const
		{
			return ((std::hash<String>()(f.name) ^ (std::hash<Uint>()(f.size) << 1)) >> 1);
		}
	};
}
