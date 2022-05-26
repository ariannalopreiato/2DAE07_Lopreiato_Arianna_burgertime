#include "MiniginPCH.h"
#include "IEventListener.h"
#include "EventQueue.h"
#include "Event.h"

dae::IEventListener::IEventListener()
{
	EventQueue::GetInstance().AddListeners(this);
}