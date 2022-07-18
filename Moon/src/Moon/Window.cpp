#include "Window.hpp"
#include "Renderer.hpp"

namespace Moon
{
	GLFWwindow* Window::s_Window;
	Uint Window::s_Width = 640;
	Uint Window::s_Height = 360;
	String Window::s_Title = "Moon Application";
	Vec3 Window::s_BackgroundColor(0, 0, 0);

	Int Window::Init()
	{
		if (!glfwInit())
		{
			return -1;
		}
		return 0;
	}

	const Char* Window::GetKeyName(Int key) {
		const Char* str = glfwGetKeyName(key, 0);
		if (str) return str;
		switch (key) {
			case GLFW_KEY_SPACE: return " ";
			case GLFW_KEY_LEFT_SHIFT: return "LSHIFT";
			case GLFW_KEY_RIGHT_SHIFT: return "RSHIFT";
			case GLFW_KEY_ESCAPE: return "ESCAPE";
			case GLFW_KEY_ENTER: return "ENTER";
			case GLFW_KEY_UP: return "UP";
			case GLFW_KEY_LEFT: return "LEFT";
			case GLFW_KEY_RIGHT: return "RIGHT";
			case GLFW_KEY_DOWN: return "DOWN";
			default: return "(UNKNOWN)";
		}
	}

	void Window::KeyCallback(GLFWwindow* window, Int key, Int scancode, Int action, Int mods)
	{
		EventHandler::Push(new Event((action == GLFW_PRESS ? EventType::KeyDown : action == GLFW_REPEAT ? EventType::KeyRepeat : EventType::KeyUp), static_cast<void*>(new String(GetKeyName(key)))));
	}

	void Window::MessageCallback(Uint source, Uint type, Uint id, Uint severity, Int length, const Char* message, const void* data)
	{
		MoonLogError(message);
	}

	void Window::MouseMoveCallback(GLFWwindow* window, Double xpos, Double ypos)
	{
		EventHandler::Push(new Event(EventType::MouseMove, static_cast<void*>(new Vec2(xpos, ypos))));
	}

	void Window::ClickCallback(GLFWwindow* window, Int button, Int action, Int mods)
	{
		Double xpos;
		Double ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (button == GLFW_MOUSE_BUTTON_1)
		{
			EventHandler::Push(new Event((action == GLFW_PRESS ? EventType::MouseLeftPress : EventType::MouseLeftRelease), static_cast<void*>(new Vec2(xpos, ypos))));
		}
		else if (button == GLFW_MOUSE_BUTTON_2)
		{
			EventHandler::Push(new Event((action == GLFW_PRESS ? EventType::MouseRightPress : EventType::MouseRightRelease), static_cast<void*>(new Vec2(xpos, ypos))));
		}
	}

	Int Window::Create()
	{
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		s_Window = glfwCreateWindow(s_Width, s_Height, s_Title.c_str(), NULL, NULL);

		if (!s_Window)
		{
			Close();
			return -1;
		}

		glfwMakeContextCurrent(s_Window);

		if (glewInit() != GLEW_OK)
		{
			Close();
			return -2;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, NULL);

		glfwSetKeyCallback(s_Window, KeyCallback);
		glfwSetCursorPosCallback(s_Window, MouseMoveCallback);
		glfwSetMouseButtonCallback(s_Window, ClickCallback);

		return 0;
	}
	
	void Window::Close()
	{
		glfwTerminate();
	}

	void Window::Update()
	{
		glfwSwapBuffers(s_Window);
		glfwPollEvents();
		if (glfwWindowShouldClose(s_Window))
		{
			EventHandler::Push(new Event(EventType::WindowClose, (EventData)nullptr));
			return;
		}
	}

	void Window::SetBackgroundColor(Float r, Float g, Float b)
	{
		Renderer::SetBackgroundColor(Vec3(r / 255, g / 255, b / 255));
	}

	void Window::SetTitle(const String& title)
	{
		s_Title = title;
	}

	void Window::SetDimensions(Uint width, Uint height)
	{
		s_Width = width;
		s_Height = height;
	}

	void Window::SetCursorType(CursorType ct)
	{
		GLFWcursor* cursor = nullptr;
		
		switch (ct)
		{
		case CursorType::Pointer:
			cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
			break;
		case CursorType::Normal:
			cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
			break;
		}

		glfwSetCursor(s_Window, cursor);
	}
}