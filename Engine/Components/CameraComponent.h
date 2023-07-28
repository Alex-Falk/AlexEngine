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
	static std::string GetName() { return "CameraComponent"; }

private:
	void RegisterInput() const;
	void HandleInput(float dt) const;

	static constexpr const char* s_forwardKey = "camera_forward";
	static constexpr const char* s_backKey = "camera_back";
	static constexpr const char* s_leftKey = "camera_left";
	static constexpr const char* s_rightKey = "camera_right";

	static constexpr const char* s_upKey = "camera_up";
	static constexpr const char* s_downKey = "camera_down";
	static constexpr const char* s_speedKey = "camera_speed";

	float m_speed;
};
