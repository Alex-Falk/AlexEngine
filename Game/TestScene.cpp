#include "TestScene.h"

inline void TestScene::ActivateScene()
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

	this->AddGameObject(ground);

	GameObject* sphere = CommonUtils::BuildSphereObject(
		"sphery",
		Vector3(0.f, 20.f, 0.f),
		2.f,
		true,
		true,
		.5f,
		true,
		false,
		Vector4(1.f, 0.f, 0.f, 1.f));

	this->AddGameObject(sphere);

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
	//sphere2->OnInitialise();

}
