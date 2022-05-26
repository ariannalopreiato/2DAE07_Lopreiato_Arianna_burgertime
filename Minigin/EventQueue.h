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
		void Cleanup();
		void AddEvent(Event&& currentEvent);
		void RemoveHandledEvents();
		void AddListeners(IEventListener* listener);

	private:
		friend class Singleton<EventQueue>;
		EventQueue();
		void Update();

		std::vector<Event> m_Events;
		std::vector<IEventListener*> m_Listeners;
		std::mutex m_Mutex;
		std::condition_variable m_CV;
		std::thread m_Thread;
		bool m_IsRunning{ true };
	};
}