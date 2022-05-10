#pragma once
#include "MiniginPCH.h"
#include "Component.h"
#include "PointComponent.h"
#include "Texture2D.h"
#include "TextureComponent.h"
#include "HealthComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "EnemyComponent.h"

class EnemyManager : public dae::Component
{
public:
	EnemyManager(const std::shared_ptr<dae::GameObject>& gameObject);
	void Update(float elapsedSec);
	void Render() const;
	std::shared_ptr<dae::GameObject> SpawnEnemy(EnemyType enemyType);
	//const std::vector<std::weak_ptr<EnemyComponent>>& GetEnemies() const;
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	//std::vector<std::weak_ptr<EnemyComponent>> m_Enemies;
};