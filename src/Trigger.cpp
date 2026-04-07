#include "Trigger.hpp"

// Constants
constexpr double TRIGGER_COOLTIME = 5.0;
constexpr double ROTATION_SPEED = 60_deg;

// Constructor
Trigger::Trigger(Vec2 centerPos, double orbitRadius, double hitRadius)
: mCircle(centerPos, hitRadius)
, mIsActive(true)
, mTimer()
, mCenterPos(centerPos)
, mOrbitRadius(orbitRadius)
{
}

// Update triger state
void Trigger::Update()
{
    if (not mIsActive && mTimer.sF() > TRIGGER_COOLTIME)
    {
        mIsActive = true;
        mTimer.reset();
    }

    Vec2 circlePos = OffsetCircular(mCenterPos, mOrbitRadius, Scene::Time() * ROTATION_SPEED);
    mCircle.setPos(circlePos);
}

// Draw trigger
void Trigger::Draw() const
{
    if (mIsActive)
    {
        TextureAsset(U"Trigger").scaled(0.4).drawAt(mCircle.center);
    }
}

// Reset trigger state
void Trigger::Reset()
{
    mIsActive = true;
    mTimer.reset();
}

// Check if trigger is hit by ball
bool Trigger::CheckHit(const Vec2& ballPos, double ballRadius)
{
    if (!mIsActive)
    {
        return false;
    }

    if (mCircle.intersects(Circle{ballPos, ballRadius}))
    {
        mIsActive = false;
        mTimer.restart();
        return true;
    }

    return false;
}