#pragma once
#include <Siv3D.hpp>

class Trigger
{
    public:
        Trigger() = default;
        Trigger(Vec2 centerPos, double orbitRadius, double hitRadius);

        void Update();
        void Draw() const;
        void Reset();

        bool CheckHit(const Vec2& ballPos, double ballRadius);
    private:
        // Collision
        Circle mCircle;

        // Circle state
        bool mIsActive;
        Stopwatch mTimer;

        // Parameters
        Vec2 mCenterPos;
        double mOrbitRadius;
};