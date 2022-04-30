#pragma once
#include <vector>
#include "Event.h"
#include "Singleton.h"

namespace dae
{
	class IEventListener;
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		void Update();
		void AddEvent(Event&& currentEvent);
		void RemoveHandledEvents();
		void AddListeners(IEventListener& listener);

	private:
		std::vector<Event> m_Events;
		std::vector<IEventListener*> m_Listeners;
	};
}