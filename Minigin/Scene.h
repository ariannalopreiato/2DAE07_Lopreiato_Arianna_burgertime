#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		Scene(const std::string& name);
		void Add(const std::shared_ptr<GameObject>& object);
		virtual void LoadSceneElements();
		void CleanUpScene();
		const std::string& GetName();
		void Update(float elapsedTime);
		void Render() const;
		void SetIsLoading(bool isLoading);
		virtual void OnSelect() {};

	private: 
		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_Objects;
		bool m_IsLoading{ false };
		static unsigned int m_IdCounter; 
	};
}
