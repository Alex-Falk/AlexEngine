#pragma once
#include "Engine/Interfaces/ISystem.h"
#include "Utils/Vector2.h"

class Tile;

namespace game
{    
    class GridSystem : public Ae::ISystem
    {
    static constexpr float c_tileSize = 1;
        
    public:
        GridSystem(Vector2F size);
    private:

        Vector2F m_size;
        Tile** m_tiles;
    };
}
