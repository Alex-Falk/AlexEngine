#pragma once

namespace Ae
{
    class IUpdatable
    {
    public:
        virtual ~IUpdatable() = default;
        virtual void onUpdate(float dt) = 0;
    };
}