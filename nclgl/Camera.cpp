#include "Camera.h"

/*
Polls the camera for keyboard / mouse movement.
Should be done once per frame! Pass it the msec since
last frame (default value is for simplicities sake...)
*/
void Camera::HandleMouse(float dt)
{

	//Update the mouse by how much
	if (Window::GetMouse()->ButtonDown(MOUSE_LEFT))
	{
		pitch -= (Window::GetMouse()->GetRelativePosition().y);
		yaw -= (Window::GetMouse()->GetRelativePosition().x);
	}

	//float wheel_speed = Window::GetMouse()->GetWheelMovement() * 0.5f;
	//Matrix4 rotation = Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Matrix4::Rotation(pitch, Vector3(1, 0, 0));
	//position += rotation * Vector3(0, 0, -1) * wheel_speed;


	//Bounds check the pitch, to be between straight up and straight down ;)
	pitch = min(pitch, 90.0f);
	pitch = max(pitch, -90.0f);

	if (yaw < 0.0f) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
}

void Camera::HandleKeyboard(float dt)
{
	float speed = 3.5f * dt;	//3.5m per second


								//Bounds check the pitch, to be between straight up and straight down ;)
	if (yaw <0) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}


	if (m_moveForward) 
	{
		position += Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Vector3(0, 0, -1) * speed;
	}
	if (m_moveBack) 
	{
		position -= Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Vector3(0, 0, -1) * speed;
	}

	if (m_moveLeft) 
	{
		position += Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Vector3(-1, 0, 0) * speed;
	}
	if (m_moveRight) 
	{
		position -= Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Vector3(-1, 0, 0) * speed;
	}

	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
		position.y += speed;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
		position.y -= speed;
	}
}

void Camera::RegisterKeys()
{
	Window::GetKeyboard()->AddOnKeyDown(KEYBOARD_W, "CameraForward", [=] { m_moveForward = true; });
	Window::GetKeyboard()->AddOnKeyDown(KEYBOARD_S, "CameraBackward", [=] { m_moveBack = true; });
	Window::GetKeyboard()->AddOnKeyDown(KEYBOARD_A, "CameraLeft", [=] { m_moveLeft = true; });
	Window::GetKeyboard()->AddOnKeyDown(KEYBOARD_D, "CameraRight", [=] { m_moveRight = true; });

	Window::GetKeyboard()->AddOnKeyUp(KEYBOARD_W, "CameraForward", [=] { m_moveForward = false; });
	Window::GetKeyboard()->AddOnKeyUp(KEYBOARD_S, "CameraBackward", [=] { m_moveBack = false; });
	Window::GetKeyboard()->AddOnKeyUp(KEYBOARD_A, "CameraLeft", [=] { m_moveLeft = false; });
	Window::GetKeyboard()->AddOnKeyUp(KEYBOARD_D, "CameraRight", [=] { m_moveRight = false; });
}

/*
Generates a view matrix for the camera's viewpoint. This matrix can be sent
straight to the shader...it's already an 'inverse camera' matrix.
*/
Matrix4 Camera::BuildViewMatrix() {
	//Why do a complicated matrix inversion, when we can just generate the matrix
	//using the negative values ;). The matrix multiplication order is important!
	return	Matrix4::Rotation(-pitch, Vector3(1, 0, 0)) *
		Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) *
		Matrix4::Translation(-position);
};

Vector3 Camera::GetViewDirection() {
	return Matrix3::Rotation(pitch, Vector3(1, 0, 0)) * Matrix3::Rotation(yaw, Vector3(0, 1, 0)) * Vector3(0, 0, -1);
}