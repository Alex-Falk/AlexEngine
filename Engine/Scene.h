#pragma once

#include "GameObject.h"
#include <string>
#include <vector>


class Scene
{
public:

	void AddGameObject(GameObject* object);

	GameObject* GetGameObjectById(UUID id);
	GameObject* GetFirstGameObjectByName(const std::string& name);

	bool RemoveGameObject(GameObject* object);
	bool RemoveGameObjectById(UUID id);

	void ActivateScene();
	void DeactivateScene();

	void Cleanup();

	std::string GetName();
	
		
protected:

	void RemoveALlGameObjects();

private:

	std::string m_name;
	std::vector<GameObject*> m_gameObjects;
};