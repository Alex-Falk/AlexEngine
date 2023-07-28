#include "CameraComponent.h"

#include "Engine/GameObject.h"
#include "nclgl/GraphicsPipeline.h"
#include "nclgl/Window.h"

CameraComponent::CameraComponent(): Component("CameraComponent"), m_speed(3.5f)
{
}

void CameraComponent::OnInitialise()
{
	RegisterInput();
}

void CameraComponent::OnUpdate(float dt)
{
	HandleInput(dt);
	GraphicsPipeline::Instance()->GetCamera()->SetPosition(m_owner->GetTransform().GetPositionVector());
}

void CameraComponent::RegisterInput() const
{
	Window::GetKeyboard()->AddKeyMapping(s_forwardKey, KEYBOARD_W);
	Window::GetKeyboard()->AddKeyMapping(s_backKey, KEYBOARD_S);
	Window::GetKeyboard()->AddKeyMapping(s_leftKey, KEYBOARD_A);
	Window::GetKeyboard()->AddKeyMapping(s_rightKey, KEYBOARD_D);
	Window::GetKeyboard()->AddKeyMapping(s_upKey, KEYBOARD_E);
	Window::GetKeyboard()->AddKeyMapping(s_downKey, KEYBOARD_Q);
	Window::GetKeyboard()->AddKeyMapping(s_speedKey, KEYBOARD_SHIFT);
}

void CameraComponent::HandleInput(float dt) const
{
	auto speed = m_speed;
	if (Window::GetKeyboard()->KeyHeld(s_speedKey))
	{
		speed *= 2;
	}
	if (Window::GetKeyboard()->KeyDown(s_forwardKey))
	{
		m_owner->TranslateLocalPosition(-Vector3::Forward() * speed);
	}

	if (Window::GetKeyboard()->KeyDown(s_leftKey))
	{
		m_owner->TranslateLocalPosition(-Vector3::Right() * speed);
	}

	if (Window::GetKeyboard()->KeyDown(s_rightKey))
	{
		m_owner->TranslateLocalPosition(Vector3::Right() * speed);
	}

	if (Window::GetKeyboard()->KeyDown(s_backKey))
	{
		m_owner->TranslateLocalPosition(Vector3::Forward() * speed);
	}

	if (Window::GetKeyboard()->KeyDown(s_upKey))
	{
		m_owner->TranslateLocalPosition(Vector3::Up() * speed);
	}

	if (Window::GetKeyboard()->KeyDown(s_downKey))
	{
		m_owner->TranslateLocalPosition(-Vector3::Up() * speed);
	}

	if (Window::GetMouse()->ButtonHeld(MOUSE_RIGHT))
	{
		auto pitchChange = (Window::GetMouse()->GetRelativePosition().y) * 10.f;
		auto yawChange = (Window::GetMouse()->GetRelativePosition().x) * 10.f;

		pitchChange = Maths::Min(pitchChange, 90.f);
		pitchChange = Maths::Max(pitchChange, -90.f);

		if (yawChange < 0.0f)
		{
			yawChange += 360.0f;
		}
		if (yawChange > 360.0f)
		{
			yawChange -= 360.0f;
		}

		m_owner->Rotate(pitchChange, yawChange, 0);
	}
}
