#pragma once

#include "Core.h"
#include "Model.hpp"

namespace Moon
{
	class Models
	{
	public:
		MOON_API static Model* Rect(const String& name, Float width, Float height);
		MOON_API static Model* Rect(const String& name, Material* material, Float width, Float height);
		MOON_API static Model* Rect(const String& name, Shader* shader, Float width, Float height);
		MOON_API static Model* Rect(const String& name, Shader* shader, Material* material, Float width, Float height);
		MOON_API static Model* Box(const String& name, Float width, Float length, Float height);
		MOON_API static Model* Box(const String& name, Material* color, Float width, Float length, Float height);									 
		MOON_API static Model* Box(const String& name, Shader* shader, Float width, Float length, Float height);
		MOON_API static Model* Box(const String& name, Shader* shader, Material* color, Float width, Float length, Float height);
	};
}
