#pragma once
#include "Engine/Scene.h"
#include "Engine/CommonUtils.h"

class TestScene : public Scene
{
public:
	TestScene(std::string name)
	{
		m_name = name;
	}

	virtual void ActivateScene() override
	{
		GameObject* ground = CommonUtils::BuildCuboidObject(
			"Ground",
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(5.0f, 1.0f, 5.0f),
			false,
			false,
			0.0f,
			false,
			false,
			Vector4(0.2f, 0.5f, 1.0f, 1.0f));

		this->AddGameObject(ground);

		GameObject* sphere = CommonUtils::BuildSphereObject(
			"sphery",
			Vector3(0.0f, 4.f, 0.f),
			2.f,
			true,
			true,
			1,
			false,
			false,
			Vector4(1.f, 0.f, 0.f, 1.f));

		this->AddGameObject(sphere);

		ground->OnInitialise();
		sphere->OnInitialise();
	}
};

