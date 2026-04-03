#pragma once
#include <Siv3D.hpp>

class Trigger
{
    public:
        Trigger() = default;
        Trigger(Vec2 centerPos, double orbitRadius, double hitRadius);

        void Update();
        void Draw() const;

        bool CheckHit(const Vec2& ballPos, double ballRadius);
    private:
        Circle mCircle;
        bool mIsActive;
        Stopwatch mTimer;
        Vec2 mCenterPos;
        double mOrbitRadius;
};