#pragma once
#include <memory>
#include <string>

namespace dae
{
	struct IEventData //work around to avoid making the Event class templated
	{
		virtual ~IEventData() = default;
	};

	template <typename Data>
	struct EventData : public IEventData
	{
		EventData(const Data& data)
			:m_Data(data)
		{}

		Data m_Data;
	};

	class Event
	{
	public:
		template <typename Data>
		Event(const Data& data, const std::string& name)
			:m_Data(std::make_unique<Data>(data)) , m_EventName(name)
		{}

		const std::string& GetName() const
		{
			return m_EventName;
		}

		template <typename Data>
		const Data& GetEventData() const
		{
			return static_cast<EventData<Data>*>(m_Data.get())->m_Data;
		}

		bool m_IsExecuted{ false };

	private:
		std::string m_EventName;
		std::unique_ptr<IEventData> m_Data;

	};
}