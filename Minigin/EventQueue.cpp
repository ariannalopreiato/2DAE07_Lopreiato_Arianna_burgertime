#include "MiniginPCH.h"
#include "EventQueue.h"
#include "IEventListener.h"
#include <functional>

namespace dae
{
	EventQueue::EventQueue()
	{
		m_Thread = std::thread(std::bind(&EventQueue::Update, this));
	}

	void EventQueue::Update()
	{
		while (m_IsRunning)
		{
			std::unique_lock<std::mutex> lock{ m_Mutex };

			m_CV.wait(lock, [this]()->bool
				{
					return !m_IsRunning || !m_Events.empty();
				});

			if (!m_IsRunning)
			{
				return;
			}

			for (size_t i = 0; i < m_Events.size(); ++i)
			{
				for (size_t j = 0; j < m_Listeners.size(); ++j)
				{
					if (m_Listeners[j]->HandleEvent(m_Events[i]))
						m_Events[i].m_IsExecuted = true;
				}
			}

			RemoveHandledEvents();
		}
	}

	void EventQueue::Cleanup()
	{
		m_IsRunning = false;

		m_CV.notify_one();

		m_Thread.join();
	}

	void EventQueue::AddEvent(Event&& currentEvent)
	{
		{
			std::unique_lock<std::mutex> lock{ m_Mutex };

			m_Events.emplace_back(std::move(currentEvent));
		}

		m_CV.notify_one();
	}

	void EventQueue::RemoveHandledEvents()
	{
		m_Events.erase(std::remove_if(m_Events.begin(), m_Events.end(), [](const Event& currentEvent)->bool
			{
				return currentEvent.m_IsExecuted;
			}), m_Events.end());
	}

	void EventQueue::AddListeners(IEventListener* listener)
	{
		std::unique_lock<std::mutex> lock{ m_Mutex };

		m_Listeners.emplace_back(listener);
	}
}
