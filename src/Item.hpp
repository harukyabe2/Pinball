#pragma once
#include <Siv3D.hpp>

class Item
{
    public:
        Item(Vec2 pos, double r);

        void Update();
        void Draw() const;

        bool CheckHit(const Vec2& ballPos, double ballRadius);
    private:
        // Collision
        Circle mCircle;

        // Circle state
        bool mIsActive;
        Stopwatch mTimer;
};