#pragma once
#include "MiniginPCH.h"
#include "Scene.h"

class MainMenuScene : public dae::Scene
{
public:
	MainMenuScene(const std::string& name);
	void IncreaseSelectedMode();
	void DecreaseSelectedMode();
	virtual void OnSelect();
	virtual void LoadSceneElements() override;

private:
	int m_SelectedMode{};
	float m_Space{ 50.f };
	float m_StartPos{ 320.f };
	std::shared_ptr<dae::GameObject> m_Arrow{};
};

