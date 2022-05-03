#include "MiniginPCH.h"
#include "ServiceLocator.h"

dae::NullSoundSystem *dae::ServiceLocator::m_DeafultSoundSystem;
dae::SoundSystem* dae::ServiceLocator::m_SoundSystemInstance = dae::ServiceLocator::m_DeafultSoundSystem;

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
	if (m_SoundSystemInstance == nullptr)
		m_SoundSystemInstance = m_DeafultSoundSystem;
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
