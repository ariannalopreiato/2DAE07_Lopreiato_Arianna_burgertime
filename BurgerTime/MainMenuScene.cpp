#include "MainMenuScene.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "MoveArrowDown.h"
#include "MoveArrowUp.h"
#include "InputManager.h"
#include "GameManager.h"
#include "GameStateHandler.h"
#include "SelectCommand.h"

MainMenuScene::MainMenuScene(const std::string& name)
	:Scene(name)
{}

void MainMenuScene::IncreaseSelectedMode()
{
	++m_SelectedMode;
	if (m_SelectedMode == 3)
		m_SelectedMode = 0;

	auto currentPos = m_Arrow->GetComponent<dae::Transform>()->GetPosition();
	m_Arrow->GetComponent<dae::Transform>()->SetPosition(currentPos.x, float(m_StartPos + (m_Space * m_SelectedMode)), 0.0f);
}

void MainMenuScene::DecreaseSelectedMode()
{
	--m_SelectedMode;
	if (m_SelectedMode == -1)
		m_SelectedMode = 2;

	auto currentPos = m_Arrow->GetComponent<dae::Transform>()->GetPosition();
	m_Arrow->GetComponent<dae::Transform>()->SetPosition(currentPos.x, float(m_StartPos + (m_Space * m_SelectedMode)), 0.0f);
}

void MainMenuScene::OnSelect()
{
	GameManager::SetGameMode(GameMode(m_SelectedMode));
	GameStateHandler::GetInstance().ChangeState(GameState::playing);
}

void MainMenuScene::LoadSceneElements()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("../Data/RetroGaming.ttf", 20);

	auto logo = std::make_shared<dae::GameObject>();
	logo->GetComponent<dae::Transform>()->SetPosition(120.f, 30.f, 0.0f);
	logo->GetComponent<dae::Transform>()->SetSize(400.f, 200.f, 0.0f);
	auto logoPic = dae::ResourceManager::GetInstance().LoadTexture("Sprites/logo.png");
	auto texture = std::make_shared<dae::TextureComponent>(logo, logoPic);
	logo->AddComponent(texture);

	auto onePlayer = std::make_shared<dae::GameObject>();
	onePlayer->GetComponent<dae::Transform>()->SetPosition(270.f, m_StartPos, 0.0f);
	auto onePlayerText = std::make_shared<dae::TextObject>(onePlayer, "1 PLAYER", font);
	onePlayer->AddComponent(onePlayerText);

	auto twoPlayer = std::make_shared<dae::GameObject>();
	twoPlayer->GetComponent<dae::Transform>()->SetPosition(270.f, m_StartPos + m_Space, 0.0f);
	auto twoPlayerText = std::make_shared<dae::TextObject>(twoPlayer, "2 PLAYERS", font);
	twoPlayer->AddComponent(twoPlayerText);

	auto versus = std::make_shared<dae::GameObject>();
	versus->GetComponent<dae::Transform>()->SetPosition(270.f, m_StartPos + (m_Space * 2), 0.0f);
	auto versusText = std::make_shared<dae::TextObject>(versus, "VERSUS", font);
	versus->AddComponent(versusText);

	auto arrow = std::make_shared<dae::GameObject>();
	arrow->GetComponent<dae::Transform>()->SetPosition(240.f, m_StartPos, 0.0f);
	auto arrowText = std::make_shared<dae::TextObject>(arrow, ">", font);
	arrow->AddComponent(arrowText);

	m_Arrow = arrow;

	auto moveUp = std::make_unique<MoveArrowUp>();

	auto moveDown = std::make_unique<MoveArrowDown>();

	auto select = std::make_unique<SelectCommand>();


	auto input = GameManager::GetInputMethodOne();
	if (input == InputMethod::controller)
	{
		dae::InputManager::GetInstance().AddCommandController(std::move(moveUp), dae::ControllerButton::ButtonUp, true);
		dae::InputManager::GetInstance().AddCommandController(std::move(moveDown), dae::ControllerButton::ButtonDown, true);
		dae::InputManager::GetInstance().AddCommandController(std::move(select), dae::ControllerButton::ButtonA, true);
	}
	else
	{
		dae::InputManager::GetInstance().AddCommandKeyboard(std::move(moveUp), SDL_SCANCODE_UP, true);
		dae::InputManager::GetInstance().AddCommandKeyboard(std::move(moveDown), SDL_SCANCODE_DOWN, true);
		dae::InputManager::GetInstance().AddCommandKeyboard(std::move(select), SDL_SCANCODE_ESCAPE, true);
	}
	
	Add(onePlayer);
	Add(twoPlayer);
	Add(versus);
	Add(arrow);
	Add(logo);
}
