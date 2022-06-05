#pragma once
#include "Singleton.h"
#include "GameObject.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(const std::shared_ptr<Scene>& scene);
		void LoadScene(const std::string& name);
		void AddSharedObject(const std::shared_ptr<dae::GameObject>& sharedObject);
		void DeleteScene(const std::string& name);
		void Update(float elapsedTime);
		void Render();
		void AddToCurrentScene(const std::shared_ptr<dae::GameObject>& gameObject);
		void SetLevelToLoad(const std::string& levelToLoad);
		const std::vector<std::shared_ptr<dae::GameObject>>& GetSharedObjects();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::weak_ptr<Scene> m_CurrentScene;
		std::vector<std::shared_ptr<GameObject>> m_SharedSceneObjects;

		bool m_CanLoadNewScene{ false };
		float m_Wait{ 0.0f };
		const float m_TotalWaitTime{ 1.f };
		std::string m_LevelToLoad{};
	};
}
