#include "MiniginPCH.h"
#include "SDL_SoundSystem.h"

void dae::SDL_SoundSystem::loadMusic(const std::string& path)
{
	auto song = Mix_LoadMUS(path.c_str());
	if (song == nullptr)
	{
		std::string errorMsg = "SoundStream: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
	m_MusicMap.insert(std::make_pair(m_MusicCounter++, song));
}

void dae::SDL_SoundSystem::playMusic(const soundId id, const int looping)
{
	auto it = m_MusicMap.find(id);
	if(it != m_MusicMap.end())
	{
		//-1 : infinite looping
		Mix_PlayMusic(it->second, looping);
		//Mix_VolumeMusic(volume);
	}
}

void dae::SDL_SoundSystem::stopMusic()
{
	Mix_HaltMusic();
}

void dae::SDL_SoundSystem::loadSound(const std::string& path)
{
	auto song = Mix_LoadWAV(path.c_str());
	if (song == nullptr)
	{
		std::string errorMsg = "SoundStream: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
		std::cerr << errorMsg;
	}
	m_ChunkMap.insert(std::make_pair(m_ChunkCounter++, song));
}

void dae::SDL_SoundSystem::playSound(const soundId id)
{
	auto it = m_ChunkMap.find(id);
	if (it != m_ChunkMap.end())
	{
		//-1 : infinite looping
		Mix_PlayChannel(-1, it->second, 0);
		//Mix_VolumeMusic(volume);
	}
}

void dae::SDL_SoundSystem::stopSound(const soundId id)
{
	Mix_HaltChannel(id);
}

void dae::SDL_SoundSystem::stopAllSounds()
{
	Mix_HaltChannel(-1);
}

bool dae::SDL_SoundSystem::HandleEvent(const Event& currentEvent)
{
	bool hasPlayed{ false };
	if (currentEvent.GetName() == "PlaySound")
	{
		playSound(currentEvent.GetEventData<soundId>());
		hasPlayed = true;
	}
	if (currentEvent.GetName() == "PlayMusic")
	{
		playMusic(currentEvent.GetEventData<soundId>(), 0);
		hasPlayed = true;
	}

	return hasPlayed;
}

dae::SDL_SoundSystem::~SDL_SoundSystem()
{
	for (const std::pair<soundId, Mix_Music*> songs : m_MusicMap)
	{
		Mix_FreeMusic(songs.second);
	}

	for (const std::pair<soundId, Mix_Chunk*> songs : m_ChunkMap)
	{
		Mix_FreeChunk(songs.second);
	}
}
