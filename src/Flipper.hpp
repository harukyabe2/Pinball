#pragma once
#include <Siv3D.hpp>

class Flipper
{
    public:
        Flipper() = default;
        Flipper(P2World& world, const Vec2& anchor, const Vec2& tipOffset, double lowerAngle, double upperAngle);

        void Draw() const;

        void AddTorque(double torque);
    private:
        // Physics
        P2Body mAnchorBody;
        P2Body mBody;
        P2PivotJoint mJoint;
};