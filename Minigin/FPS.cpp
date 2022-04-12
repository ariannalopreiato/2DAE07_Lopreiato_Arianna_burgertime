#include "MiniginPCH.h"
#include "FPS.h"
#include <chrono>

dae::FPS::FPS(const int msPerFrame, const std::shared_ptr<GameObject>& gameObject)
	: Component(gameObject)
	, m_MsPerFrame{ msPerFrame }
{ }

void dae::FPS::Update(float)
{
	double sPerFrame = m_MsPerFrame/1000;
	m_Fps = int(1 / sPerFrame);
}

int dae::FPS::GetFPS() const
{
	return m_Fps;
}

std::shared_ptr<dae::Component> dae::FPS::Clone(const std::shared_ptr<GameObject>& gameObject)
{
	return std::make_shared<FPS>(m_MsPerFrame, gameObject);
}