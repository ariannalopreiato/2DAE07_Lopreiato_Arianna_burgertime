#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "Renderer.h"

dae::CollisionComponent::CollisionComponent(std::shared_ptr<dae::GameObject> gameObject)
	:Component(gameObject)
{
	m_Transform = gameObject->GetComponent<Transform>();
}

void dae::CollisionComponent::Update(float)
{
	auto currentGameObjectPos = m_Transform.lock()->GetPosition();
	m_Shape.x = int(currentGameObjectPos.x);
	m_Shape.y = int(currentGameObjectPos.y);
	auto currentGameObjectSize = m_Transform.lock()->GetSize();
	m_Shape.w = int(currentGameObjectSize.x);
	m_Shape.h = int(currentGameObjectSize.y);
}

void dae::CollisionComponent::Render() const
{
	if (m_IsBoxVisible)
	{
		auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();
		SDL_RenderDrawRect(renderer, &m_Shape);
	}
}

bool dae::CollisionComponent::IsOverlapping(const SDL_Rect& other)
{
	SDL_bool isOverlapping = SDL_HasIntersection(&m_Shape, &other);
	if (isOverlapping == SDL_TRUE)
		return true;
	else
		return false;
}

const SDL_Rect& dae::CollisionComponent::GetCollisionBox() const
{
	return m_Shape;
}

std::shared_ptr<dae::Component> dae::CollisionComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<CollisionComponent>(gameObject);
}