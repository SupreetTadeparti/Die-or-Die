#pragma once

#include "Core.h"

namespace Moon
{
	class Math
	{
	public:
		static const LongDouble PI;
		template <typename T>
		static MOON_API Mat4 Perspective(T fov, T aspect, T zNear, T zFar);
		template <typename T>
		static MOON_API Mat4 Ortho(T left, T right, T bottom, T top, T zNear, T zfar);
	};
}