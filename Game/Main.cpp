#include <PhysicsEngine/PhysicsEngine.h>
#include <nclgl/GraphicsPipeline.h>

#include <Engine/SceneManager.h>

#include "TestScene.h"
#include "Engine/MessageSystem.h"
#include "Engine/SystemManager.h"
#include "Engine/Interfaces/ISystem.h"

#define GET_INSTANCE(CLASS) CLASS::Instance();

class Game
{
public:
	Game()
	{
		Initialize();
		SceneManager::Instance()->GoToScene("test");
		UpdateMainThread();
	}

	~Game()
	{
		_renderThread.join();
	}

	void UpdateMainThread()
	{
		while (Window::GetWindow().UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE))
		{
			//Start Timing
			float dt = Window::GetWindow().GetTimer()->GetTimedMS() * 0.001f; //How many milliseconds since last update?
			auto scene = SceneManager::Instance()->GetActiveScene();

			if (scene)
				scene->UpdateScene(dt);

			GraphicsPipeline::Instance()->UpdateScene(dt);
			GraphicsPipeline::Instance()->RenderScene();

			Physics::PhysicsEngine::Instance()->UpdatePhysics(dt);

			UpdateSystems(dt);
		}
	}

	void UpdateSystems(float dt)
	{
		for(auto system : m_systems)
		{
			system->OnUpdate(dt);
		}
	}

	void RenderThread()
	{
		auto timer = GameTimer();

		while (_running)
		{
			//Physics::PhysicsEngine::Instance()->UpdatePhysics(timer.GetTimedMS() * 0.001f);
			//GraphicsPipeline::Instance()->UpdateScene(timer.GetTimedMS() * 0.001f);
			//GraphicsPipeline::Instance()->RenderScene();
		}
	}

	void Initialize()
	{
		if (!Window::Initialise("Game Technologies - Collision Resolution", 1280, 800, false))
			Quit(true, "Window failed to initialise!");

		_running = true;

		Physics::PhysicsEngine::Instance();
		GraphicsPipeline::Instance();
		_renderThread = std::thread(&Game::RenderThread, this);
		SceneManager::Instance();

		Scene* scene = new TestScene("test");
		SceneManager::Instance()->AddScene(scene);

		ae::MessageSystem* test = nullptr;
		USE_SYSTEM(test);

		auto mgs = ae::Message();
		test->addMessage(mgs);
	}

	void Quit(bool error, const string& reason)
	{
		//Release Singletons
		SceneManager::Release();
		GraphicsPipeline::Release();
		Physics::PhysicsEngine::Release();
		Window::Destroy();

		//Show console reason before exit
		if (error)
		{
			std::cout << reason << std::endl;
			system("PAUSE");
			exit(-1);
		}
	}

private:
	std::thread _renderThread;
	std::mutex _mutex;
	std::atomic<float> _dt;

	std::vector<std::shared_ptr<ae::ISystem>> m_systems;

	bool _running{};
};

int main()
{
	auto game = new Game();
	return 0;
}
