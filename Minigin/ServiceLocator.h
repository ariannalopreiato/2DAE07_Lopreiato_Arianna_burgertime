#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		void loadMusic(const std::string&) override {};
		void playMusic(const soundId, const int) override {};
		void stopMusic() override {};
		void loadSound(const std::string&) override {};
		void playSound(const soundId) override {};
		void stopSound(const soundId) override {};
		void stopAllSounds() override {};
	};

	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(SoundSystem* soundSystem);

	private:
		static SoundSystem* m_SoundSystemInstance;
		static NullSoundSystem* m_DeafultSoundSystem;
	};
}
