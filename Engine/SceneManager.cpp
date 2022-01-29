#include "SceneManager.h"

void SceneManager::AddScene(Scene* scene)
{
	if (scene == nullptr) {
		return;
	}

	m_scenes.push_back(scene);
}

void SceneManager::RemoveScene(Scene* scene)
{
	if (scene == nullptr) {
		return;
	}

	m_scenes.erase(std::remove(m_scenes.begin(), m_scenes.end(), scene), m_scenes.end());
}

bool SceneManager::GoToScene(const std::string& name)
{
	for (Scene* scene : m_scenes) {
		if (scene->GetName() == name) {
			m_scene = scene;
			m_scene->ActivateScene();
			return true;
		}
	}

	return false;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (Scene* scene : m_scenes) {
		scene->Cleanup();
		delete scene;
	}

	m_scenes.clear();
}
