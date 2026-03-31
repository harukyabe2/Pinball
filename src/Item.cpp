#include "Item.hpp"

Item::Item(Vec2 pos, double r)
: mCircle(pos, r)
, mIsActive(true)
, mTimer(StartImmediately::Yes)
{
}

void Item::Update()
{
    if (not mIsActive && mTimer.sF() > 30.0)
    {
        mIsActive = true;
        mTimer.restart();
    }
}

void Item::Draw() const
{
    if (mIsActive)
    {
        mCircle.draw(Palette::Yellow);
        double blinkAlpha = Periodic::Square0_1(1.0s);
        mCircle.draw(ColorF{1.0, 1.0, 1.0, blinkAlpha});
    }
}

bool Item::CheckHit(const Vec2& ballPos, double ballRadius)
{
    if (!mIsActive)
    {
        return false;
    }

    if (mCircle.intersects(Circle{ballPos, ballRadius}))
    {
        AudioAsset(U"Coin").playOneShot();
        mIsActive = false;
        mTimer.restart();
        return true;
    }

    return false;
}