#include "Application.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"


namespace Moon
{
	void Application::Run()
	{
		int err = Window::Create();

		if (err == -1)
		{
			MoonLogCritical("Failed to Initialize Window!");
			return;
		}

		if (err == -2)
		{
			MoonLogCritical("Failed to Initialize GlEW!");
			return;
		}

		bool running = true;

		OnStart();

		while (running)
		{
			Renderer::Prepare();
			Renderer::Render();
			OnUpdate();
			EventHandler::Update();
			Window::Update();
			while (EventHandler::Front() != nullptr)
			{
				if (EventHandler::Front()->GetEventType() == EventType::WindowClose)
				{
					running = false;
				}
				EventHandler::Pop();
			}
		}

		Window::Close();
	}

	void Application::Close()
	{
		EventHandler::Push(new Event(EventType::WindowClose, nullptr));
	}
}