#include "MiniginPCH.h"
#include "ServiceLocator.h"

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	return *m_SoundSystemInstance;
}

void dae::ServiceLocator::RegisterSoundSystem(SoundSystem* soundSystem)
{
	if (soundSystem == nullptr)
		m_SoundSystemInstance = m_DeafultSoundSystem;
	else
	{
		delete m_SoundSystemInstance;
		m_SoundSystemInstance = soundSystem;
	}
}
