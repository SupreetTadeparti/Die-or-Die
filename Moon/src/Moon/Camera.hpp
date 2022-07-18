#pragma once

#include "Core.h"

namespace Moon
{
	class Camera
	{
	public:
		MOON_API Camera();
		MOON_API void Move(Vec3 translation);
		MOON_API void Move(Double x, Double y, Double z);
		MOON_API void Rotate(Vec3 rotation);
		MOON_API void Rotate(Double x, Double y, Double z);
		MOON_API inline Mat4 const GetViewMatrix() const { return m_ViewMatrix; }
	private:
		void UpdateViewMatrix();
		Vec3 m_Rotation;
		Mat4 m_TranslationMatrix;
		Mat4 m_RotationMatrix;
		Mat4 m_ViewMatrix;
	};
}

