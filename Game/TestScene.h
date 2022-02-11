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
			Vector3(0.0f, 10.f, 0.f),
			2.f,
			true,
			true,
			2.f,
			true,
			false,
			Vector4(1.f, 0.f, 0.f, 1.f));

		this->AddGameObject(sphere);

		GameObject* sphere2 = CommonUtils::BuildSphereObject(
			"sphery2",
			Vector3(0.0f, 0.f, 0.f),
			2.f,
			true,
			false,
			0.f,
			true,
			false,
			Vector4(1.f, 0.f, 0.f, 1.f));

		this->AddGameObject(sphere2);

		ground->OnInitialise();
		sphere->OnInitialise();
		sphere2->OnInitialise();
	}
};

