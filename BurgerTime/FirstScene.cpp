#include "FirstScene.h"
#include "GameManager.h"

FirstScene::FirstScene(const std::string& name)
	:Scene(name)
{}

void FirstScene::LoadSceneElements()
{
    Scene::LoadSceneElements();

    GameManager::LoadLevel("../Data/Level1.txt");
    GameManager::LoadPlayersAndEnemies(glm::vec3{ 155.0f, 350.f, 0.0f }, "../Data/EnemiesLevel1.txt", glm::vec3{ 300.0f, 350.f, 0.0f });
}
