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
		void DeleteScene(const std::string& name);
		void Update(float elapsedTime);
		void Render();
		void AddToCurrentScene(const std::shared_ptr<dae::GameObject>& gameObject);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::weak_ptr<Scene> m_CurrentScene;
	};
}
