#pragma once
#include "PlayerComponent.h"

class IPlayerState
{
public:
	virtual ~IPlayerState() {};
	virtual void HandleInput(std::shared_ptr<PlayerComponent> player) {};
	virtual void Update(std::shared_ptr<PlayerComponent> player) {};
};

