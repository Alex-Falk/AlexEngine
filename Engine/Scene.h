#pragma once

#include "GameObject.h"
#include <string>
#include <vector>


class Scene
{
public:
	Scene();
	virtual ~Scene() = default;

	void AddGameObject(GameObject* object);

	GameObject* GetGameObjectById(UUID id);
	GameObject* GetFirstGameObjectByName(const std::string& name);

	bool RemoveGameObject(GameObject* object);
	bool RemoveGameObjectById(UUID id);

	virtual void ActivateScene();
	void DeactivateScene();

	void Cleanup();

	std::string GetName();

	void UpdateScene(float dt) const;


protected:
	void RemoveALlGameObjects();

	std::string m_name;

private:
	std::vector<GameObject*> m_gameObjects;
};
