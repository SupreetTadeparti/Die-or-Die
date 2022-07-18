#include "Event.hpp"

namespace Moon
{
	std::vector<CustomEvent*> EventHandler::s_CustomEvents;
	std::queue<Event*> EventHandler::s_EventQueue;
	std::unordered_map<String, bool> EventHandler::s_Keys;
	MouseMoveCallback EventHandler::s_MouseMoveCallback = nullptr;
	MouseMoveCallback EventHandler::s_ClickCallback = nullptr;
	void* EventHandler::s_MouseMoveApp;
	void* EventHandler::s_ClickApp;

	Event::Event(EventType type, EventData data) : m_EventType(type), m_EventData(data)
	{
	}

	CustomEvent::CustomEvent(CustomEventCallback callback, Uint ms, void* app) : m_Callback(callback), m_Interval(ms), m_Application(app), m_OneTime(false)
	{
		ResetTime();
	}

	CustomEvent::CustomEvent(CustomEventCallback callback, Uint ms, void* app, Bool oneTime) : m_Callback(callback), m_Interval(ms), m_Application(app), m_OneTime(oneTime)
	{
		ResetTime();
	}

	void CustomEvent::ResetTime()
	{
		m_PrevTime = Util::CurrentTime();
	}

	Event* EventHandler::Front()
	{
		if (s_EventQueue.size() == 0) return nullptr;
		return s_EventQueue.front();
	}

	void EventHandler::Pop()
	{
		delete s_EventQueue.front()->GetEventData();
		s_EventQueue.pop();
	}

	void EventHandler::Push(Event* e)
	{
		EventType eventType = e->GetEventType();
		if (eventType == EventType::KeyDown)
		{
			s_Keys[*(static_cast<String*>(e->GetEventData()))] = true;
		}
		else if (eventType == EventType::KeyUp)
		{
			s_Keys[*(static_cast<String*>(e->GetEventData()))] = false;
		}
		else if (eventType == EventType::MouseMove)
		{
			if (s_MouseMoveCallback != nullptr)
			{
				Vec2 mousePos = *(static_cast<Vec2*>(e->GetEventData()));
				Double x = mousePos.x;
				Double y = mousePos.y;
				s_MouseMoveCallback(s_MouseMoveApp, x, y);
			}
		}
		else if (eventType == EventType::MouseLeftPress)
		{
			if (s_ClickCallback != nullptr)
			{
				Vec2 mousePos = *(static_cast<Vec2*>(e->GetEventData()));
				Double x = mousePos.x;
				Double y = mousePos.y;
				s_ClickCallback(s_ClickApp, x, y);
			}
		}
		s_EventQueue.push(e);
	}

	void EventHandler::Push(CustomEvent* e)
	{
		s_CustomEvents.push_back(e);
	}

	bool EventHandler::KeyDown(const char* key)
	{
		return s_Keys[key];
	}

	void EventHandler::Update()
	{
		List<CustomEvent*> rem;

		for (Uint i = 0; i < s_CustomEvents.size(); i++)
		{
			CustomEvent* e = s_CustomEvents[i];
			if ((Util::CurrentTime() - e->GetPrevTime()).count() >= e->GetInterval())
			{
				e->ResetTime();
				e->GetCallback()(e->GetApplication());
				if (e->GetOneTime())
				{
					rem.push_back(e);
				}
			}
		}

		for (CustomEvent*& e : rem)
		{
			s_CustomEvents.erase(std::remove(s_CustomEvents.begin(), s_CustomEvents.end(), e), s_CustomEvents.end());
		}
	}

	void EventHandler::OnMouseMove(MouseMoveCallback callback, void* app)
	{
		s_MouseMoveCallback = callback;
		s_MouseMoveApp = app;
	}

	void EventHandler::OnClick(ClickCallback callback, void* app)
	{
		s_ClickCallback = callback;
		s_ClickApp = app;
	}
}