#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "TextureComponent.h"
#include "Texture2D.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPS.h"
#include "Component.h"
#include <chrono>

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo"); //create scene
	auto go = std::make_shared<dae::GameObject>(); //create game object

	//create components
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto text = std::make_shared<dae::TextObject>(go, "Press A, B, X or Y to play sound", font);
	//auto picture = dae::ResourceManager::GetInstance().LoadTexture("PeterPepperWalk.png");
	//auto texture = std::make_shared<dae::TextureComponent>(go, picture);
	go->AddComponent(text);
	//go->AddComponent(texture);
	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = chrono::high_resolution_clock::now();
			float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();
			lastTime = currentTime;
		}
	}

	Cleanup();
}
