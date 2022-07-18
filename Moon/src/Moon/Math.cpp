#include "Math.hpp"

namespace Moon
{
	const LongDouble Math::PI = M_PI;

	template <typename T>
	MOON_API Mat4 Math::Perspective(T fov, T aspect, T zNear, T zFar)
	{
		return glm::perspective(fov, aspect, zNear, zFar);
	}

	template <typename T>
	MOON_API Mat4 Math::Ortho(T left, T right, T bottom, T top, T zNear, T zFar)
	{
		return glm::ortho(left, right, bottom, top, zNear, zFar);
	}

	template MOON_API Mat4 Math::Perspective(Int fov, Int aspect, Int zNear, Int zFar);
	template MOON_API Mat4 Math::Perspective(Float fov, Float aspect, Float zNear, Float zFar);
	template MOON_API Mat4 Math::Perspective(Double fov, Double aspect, Double zNear, Double zFar);
	template MOON_API Mat4 Math::Ortho(Int left, Int right, Int bottom, Int top, Int zNear, Int zFar);
	template MOON_API Mat4 Math::Ortho(Float left, Float right, Float bottom, Float top, Float zNear, Float zFar);
	template MOON_API Mat4 Math::Ortho(Double left, Double right, Double bottom, Double top, Double zNear, Double zFar);
}