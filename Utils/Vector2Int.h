#pragma once

class Vector2Int
{
public:
    int x;
    int y;

    Vector2Int() = default;
    Vector2Int(int x, int y);
    Vector2Int(const Vector2Int& other) = default;
};
