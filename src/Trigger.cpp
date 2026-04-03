#include "Trigger.hpp"

Trigger::Trigger(Vec2 centerPos, double orbitRadius, double hitRadius)
: mCircle(centerPos, hitRadius)
, mIsActive(true)
, mTimer(StartImmediately::Yes)
, mCenterPos(centerPos)
, mOrbitRadius(orbitRadius)
{
}

void Trigger::Update()
{
    if (not mIsActive && mTimer.sF() > 10.0)
    {
        mIsActive = true;
        mTimer.restart();
    }

    Vec2 circlePos = OffsetCircular(mCenterPos, mOrbitRadius, Scene::Time() * 60_deg);
    mCircle.setPos(circlePos);
}

void Trigger::Draw() const
{
    if (mIsActive)
    {
        TextureAsset(U"Trigger").scaled(0.4).drawAt(mCircle.center);
    }
}

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