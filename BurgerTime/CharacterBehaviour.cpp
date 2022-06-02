#include "CharacterBehaviour.h"
#include "GameObject.h"
#include "LevelCreator.h"

CharacterBehaviour::CharacterBehaviour(const std::shared_ptr<dae::GameObject>& gameObject)
	:Component(gameObject)
{
	m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();
	m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();
}

void CharacterBehaviour::Update(float)
{
	if(m_Collision.lock() == nullptr)
		m_Collision = m_GameObject.lock()->GetComponent<dae::CollisionComponent>();

	if(m_Transform.lock() == nullptr)
		m_Transform = m_GameObject.lock()->GetComponent<dae::Transform>();

	SDL_Rect collisionBox = m_Collision.lock()->GetCollisionBox();
	m_LineLeft = Line{ collisionBox.x,
		collisionBox.y + collisionBox.h,
		collisionBox.x,
		collisionBox.y + collisionBox.h + m_LineLength };

	m_LineRight = Line{ collisionBox.x + collisionBox.w,
		collisionBox.y + collisionBox.h,
		collisionBox.x + collisionBox.w,
		collisionBox.y + collisionBox.h + m_LineLength };
}

bool CharacterBehaviour::CanGoRight()
{
	auto objects = LevelCreator::GetPlatforms();
	for (size_t i = 0; i < objects.size(); ++i)
	{
		auto box = objects.at(i)->GetCollisionBox();
		box.h = 1;
		if (SDL_IntersectRectAndLine(&box, &m_LineRight.x1, &m_LineRight.y1, &m_LineRight.x2, &m_LineRight.y2))
		{
			m_CollidingPlatform = box;
			return true;
		}
	}
	return false;
}

bool CharacterBehaviour::CanGoLeft()
{
	auto objects = LevelCreator::GetPlatforms();
	for (size_t i = 0; i < objects.size(); ++i)
	{
		auto box = objects.at(i)->GetCollisionBox();
		box.h = 1;
		if (SDL_IntersectRectAndLine(&box, &m_LineLeft.x1, &m_LineLeft.y1, &m_LineLeft.x2, &m_LineLeft.y2))
		{
			m_CollidingPlatform = box;
			return true;
		}
	}
	return false;
}

bool CharacterBehaviour::CanGoUp()
{
	auto stairs = LevelCreator::GetStairs();
	auto collisionBox = m_Collision.lock()->GetCollisionBox();
	collisionBox.h = 1;
	collisionBox.x = collisionBox.x + collisionBox.w / 3;
	collisionBox.w = collisionBox.w / 3;

	for (size_t i = 0; i < stairs.size(); ++i)
	{
		auto stairBox = stairs.at(i);
		if (stairBox->IsOverlapping(collisionBox))
			return true;
	}
	return false;
}

bool CharacterBehaviour::CanGoDown()
{
	auto stairs = LevelCreator::GetStairs();
	auto collisionBox = m_Collision.lock()->GetCollisionBox();
	collisionBox.x = collisionBox.x + collisionBox.w / 3;
	collisionBox.w = collisionBox.w / 3;
	collisionBox.y = collisionBox.y + collisionBox.h;
	collisionBox.h = 2;
	for (size_t i = 0; i < stairs.size(); ++i)
	{
		auto stairBox = stairs.at(i);
		if (stairBox->IsOverlapping(collisionBox))
			return true;
	}
	return false;
}

void CharacterBehaviour::SnapBack()
{
	int pushBack{ 1 };
	auto currentPos = m_Transform.lock()->GetPosition();
	if (!CanGoLeft())
		m_Transform.lock()->SetPosition(float(currentPos.x + pushBack), float(currentPos.y), 0.0f);
	else if (!CanGoRight())
		m_Transform.lock()->SetPosition(float(currentPos.x - pushBack), float(currentPos.y), 0.0f);
}

void CharacterBehaviour::SnapDown()
{
	auto playerBox = m_Collision.lock()->GetCollisionBox();
	m_Transform.lock()->SetPosition(float(playerBox.x), float(m_CollidingPlatform.y - playerBox.h), 0.0f);
}

const Line& CharacterBehaviour::GetLineLeft()
{
	return m_LineLeft;
}

const Line& CharacterBehaviour::GetLineRight()
{
	return m_LineRight;
}

std::shared_ptr<dae::Component> CharacterBehaviour::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<CharacterBehaviour>(gameObject);
}
