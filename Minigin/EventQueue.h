#pragma once
#include <vector>
#include "Event.h"
#include "Singleton.h"
#include <mutex>

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
		std::mutex m_Mutex;
		int m_NrThreads;
		std::vector<std::jthread> m_Threads;
	};
}