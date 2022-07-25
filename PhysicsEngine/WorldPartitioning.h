#pragma once
#include <vector>

#include "Maths/Vector3.h"

namespace Physics
{
    class PhysicsNode;
    struct CollisionPair;

    class WorldPartitioning
    {
    public:
        WorldPartitioning();
        WorldPartitioning(Vector3 min, Vector3 max, std::vector<PhysicsNode*> physicsNodes);
        virtual ~WorldPartitioning();
        
        virtual void AddPhysicsNode(PhysicsNode* physicsNode) const = 0;
        virtual void RemovePhysicsNode(PhysicsNode* physicsNode) const = 0;
        virtual std::vector<CollisionPair> GetCollisionPairs() const = 0;

        virtual void Update() = 0;
    protected:
    };

}
