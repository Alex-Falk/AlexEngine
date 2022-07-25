#pragma once
#include "Component.h"

/**
 * \brief This component should wrap around the nclgl::Camera and take some of the functionality out of there
 * Maily I don't want the Input to go directly to teh nclgl::Camera
 */
class CameraComponent : public Component
{
public:
 CameraComponent();
 
 void OnInitialise() override;
 void OnUpdate(float dt) override;
 inline static std::string GetName() { return "CameraComponent"; }

private:
 void RegisterInput() const;
 void HandleInput(float dt);

 std::string m_forwardBinding = GetName() + "_Forward" ;
 std::string m_backBinding = GetName() + "_Back" ;
 std::string m_leftBinding = GetName() + "_Left" ;
 std::string m_rightBinding = GetName() + "_Right" ;

 float m_speed;
};
