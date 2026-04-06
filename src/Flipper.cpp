#include "Flipper.hpp"

// Constructor
Flipper::Flipper(P2World& world, const Vec2& anchor, const Vec2& tipOffset, double lowerAngle, double upperAngle)
{
    LineString flipperLine;
    flipperLine << Vec2{0, 0} << tipOffset;
    Polygon flipperShape = flipperLine.calculateRoundBuffer(5.0);

    P2Material material;
    material.density = 0.3;

    mAnchorBody = world.createCircle(P2Static, anchor, 1.0);
    mBody = world.createPolygon(P2Dynamic, anchor, flipperShape, material, P2Filter{0x0004, 0x0001});
    mJoint = world.createPivotJoint(mAnchorBody, mBody, anchor).setLimits(lowerAngle, upperAngle).setLimitsEnabled(true);
}

// Draw flipper
void Flipper::Draw() const
{
    mBody.draw(Palette::White);
}

// Apply torque to flipper
void Flipper::AddTorque(double torque)
{
    mBody.applyTorque(torque);
}
