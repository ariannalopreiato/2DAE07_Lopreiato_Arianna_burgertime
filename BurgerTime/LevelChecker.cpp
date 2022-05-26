#include "LevelChecker.h"

bool LevelChecker::CheckIsNextStairs(const SDL_Rect& otherCollisionBox)
{
	auto stairs = LevelCreator::GetStairs();
	SDL_Rect playerCenter{};
	playerCenter.w = otherCollisionBox.w / 3;
	playerCenter.h = otherCollisionBox.h;
	playerCenter.y = otherCollisionBox.y;
	playerCenter.x = otherCollisionBox.x + playerCenter.w;

	for (size_t i = 0; i < stairs.size(); ++i)
	{
		auto stairCollision = stairs.at(i)->GetComponent<dae::CollisionComponent>();
		auto stairBox = stairCollision->GetCollisionBox();
		if (stairCollision->IsOverlapping(playerCenter))
		{
			return true;
		}
	}
	return false;
}

bool LevelChecker::CheckIsOnStairs(const SDL_Rect& )
{
	//todo check is on stairs
	//auto stairs = LevelCreator::GetStairs();
	//for (size_t i = 0; i < stairs.size(); ++i)
	//{
	//	if(otherCollisionBox.y > )
	//}
	return false;
}

bool LevelChecker::CheckIsOnIngredient(const SDL_Rect& )
{
	return false;
}

bool LevelChecker::CheckIsOnPlatform(const SDL_Rect& )
{
	return false;
}
