#pragma once

namespace dae
{
	class Event;
	class EventQueue;
	class IEventListener
	{
	public:
		IEventListener();
		virtual ~IEventListener() = default;
		virtual bool HandleEvent(const Event& currentEvent) = 0;
	};
}