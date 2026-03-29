#pragma once
#include <Siv3D.hpp>

class Flipper
{
    public:
        Flipper(P2World& world, const Vec2& anchor, const Vec2& tipOffset, double lowerAngle, double upperAngle);

        void Draw() const;

        void AddTorque(double torque);
    private:
        P2Body mAnchorBody;
        P2Body mBody;
        P2PivotJoint mJoint;
};