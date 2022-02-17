#pragma once
#include "Engine/Scene.h"
#include "Engine/CommonUtils.h"
#include <Engine/GridSystem.h>

class TestScene : public Scene
{
public:
	TestScene(std::string name)
	{
		m_name = name;
	}

	virtual void ActivateScene() override;


private:
	GridSystem<64, 64> Grid = GridSystem<64, 64>(1.f);
};

