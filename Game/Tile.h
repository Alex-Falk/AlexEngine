#pragma once
#include "Engine/Interfaces/IUpdatable.h"

class Tile : public Ae::IUpdatable
{
public:
    void onUpdate(float dt) override;

private:
    
};
