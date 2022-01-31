#pragma once
#include "Engine/Scene.h"
#include <PhysicsEngine/CommonUtils.h>

class TestScene : public Scene
{
	virtual void ActivateScene() override
	{
		GameObject* ground = CommonUtils::BuildCuboidObject(
			"Ground",
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(5.0f, 1.0f, 5.0f),
			false,
			0.0f,
			false,
			false,
			Vector4(0.2f, 0.5f, 1.0f, 1.0f));

		this->AddGameObject(ground);

		ground->OnInitialise();
	}
};

