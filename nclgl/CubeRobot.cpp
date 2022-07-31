#include "CubeRobot.h"

//cube is a static class variable, and so must be initialised outside of the 
//class...here's as good a place as any!
Mesh* CubeRobot::cube = nullptr;

CubeRobot::CubeRobot(void)
{
	if (!cube)
	{
		CreateCube();
	}
	SetMesh(cube);

	//Make the body
	auto body = new RenderNode(cube, Vector4(1, 0, 0, 1));
	body->SetModelScale(Vector3(10, 15, 5));
	body->SetTransform(Maths::Matrix4::CreateTranslationMatrix(Vector3(0, 35, 0)));
	AddChild(body);

	//Add the head
	head = new RenderNode(cube, Vector4(0, 1, 0, 1));
	head->SetModelScale(Vector3(5, 5, 5));
	head->SetTransform(Maths::Matrix4::CreateTranslationMatrix(Vector3(0, 30, 0)));
	body->AddChild(head);

	//Add the left arm
	leftArm = new RenderNode(cube, Vector4(0, 0, 1, 1));
	leftArm->SetModelScale(Vector3(3, -18, 3));
	leftArm->SetTransform(Maths::Matrix4::CreateTranslationMatrix(Vector3(-12, 30, -1)));
	body->AddChild(leftArm);

	//Add the right arm
	rightArm = new RenderNode(cube, Vector4(0, 0, 1, 1));
	rightArm->SetModelScale(Vector3(3, -18, 3));
	rightArm->SetTransform(Maths::Matrix4::CreateTranslationMatrix(Vector3(12, 30, -1)));
	body->AddChild(rightArm);

	//Add the left leg
	leftLeg = new RenderNode(cube, Vector4(0, 0, 1, 1));
	leftLeg->SetModelScale(Vector3(3, -17.5, 3));
	leftLeg->SetTransform(Maths::Matrix4::CreateTranslationMatrix(Vector3(-8, 0, 0)));
	body->AddChild(leftLeg);

	//Finally the right leg!
	rightLeg = new RenderNode(cube, Vector4(0, 0, 1, 1));
	rightLeg->SetModelScale(Vector3(3, -17.5, 3));
	rightLeg->SetTransform(Maths::Matrix4::CreateTranslationMatrix(Vector3(8, 0, 0)));
	body->AddChild(rightLeg);

	//Giant CubeRobot!
	//transform = Matrix4::Scale(Vector3(10,10,10));

	//The Scene Management Tutorial introduces these, as cheap culling tests
	body->SetBoundingRadius(15.0f);
	head->SetBoundingRadius(5.0f);

	leftArm->SetBoundingRadius(18.0f);
	rightArm->SetBoundingRadius(18.0f);

	leftLeg->SetBoundingRadius(18.0f);
	rightLeg->SetBoundingRadius(18.0f);
}

void CubeRobot::Update(float msec)
{
	transform = transform * Maths::Matrix4::CreateRotationMatrix(msec / 10.0f, Vector3(0, 1, 0));

	head->SetTransform(Maths::Matrix4::CreateRotationMatrix(-msec / 10.0f, Vector3(0, 1, 0)) * head->GetTransform());
	leftArm->SetTransform(
		leftArm->GetTransform() * Maths::Matrix4::CreateRotationMatrix(-msec / 10.0f, Vector3(1, 0, 0)));
	rightArm->SetTransform(
		rightArm->GetTransform() * Maths::Matrix4::CreateRotationMatrix(msec / 10.0f, Vector3(1, 0, 0)));

	RenderNode::Update(msec);
}
