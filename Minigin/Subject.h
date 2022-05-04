#pragma once
#include <vector>

namespace dae
{
	class Observer;
	class Subject //object being observed
	{
	public:
		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);
		~Subject();

	protected:
		void notify(const std::string& message);

	private:
		std::vector<std::shared_ptr<Observer>> m_Observers;
	};
}
