#include "SecondScene.h"
#include "GameManager.h"

SecondScene::SecondScene(const std::string& name)
	:Scene(name)
{}

void SecondScene::LoadSceneElements()
{
    ////----------------------------------------Lives display
    //for (size_t i = 0; i < size_t(startLives); ++i)
    //{
    //    auto health = pHealthComponentOne->SpawnLife();
    //    Add(health);
    //}

    auto font = dae::ResourceManager::GetInstance().LoadFont("../Data/RetroGaming.ttf", 20);
    //------------------------------------------------------Score component
    auto scoreGO = std::make_shared<dae::GameObject>();
    auto scoreComponent = std::make_shared<PointComponent>(scoreGO, 0, glm::vec3{ 170.f, 30.f, 0.0f }, "HighScores.txt");
    auto textPoint = std::make_shared<dae::TextObject>(scoreGO, "0", font);
    textPoint->SetColor(SDL_Color{ 255, 255, 255, 255 });
    scoreGO->AddComponent(textPoint);
    scoreGO->AddComponent(scoreComponent);

    //------------------------------------------------------Pepper component
    auto pepperGO = std::make_shared<dae::GameObject>();
    auto pepperComponent = std::make_shared<PointComponent>(pepperGO, 0, glm::vec3{ 600.f, 30.f, 0.0f }, "HighScores.txt");
    auto pepperAmount = std::make_shared<dae::TextObject>(pepperGO, "5", font);
    pepperAmount->SetColor(SDL_Color{ 255, 255, 255, 255 });
    pepperGO->AddComponent(pepperAmount);
    pepperGO->AddComponent(pepperComponent);

    //------------------------------------------------------Lives component
    //auto livesGO = std::make_shared<dae::GameObject>();
    //auto pepperComponent = std::make_shared<PointComponent>(pepperGO, 0, glm::vec3{ 600.f, 30.f, 0.0f });
    //auto pepperAmount = std::make_shared<dae::TextObject>(pepperGO, "5", font);
    //pepperAmount->SetColor(SDL_Color{ 255, 255, 255, 255 });
    //pepperGO->AddComponent(pepperAmount);
    //pepperGO->AddComponent(pepperComponent);

    Add(pepperGO);
    Add(scoreGO);

    GameManager::LoadUI(font);
    GameManager::LoadLevel("../Data/Level2.txt", scoreComponent);
    GameManager::LoadPlayersAndEnemies(glm::vec3{ 155.f, 510.f, 0.0f }, "../Data/EnemiesLevel2.txt", glm::vec3{ 443.0f, 510.f, 0.0f });
}