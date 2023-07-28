#pragma once
#include "Engine/Interfaces/IUpdatable.h"

class Tile : public ae::IUpdatable
{
public:
    void OnUpdate(float dt) override;

private:
    
};
