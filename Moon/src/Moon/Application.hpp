#pragma once

#include "Core.h"

namespace Moon
{
	class MOON_API Application
	{
	public:
		virtual void OnStart() {};
		virtual void OnUpdate() {};
		void Run();
		void Close();
	};

	Application* CreateApplication();
}
