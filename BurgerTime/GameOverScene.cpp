#include "GameOverScene.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameManager.h"
#include "GameStateHandler.h"
#include "SelectCommand.h"
#include "InputManager.h"
#include <fstream>
#include <string>

GameOverScene::GameOverScene(const std::string& name)
	:Scene(name)
{}

GameOverScene::~GameOverScene()
{
	if (!m_Scores.empty())
		WriteToFile();
}

void GameOverScene::SetPoints(int points)
{
	m_CurrentPoints = points;
	ReadFile();
}

void GameOverScene::OnSelect()
{
	GameStateHandler::GetInstance().ChangeState(GameState::mainMenu);
}

void GameOverScene::LoadSceneElements()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("../Data/RetroGaming.ttf", 25);

	auto highScore = std::make_shared<dae::GameObject>();
	highScore->GetComponent<dae::Transform>()->SetPosition(175.f, 100.f, 0.0f);
	auto highScoreText = std::make_shared<dae::TextObject>(highScore, "HIGH SCORE BOARD", font);
	highScoreText->SetColor(SDL_Color{ 255, 0, 0});
	highScore->AddComponent(highScoreText);

	auto select = std::make_unique<SelectCommand>();

	float startPos{ 260.f };
	int currentPlayer{ 1 };
	for (const auto& score : m_Scores)
	{
		auto points = std::make_shared<dae::GameObject>();
		points->GetComponent<dae::Transform>()->SetPosition(230.f, startPos, 0.0f);
		auto pointsText = std::make_shared<dae::TextObject>(points, std::to_string(currentPlayer) + ". " + std::to_string(score), font);
		points->AddComponent(pointsText);
		Add(points);
		startPos += 50;
		++currentPlayer;
	}

	auto input = GameManager::GetInputMethodOne();
	if(input == InputMethod::controller)
		dae::InputManager::GetInstance().AddCommandController(std::move(select), dae::ControllerButton::ButtonX, false);
	else
		dae::InputManager::GetInstance().AddCommandKeyboard(std::move(select), SDL_SCANCODE_RSHIFT, true);


	Add(highScore);
}

void GameOverScene::ReadFile()
{
	std::ifstream highScores;
	highScores.open(m_File);
	std::string line;
	m_Scores.clear();
	while (std::getline(highScores, line))
	{
		m_Scores.emplace_back(std::stoi(line));
	}
	for (size_t i = 0; i < m_Scores.size(); ++i)
	{
		if (m_Scores[i] < m_CurrentPoints)
		{
			auto extra = m_Scores[i];
			m_Scores[i] = m_CurrentPoints;
			m_CurrentPoints = extra;
		}
	}
}

void GameOverScene::WriteToFile()
{
	std::ofstream highScores;
	highScores.open(m_File);
	for(size_t i = 0 ; i < m_Scores.size(); ++i)
		highScores << std::to_string(m_Scores[i]) << '\n';
	highScores.close();
}
