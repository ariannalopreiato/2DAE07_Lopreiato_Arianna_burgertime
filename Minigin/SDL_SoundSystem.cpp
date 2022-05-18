#include "MiniginPCH.h"
#include "SDL_SoundSystem.h"
#include <SDL_mixer.h>

class dae::SDL_SoundSystem::PimplImpl
{
private:
	std::unordered_map<soundId, Mix_Music*> m_MusicMap;
	std::unordered_map<soundId, Mix_Chunk*> m_ChunkMap;
	soundId m_MusicCounter{ 0 };
	soundId m_ChunkCounter{ 0 };

public:
	soundId loadMusic(const std::string& path)
	{
		auto song = Mix_LoadMUS(path.c_str());
		if (song == nullptr)
		{
			std::string errorMsg = "SoundStream: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
			std::cerr << errorMsg;
		}
		m_MusicMap.insert(std::make_pair(m_MusicCounter, song));
		++m_MusicCounter;
		return m_MusicCounter - 1;
	}

	void playMusic(const soundId id, const int looping)
	{
		auto it = m_MusicMap.find(id);
		if (it != m_MusicMap.end())
		{
			//-1 : infinite looping
			Mix_PlayMusic(it->second, looping);
			//Mix_VolumeMusic(volume);
		}
	}
		//ProcessQueue
		//{ do
		//{
		//	if (!m_requests.empty())
		//	{
		//		std::unique_lock<std::mutex> lock{ m_mutex };
		//		auto request = m_request.front();
		//		m_request.pop();
		//		lock.unlock();
		//		auto audioclip = audioclips[request.first];
		//		if (!audioclip->is_loaded())
		//			audioclip->load();
		//		audioclip->set_volume(request.second);
		//		audioclip->play();
		//	std::lock_guard<std::mutex> lock{ mutex };
		//	if (m_requests.empty())
		//		m_work.available.wait(lock);
		//}while (!m_Requests.empty());
		//}

	void stopMusic()
	{
		Mix_HaltMusic();
	}

	soundId loadSound(const std::string& path)
	{
		auto song = Mix_LoadWAV(path.c_str());
		if (song == nullptr)
		{
			std::string errorMsg = "SoundStream: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError();
			std::cerr << errorMsg;
		}
		m_ChunkMap.insert(std::make_pair(m_ChunkCounter, song));
		++m_ChunkCounter;
		return m_ChunkCounter - 1;
	}

	void playSound(const soundId id)
	{
		auto it = m_ChunkMap.find(id);
		if (it != m_ChunkMap.end())
		{
			//-1 : infinite looping
			Mix_PlayChannel(-1, it->second, 0);
			//Mix_VolumeMusic(volume);
		}
	}

	void stopSound(const soundId id)
	{
		Mix_HaltChannel(id);
	}

	void stopAllSounds()
	{
		Mix_HaltChannel(-1);
	}

	bool HandleEvent(const Event& currentEvent)
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

	~PimplImpl()
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
};

dae::SDL_SoundSystem::SDL_SoundSystem()
	:m_pImpl{ std::make_unique<PimplImpl>() }
	//m_thread(&sdl_sound_system::process_queue)
{}

dae::soundId dae::SDL_SoundSystem::loadMusic(const std::string& path)
{
	return m_pImpl->loadMusic(path);
}

void dae::SDL_SoundSystem::playMusic(const soundId id, const int looping)
{
	m_pImpl->playMusic(id, looping);
}

void dae::SDL_SoundSystem::stopMusic()
{
	m_pImpl->stopMusic();
}

dae::soundId dae::SDL_SoundSystem::loadSound(const std::string& path)
{
	return m_pImpl->loadSound(path);
}

void dae::SDL_SoundSystem::playSound(const soundId id)
{
	m_pImpl->playSound(id);
}

void dae::SDL_SoundSystem::stopSound(const soundId id)
{
	m_pImpl->stopSound(id);
}

void dae::SDL_SoundSystem::stopAllSounds()
{
	m_pImpl->stopAllSounds();
}

bool dae::SDL_SoundSystem::HandleEvent(const Event& currentEvent)
{
	return m_pImpl->HandleEvent(currentEvent);
}

dae::SDL_SoundSystem::~SDL_SoundSystem()
{
	m_pImpl->~PimplImpl();
}
