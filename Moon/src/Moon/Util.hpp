#pragma once

#include "Core.h"

namespace Moon
{
	class MOON_API Util
	{
	public:
		static Int Random(Int start, Int end);
		static std::chrono::milliseconds CurrentTime();
	};
}