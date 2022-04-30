#pragma once
#include "SoundSystem.h"
#include <SDL_mixer.h> //todo pimpl away
#include "IEventListener.h"
#include "Event.h"

namespace dae
{
	class SDL_SoundSystem : public SoundSystem, IEventListener
	{
	public:
		void loadMusic(const std::string& path) override;
		void playMusic(const soundId id, const int looping) override;
		void stopMusic() override;
		void loadSound(const std::string& path) override;
		void playSound(const soundId id) override;
		void stopSound(const soundId id) override;
		void stopAllSounds() override;
		bool HandleEvent(const Event& currentEvent) override;
		~SDL_SoundSystem();

	private:
		std::unordered_map<soundId, Mix_Music*> m_MusicMap;
		std::unordered_map<soundId, Mix_Chunk*> m_ChunkMap;
		soundId m_MusicCounter{ 0 };
		soundId m_ChunkCounter{ 0 };
	};
}