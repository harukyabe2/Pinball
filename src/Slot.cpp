#include "Slot.hpp"

// Constructor
Slot::Slot(const Vec2& pos)
: mSlotItems{U"Seven", U"Diamond", U"Trump", U"Grape", U"Cherry"}
, mCurrentIndexes{0, 2, 4}
, mResultIndex(0)
, mPos{pos}
, mIsSpinning(false)
, mIsAligned(false)
, mWillWin(false)
, mTimer()
{
}

// Update slot state
void Slot::Update()
{
    if (not mIsSpinning)
    {
        return;
    }

    // Blinking
    if (Periodic::Square0_1(0.1s)) 
    {
        mCurrentIndexes[0] = Random(0, 4);
        mCurrentIndexes[1] = Random(0, 4);
        mCurrentIndexes[2] = Random(0, 4);
    }

    // Stop spinning and determine result
    if (mTimer.sF() > 2.0)
    {
        mIsSpinning = false;
        mTimer.reset();

        if (mWillWin)
        {
            mCurrentIndexes[0] = mResultIndex;
            mCurrentIndexes[1] = mResultIndex;
            mCurrentIndexes[2] = mResultIndex;

            mIsAligned = true;
        }
        else
        {
            mCurrentIndexes[0] = Random(0, 4);
            mCurrentIndexes[1] = Random(0, 4);

            while (mCurrentIndexes[0] == mCurrentIndexes[1] && mCurrentIndexes[1] == mCurrentIndexes[2])
            {
                mCurrentIndexes[2] = Random(0, 4);
            }
        }
    }
}

// Draw slot
void Slot::Draw() const
{
    for (int32 i = 0; i < 3; ++i)
    {
        Vec2 drawPos = mPos + Vec2{-100.0 + (i * 100.0), 0};
        RoundRect{Arg::center = drawPos, 80, 120, 5}.drawFrame(3, Palette::White);
        TextureAsset(mSlotItems[mCurrentIndexes[i]]).scaled(0.4).drawAt(drawPos);
    }
}

// Spin slot and determine result
void Slot::StartSpin()
{
    if (mIsSpinning)
    {
        return;
    }

    mIsSpinning = true;
    mIsAligned = false;
    mWillWin = true;
    mTimer.restart();

    AudioAsset(U"Slot").playOneShot();

    double r = Random();

    if (r < 0.05)
    {
        // Seven
        mResultIndex = 0;
    }
    else if (r < 0.1)
    {
        // Diamond
        mResultIndex = 1;
    }
    else if (r < 0.15)
    {
        // Trump
        mResultIndex = 2;
    }
    else if (r < 0.2)
    {
        // Grape
        mResultIndex = 3;
    }
    else if (r < 0.3)
    {
        // Cherry
        mResultIndex = 4;
    }
    else
    {
        mWillWin = false;
    }
}

int32 Slot::CheckJackpot()
{
    if (not mIsAligned)
    {
        return 0;
    }

    mIsAligned = false;

    constexpr int32 SCORE[] = {
        1000, // Seven
        500,  // Diamond
        300,  // Trump
        200,  // Grape
        100   // Cherry
    };

    return SCORE[mCurrentIndexes[0]];
}