#include "FirstScene.h"
#include "GameManager.h"

FirstScene::FirstScene(const std::string& name)
	:Scene(name)
{}

void FirstScene::LoadSceneElements()
{
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
    auto livesGO = std::make_shared<dae::GameObject>();
    livesGO->GetComponent<dae::Transform>()->SetPosition(glm::vec3{ 600.f, 30.f, 0.0f });
    auto livesComponent = std::make_shared<HealthComponent>(livesGO, 0);
    livesGO->AddComponent(livesComponent);

    Add(pepperGO);
    Add(scoreGO);
    GameManager::LoadUI(font);
    GameManager::LoadLevel("../Data/Level1.txt", scoreComponent);
    GameManager::LoadPlayersAndEnemies(glm::vec3{ 280.0f, 350.f, 0.0f }, "../Data/EnemiesLevel1.txt", glm::vec3{ 320.0f, 350.f, 0.0f });
}
