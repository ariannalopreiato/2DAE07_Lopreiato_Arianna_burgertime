#pragma once
#include "MiniginPCH.h"
#include "Scene.h"

class GameOverScene : public dae::Scene
{
public:
	GameOverScene(const std::string& name);
	~GameOverScene();
	void SetPoints(int points);
	virtual void OnSelect();
	virtual void LoadSceneElements() override;
	void WriteToFile();

private:
	void ReadFile();
	std::vector<int> m_Scores;
	int m_CurrentPoints{};
	const std::string m_File{ "../Data/HighScores.txt" };
};

