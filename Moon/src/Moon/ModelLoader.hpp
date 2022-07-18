#pragma once

#include "Core.h"
#include "Model.hpp"

namespace Moon
{
	struct VertexData
	{
		List<Float> Positions;
		List<Float> TextureCoordinates;
		List<Float> Normals;
		List<Uint> Indices;
	};

	class MOON_API ModelLoader
	{
	public:
		static Model* LoadModel(const String& name, Shader* shader, Material* material, const String& file);
		static VertexData LoadOBJ(const String& path);
	private:
		static List<String> SplitString(const String& string, Char delimeter);
	};
}