#pragma once

namespace ae
{
    class IUpdatable
    {
    public:
        virtual ~IUpdatable() = default;
        virtual void OnUpdate(float dt) = 0;
    };
}