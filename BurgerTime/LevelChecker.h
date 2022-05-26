#pragma once
#include "MiniginPCH.h"
#include "LevelCreator.h"

class LevelChecker
{
public:
	bool CheckIsNextStairs(const SDL_Rect& otherCollisionBox);
	bool CheckIsOnStairs(const SDL_Rect& otherCollisionBox);
	bool CheckIsOnIngredient(const SDL_Rect& otherCollisionBox);
	bool CheckIsOnPlatform(const SDL_Rect& otherCollisionBox);
private:
};

