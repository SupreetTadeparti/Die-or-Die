#pragma once

#include "Core.h"
#include "Model.hpp"

namespace Moon
{
	class Entity
	{
	public:
		MOON_API Entity(Model* model, Vec3 translation=Vec3(0.0f), Vec3 rotation=Vec3(0.0f), Vec3 scale=Vec3(1.0f));
		MOON_API void Translate(Vec3 translation);
		MOON_API void Rotate(Vec3 rotation);
		MOON_API void Scale(Vec3 scale);
		MOON_API void SetMaterial(Material* material);
		MOON_API inline Vec3 const GetTranslation() const { return m_Translation; }
		MOON_API inline Material* const GetMaterial() const { return m_Material; }
		MOON_API inline Mat4 const GetModelMatrix() const { return m_ModelMatrix; }
		MOON_API inline Model* const GetModel() const { return m_Model; }
	private:
		void UpdateModelMatrix();
		Vec3 m_Translation;
		Vec3 m_Rotation;
		Vec3 m_Scale;
		Material* m_Material;
		Model* m_Model;
		Mat4 m_ModelMatrix;
	};
}
