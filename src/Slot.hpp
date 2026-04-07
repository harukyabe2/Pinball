#pragma once
#include <Siv3D.hpp>

class Slot
{
    public:
        Slot() = default;
        Slot(const Vec2& pos);

        void Update();
        void Draw() const;
        void Reset();

        void StartSpin();
        int32 CheckJackpot();
    private:
        // Slot items
        String mSlotItems[5];
        int32 mCurrentIndexes[3];
        int32 mResultIndex;

        // Slot pos
        Vec2 mPos;

        // Slot state
        bool mIsSpinning;
        bool mIsAligned;
        bool mWillWin;
        Stopwatch mTimer;
};