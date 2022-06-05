#include "SecondScene.h"
#include "GameManager.h"

SecondScene::SecondScene(const std::string& name)
	:Scene(name)
{}

void SecondScene::LoadSceneElements()
{
    Scene::LoadSceneElements();
    GameManager::LoadLevel("../Data/Level2.txt");
    GameManager::LoadPlayersAndEnemies(glm::vec3{ 155.f, 490.f, 0.0f }, "../Data/EnemiesLevel2.txt", glm::vec3{ 443.0f, 490.f, 0.0f });
}