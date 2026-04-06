#include "Item.hpp"

// Constant
constexpr double ITEM_COOLTIME = 15.0;

// Constructor
Item::Item(Vec2 pos, double r)
: mCircle(pos, r)
, mIsActive(true)
, mTimer()
{
}

// Update item state
void Item::Update()
{
    if (not mIsActive && mTimer.sF() > ITEM_COOLTIME)
    {
        mIsActive = true;
        mTimer.restart();
    }
}

// Draw item
void Item::Draw() const
{
    if (mIsActive)
    {
        mCircle.draw(Palette::Yellow);
        double blinkAlpha = Periodic::Square0_1(1.0s);
        mCircle.draw(ColorF{1.0, 1.0, 1.0, blinkAlpha});
    }
}

// Check if item is hit by ball
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