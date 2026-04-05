#pragma once
#include <Siv3D.hpp>

class Slot
{
    public:
        Slot() = default;
        Slot(const Vec2& pos);

        void Update();
        void Draw() const;

        void StartSpin();
        int32 CheckJackpot();
    private:
        Array<String> mSlotItems;
        Array<int32> mCurrentIndexes;
        int32 mResultIndex;
        Vec2 mPos;
        bool mIsSpinning;
        bool mIsAligned;
        bool mWillWin;
        Stopwatch mTimer;
};