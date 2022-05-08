#include "MiniginPCH.h"
#include "EventQueue.h"
#include "IEventListener.h"

void dae::EventQueue::Update()
{
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

void dae::EventQueue::AddEvent(Event&& currentEvent)
{
	m_Events.push_back(std::move(currentEvent));
}

void dae::EventQueue::RemoveHandledEvents()
{
	m_Events.erase(std::remove_if(m_Events.begin(), m_Events.end(), [](const Event& currentEvent)->bool
		{
			return currentEvent.m_IsExecuted;
		}), m_Events.end());
}

void dae::EventQueue::AddListeners(IEventListener& listener)
{
	m_Listeners.push_back(&listener);
}
