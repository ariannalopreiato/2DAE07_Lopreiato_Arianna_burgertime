#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.emplace_back(observer);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}

void dae::Subject::notify(const std::string& message)
{
	for (size_t i = 0; i < m_Observers.size(); ++i)
	{
		m_Observers[i]->onNotify(message);
	}
}

dae::Subject::~Subject()
{}