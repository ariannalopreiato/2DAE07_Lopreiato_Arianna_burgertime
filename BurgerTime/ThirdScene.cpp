#include "ThirdScene.h"
#include "GameManager.h"

ThirdScene::ThirdScene(const std::string& name)
	:Scene(name)
{}

void ThirdScene::LoadSceneElements()
{
    Scene::LoadSceneElements();
    GameManager::LoadLevel("../Data/Level3.txt");
    GameManager::LoadPlayersAndEnemies(glm::vec3{ 155.f, 470.f, 0.0f }, "../Data/EnemiesLevel3.txt", glm::vec3{ 443.0f, 470.f, 0.0f });
}