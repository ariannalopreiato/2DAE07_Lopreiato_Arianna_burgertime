#pragma once
#include "SoundSystem.h"
#include "IEventListener.h"
#include "Event.h"

namespace dae
{
	class SDL_SoundSystem : public SoundSystem, IEventListener
	{
	public:
		SDL_SoundSystem();
		soundId loadMusic(const std::string& path) override;
		void playMusic(const soundId id, const int looping) override;
		void stopMusic() override;
		soundId loadSound(const std::string& path) override;
		void playSound(const soundId id) override;
		void stopSound(const soundId id) override;
		void stopAllSounds() override;
		bool HandleEvent(const Event& currentEvent) override;
		~SDL_SoundSystem();

	private:
		class PimplImpl;
		std::unique_ptr<PimplImpl> m_pImpl;
	};
}