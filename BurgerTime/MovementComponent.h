#pragma once
#include "Component.h"
#include "structs.h"
#include "Vector2f.h"
#include "Observer.h"

class MovementComponent : public dae::Component
{
public:
	MovementComponent(const std::shared_ptr<dae::GameObject>& gameObject, bool isControlled);
	virtual std::shared_ptr<Component> Clone(const std::shared_ptr<dae::GameObject>& gameObject) override;
	//virtual void onNotify(const std::string& message) override;

private:
	bool m_IsControlled{ false };
};

