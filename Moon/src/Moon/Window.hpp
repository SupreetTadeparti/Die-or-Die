#pragma once

#include "Core.h"

namespace Moon
{
	enum class CursorType
	{
		Normal, Pointer
	};

	class Window
	{
	public:
		MOON_API static Int Init();
		MOON_API static Int Create();
		MOON_API static void Close();
		MOON_API static void Update();

		MOON_API static inline Uint GetWidth() { return s_Width; }
		MOON_API static inline Uint GetHeight() { return s_Height; }

		//   -------------------------------------
		//   |  To be used by Moon Applications  |
		//   -------------------------------------

		MOON_API static void SetBackgroundColor(Float r, Float g, Float b);
		MOON_API static void SetTitle(const String& title);
		MOON_API static void SetDimensions(Uint width, Uint height);
		MOON_API static void SetCursorType(CursorType);
	private:
		MOON_API static const Char* Window::GetKeyName(Int key);
		MOON_API static void KeyCallback(GLFWwindow*, Int, Int, Int, Int);
		MOON_API static void MessageCallback(Uint source, Uint type, Uint id,
			Uint severity, Int length,
			const Char* msg, const void* data);
		MOON_API static void MouseMoveCallback(GLFWwindow*, Double, Double);
		MOON_API static void ClickCallback(GLFWwindow*, Int, Int, Int);
		static GLFWwindow* s_Window;
		static Uint s_Width;
		static Uint s_Height;
		static String s_Title;
		static Vec3 s_BackgroundColor;
	};
}
