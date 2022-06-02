#pragma once
#include "MiniginPCH.h"
#include "Scene.h"
#include "MoveCommand.h"
#include "ControllerButton.h"
#include "SoundSystem.h"
#include "ServiceLocator.h"
#include "SDL_SoundSystem.h"
#include "GameObject.h"
#include "TextObject.h"
#include "InputManager.h"
#include "Renderer.h"
#include "PlayerComponent.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerAttackComponent.h"
#include "Ingredient.h"
#include "Texture2D.h"
#include "AttackCommand.h"
#include "LevelReader.h"
#include "LevelCreator.h"
#include "EnemyManager.h"

class FirstScene : public dae::Scene
{
public:
	FirstScene(const std::string& name);
	virtual void LoadSceneElements() override;
};

