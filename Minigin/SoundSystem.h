#pragma once
#include "ResourceManager.h"
#include <unordered_map>

namespace dae 
{
	using soundId = unsigned short;
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;
		virtual ~SoundSystem() = default;

		virtual soundId loadMusic(const std::string& path) = 0;
		virtual void playMusic(const soundId id, const int looping) = 0;
		virtual void stopMusic() = 0;

		virtual soundId loadSound(const std::string& path) = 0;
		virtual void playSound(const soundId id) = 0;
		virtual void stopSound(const soundId id) = 0;
		virtual void stopAllSounds() = 0;
	};
}