#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		//friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		Scene(const std::string& name);
		void Add(const std::shared_ptr<GameObject>& object);
		virtual void LoadSceneElements() = 0;
		void CleanUpScene();
		const std::string& GetName();
		void Update(float elapsedTime);
		void Render() const;

	private: 
		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_Objects;

		static unsigned int m_IdCounter; 
	};
}
