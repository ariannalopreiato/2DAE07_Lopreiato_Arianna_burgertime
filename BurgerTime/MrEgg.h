#pragma once
#include "Enemy.h"
#include "Component.h"
#include "TextureComponent.h"

class Texture2D;
class MrEgg : public Enemy, dae::Component
{
public:
	virtual void Update(float elapsedSec) override;
	virtual void Render() const override;
	MrEgg(const std::shared_ptr<dae::GameObject>& gameObject);
};

