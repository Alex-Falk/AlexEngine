
#include <PhysicsEngine/PhysicsEngine.h>
#include <nclgl/GraphicsPipeline.h>

#include <Engine/SceneManager.h>

#include "TestScene.h"

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
			float dt = Window::GetWindow().GetTimer()->GetTimedMS() * 0.001f;	//How many milliseconds since last update?
			auto scene = SceneManager::Instance()->GetActiveScene();

			if (scene) 
				scene->UpdateScene(dt);

			GraphicsPipeline::Instance()->UpdateScene(dt);
			GraphicsPipeline::Instance()->RenderScene();
		}
	}
	
	void RenderThread()
	{
		GameTimer timer = GameTimer();
		
		while(_running)
		{
			Physics::PhysicsEngine::Instance()->UpdatePhysics(timer.GetTimedMS() * 0.001f);
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
	}

	void Quit(bool error, const string& reason) {
		//Release Singletons
		SceneManager::Release();
		GraphicsPipeline::Release();
		Physics::PhysicsEngine::Release();
		Window::Destroy();

		//Show console reason before exit
		if (error) {
			std::cout << reason << std::endl;
			system("PAUSE");
			exit(-1);
		}
	}

private:
	std::thread _renderThread;
	std::mutex _mutex;
	std::atomic<float> _dt;

	bool _running{};
};

int main() {
		auto game = new Game();
		return 0;
}