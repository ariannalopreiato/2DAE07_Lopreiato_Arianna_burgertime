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
	if (m_IsInStartingPos)
	{
		auto currentGameObjectPos = m_Transform.lock()->GetPosition();
		m_Shape.x = int(currentGameObjectPos.x);
		m_Shape.y = int(currentGameObjectPos.y);
	}

	if (m_HasStartingSize)
	{
		auto currentGameObjectSize = m_Transform.lock()->GetSize();
		m_Shape.w = int(currentGameObjectSize.x);
		m_Shape.h = int(currentGameObjectSize.y);
	}
}

void dae::CollisionComponent::Render() const
{
	if (m_IsBoxVisible)
	{
		auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();
		SDL_SetRenderDrawColor(renderer, Uint8{ 255 }, Uint8{ 255 }, Uint8{ 255 }, Uint8{ 255 });
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

void dae::CollisionComponent::SetSize(float width, float height)
{
	m_Shape.w = int(width);
	m_Shape.h = int(height);
	m_HasStartingSize = false;
}

void dae::CollisionComponent::SetPosition(float x, float y)
{
	m_Shape.x = int(x);
	m_Shape.y = int(y);
	m_IsInStartingPos = false;
}

void dae::CollisionComponent::ResetSize()
{
	m_HasStartingSize = true;
}

void dae::CollisionComponent::ResetPosition()
{
	m_IsInStartingPos = true;
}

const SDL_Rect& dae::CollisionComponent::GetCollisionBox() const
{
	return m_Shape;
}

std::shared_ptr<dae::Component> dae::CollisionComponent::Clone(const std::shared_ptr<dae::GameObject>& gameObject)
{
	return std::make_shared<CollisionComponent>(gameObject);
}