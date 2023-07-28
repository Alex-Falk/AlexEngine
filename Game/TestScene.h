#pragma once
#include "Engine/MessageSystem.h"
#include "Engine/Components/CameraComponent.h"
#include "Engine/Scene.h"
#include "Engine/Common/CommonUtils.h"
#include "Engine/SphereObject.h"

class TestScene : public Scene
{
public:
	TestScene(std::string name)
	{
		m_name = name;
	}

	void ActivateScene() override
	{
		GameObject* ground = CommonUtils::BuildCuboidObject(
			"Ground",
			Vector3(0.0f, 0.0f, 0.0f),
			Vector3(25.0f, 1.0f, 25.0f),
			true,
			false,
			0.0f,
			true,
			false,
			Vector4(0.2f, 0.5f, 1.0f, 1.0f));

		ground->SetRotation(Maths::Quaternion::EulerAnglesToQuaternion(30, 30, 30));
		this->AddGameObject(ground);

		auto sphere = new SphereObject(
			Vector3(0.f, 20.f, 0.f),
			2.f,
			true,
			10.f,
			Vector4(1.f, 0.f, 0.f, 1.f));

		this->AddGameObject(sphere);

		auto cam = CommonUtils::BuildCameraObject("cam", Vector3(5, 5, 5));
		this->AddGameObject(cam);

		//GameObject* sphere2 = CommonUtils::BuildSphereObject(
		//	"sphery2",
		//	Vector3(5.f, 5.f, 5.f),
		//	2.f,
		//	true,
		//	true,
		//	1.f,
		//	true,
		//	false,
		//	Vector4(1.f, 0.f, 0.f, 1.f));

		//this->AddGameObject(sphere2);

		ground->OnInitialise();
		sphere->OnInitialise();
		cam->OnInitialise();
		//sphere2->OnInitialise();

		const ae::MessageCallback func = [this](ae::Message& msg) { OnMessageRecieved(msg); };
		//ae::MessageSystem::Instance()->subscribe<ae::Message>(func);

		ae::Message msg = ae::Message();
		//ae::MessageSystem::Instance()->addMessage(msg);
	}

	void OnMessageRecieved(ae::Message& msg)
	{
		NCLDebug::Log("hello there");
	}
};
