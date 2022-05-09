#pragma once
#include "Enemy.h"
#include "Component.h"

class EnemyManager : public dae::Component
{
public:
	EnemyManager(const std::shared_ptr<dae::GameObject>& gameObject);
	void Update(float elapsedSec);
	void Render() const;
	void AddEnemy(const std::weak_ptr<Enemy>& enemy);
	const std::vector<std::weak_ptr<Enemy>>& GetEnemies() const;
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;

private:
	std::vector<std::weak_ptr<Enemy>> m_Enemies;
};

