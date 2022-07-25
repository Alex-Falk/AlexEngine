#pragma once

#include <nclgl\TSingleton.h>
#include "Scene.h"

class SceneManager : public TSingleton<SceneManager>
{
	friend class TSingleton<SceneManager>;

public:
	void AddScene(Scene* scene);
	void RemoveScene(Scene* scene);

	bool GoToScene(const std::string& name);

	inline Scene* GetActiveScene() const { return m_scene; }

protected:
	SceneManager();
	~SceneManager() override;

private:
	Scene* m_scene;
	std::vector<Scene*> m_scenes;
};

