#pragma once
#include "SoundSystem.h"
#include <SDL_mixer.h>

namespace dae
{
	class SDL_SoundSystem : public SoundSystem
	{
	public:
		void loadMusic(const std::string& path) override;
		void playMusic(const soundId id, const int looping) override;
		void stopMusic() override;
		void loadSound(const std::string& path) override;
		void playSound(const soundId id) override;
		void stopSound(const soundId id) override;
		void stopAllSounds() override;
		~SDL_SoundSystem();

	private:
		std::unordered_map<soundId, Mix_Music*> m_MusicMap;
		std::unordered_map<soundId, Mix_Chunk*> m_ChunkMap;
		soundId m_MusicCounter{ 0 };
		soundId m_ChunkCounter{ 0 };
	};
}