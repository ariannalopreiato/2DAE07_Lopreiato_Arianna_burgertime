#pragma once
#include "Minigin.h"
struct SDL_Window;

class BurgerTime
{
public:
	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();
private:
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	dae::Minigin m_MiniginEngine;
	float m_ElapsedTime{ 0.0f };
};