#include "Slot.hpp"

Slot::Slot(const Vec2& pos)
: mSlotItems{U"Seven", U"Diamond", U"Trump", U"Grape", U"Cherry"}
, mCurrentIndexes{0, 2, 4}
, mPos{pos}
, mIsSpinning(false)
, mIsAligned(false)
, mTimer(StartImmediately::Yes)
{
}

void Slot::Update()
{
    if (not mIsSpinning)
    {
        return;
    }

    if (mTimer.sF() / 0.1 > 1) 
    {
        mCurrentIndexes[0] = Random(0, 4);
        mCurrentIndexes[1] = Random(0, 4);
        mCurrentIndexes[2] = Random(0, 4);
    }

    if (mTimer.sF() > 2.0)
    {
        mIsSpinning = false;
        mTimer.reset();

        if (mCurrentIndexes[0] == mCurrentIndexes[1] && mCurrentIndexes[1] == mCurrentIndexes[2])
        {
            mIsAligned = true;
        }
    }
}

void Slot::Draw() const
{
    for (int32 i = 0; i < 3; ++i)
    {
        Vec2 drawPos = mPos + Vec2{-100.0 + (i * 100.0), 0};
        RoundRect{Arg::center = drawPos, 80, 120, 5}.drawFrame(3, Palette::White);
        TextureAsset(mSlotItems[mCurrentIndexes[i]]).scaled(0.4).drawAt(drawPos);
    }
}

void Slot::StartSpin()
{
    if (mIsSpinning)
    {
        return;
    }

    mIsSpinning = true;
    mIsAligned = false;
    mTimer.restart();
}

int32 Slot::CheckJackpot()
{
    int32 score = 0;
    if (mIsAligned)
    {
        mIsAligned = false;

        if (mCurrentIndexes[0] == 0)
        {
            // Seven
            score = 1000;
        }
        else if (mCurrentIndexes[0] == 1)
        {
            // Diamond
            score = 500;
        }
        else if (mCurrentIndexes[0] == 2)
        {
            // Trump
            score = 300;
        }
        else if (mCurrentIndexes[0] == 3)
        {
            // Grape
            score = 200;
        }
        else if (mCurrentIndexes[0] == 4)
        {
            // Cherry
            score = 100;
        }
    }
    return score;
}