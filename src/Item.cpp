#include "Item.hpp"

Item::Item(Vec2 pos, double r)
: mCircle(pos, r)
, mIsActive(true)
{
}

void Item::Draw() const
{
    if (mIsActive)
    {
        mCircle.draw(Palette::Yellow);
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
        mIsActive = false;
        return true;
    }

    return false;
}