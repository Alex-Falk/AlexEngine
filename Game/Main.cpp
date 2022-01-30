
#include <PhysicsEngine/PhysicsEngine.h>
#include <PhysicsEngine/GraphicsPipeline.h>

#include <Engine/SceneManager.h>

#include "TestScene.h"

void Quit(bool error, const string& reason);

void Initialize()
{
	if (!Window::Initialise("Game Technologies - Collision Resolution", 1280, 800, false))
		Quit(true, "Window failed to initialise!");

	PhysicsEngine::Instance();
	GraphicsPipeline::Instance();
	SceneManager::Instance();

	Scene* scene = new TestScene();
	SceneManager::Instance()->AddScene(scene);
	scene->ActivateScene();
}

void Quit(bool error, const string& reason) {
	//Release Singletons
	SceneManager::Release();
	GraphicsPipeline::Release();
	PhysicsEngine::Release();
	Window::Destroy();

	//Show console reason before exit
	if (error) {
		std::cout << reason << std::endl;
		system("PAUSE");
		exit(-1);
	}
}


int main() {
	Initialize();

	while (Window::GetWindow().UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		//Start Timing
		float dt = Window::GetWindow().GetTimer()->GetTimedMS() * 0.001f;	//How many milliseconds since last update?

		auto scene = SceneManager::Instance()->GetActiveScene();

		GraphicsPipeline::Instance()->UpdateScene(dt);
		GraphicsPipeline::Instance()->RenderScene();
	}
}