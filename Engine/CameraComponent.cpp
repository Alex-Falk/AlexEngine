#include "CameraComponent.h"

#include "GameObject.h"
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
    Window::GetKeyboard()->AddKeyMapping(m_forwardBinding, KEYBOARD_W);
    Window::GetKeyboard()->AddKeyMapping(m_backBinding, KEYBOARD_S);
    Window::GetKeyboard()->AddKeyMapping(m_leftBinding,KEYBOARD_A);
    Window::GetKeyboard()->AddKeyMapping(m_rightBinding, KEYBOARD_D);
}

void CameraComponent::HandleInput(float dt)
{
    if (Window::GetKeyboard()->KeyDown(m_forwardBinding))
    {
        m_owner->TranslatePosition(Quaternion::FromMatrix(m_owner->GetTransform()).Transform(Vector3::Forward()));
    }
}
