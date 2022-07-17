#include "Camera.h"

Camera::~Camera()
{
	Window::GetKeyboard()->RemoveOnKeyDown(KEYBOARD_W, "CameraForward");
	Window::GetKeyboard()->RemoveOnKeyDown(KEYBOARD_S, "CameraBackward");
	Window::GetKeyboard()->RemoveOnKeyDown(KEYBOARD_A, "CameraLeft");
	Window::GetKeyboard()->RemoveOnKeyDown(KEYBOARD_D, "CameraRight");

	Window::GetKeyboard()->RemoveOnKeyUp(KEYBOARD_W, "CameraForward");
	Window::GetKeyboard()->RemoveOnKeyUp(KEYBOARD_S, "CameraBackward");
	Window::GetKeyboard()->RemoveOnKeyUp(KEYBOARD_A, "CameraLeft");
	Window::GetKeyboard()->RemoveOnKeyUp(KEYBOARD_D, "CameraRight");
}

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
		m_moveForward = false;
		
	}
	if (m_moveBack) 
	{
		position -= Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Vector3(0, 0, -1) * speed;
		m_moveBack = false;
	}

	if (m_moveLeft) 
	{
		position += Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Vector3(-1, 0, 0) * speed;
		m_moveLeft = false;
	}
	if (m_moveRight) 
	{
		position -= Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Vector3(-1, 0, 0) * speed;
		m_moveRight = false;
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
	Window::GetKeyboard()->AddOnKeyHeld(KEYBOARD_W, "CameraForward", [=] { m_moveForward = true; });
	Window::GetKeyboard()->AddOnKeyHeld(KEYBOARD_S, "CameraBackward", [=] { m_moveBack = true; });
	Window::GetKeyboard()->AddOnKeyHeld(KEYBOARD_A, "CameraLeft", [=] { m_moveLeft = true; });
	Window::GetKeyboard()->AddOnKeyHeld(KEYBOARD_D, "CameraRight", [=] { m_moveRight = true; });
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