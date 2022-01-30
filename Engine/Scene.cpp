#include "Scene.h"

void Scene::AddGameObject(GameObject* object)
{
	if (!object || std::find(m_gameObjects.begin(), m_gameObjects.end(), object) != m_gameObjects.end())
	{
		return;
	}

	m_gameObjects.push_back(object);
}

GameObject* Scene::GetGameObjectById(UUID id)
{
	return nullptr;
}

GameObject* Scene::GetFirstGameObjectByName(const std::string& name)
{
	return nullptr;
}

bool Scene::RemoveGameObject(GameObject* object)
{
	m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), object), m_gameObjects.end());
	return true;
}

bool Scene::RemoveGameObjectById(UUID id)
{
	return false;
}

void Scene::ActivateScene()
{
}

void Scene::DeactivateScene()
{
}

void Scene::Cleanup()
{
}

std::string Scene::GetName()
{
	return "";
}

void Scene::RemoveALlGameObjects()
{
}