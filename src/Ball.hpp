#pragma once
#include <Siv3D.hpp>

class Ball
{
    public:
        Ball(P2World& world, const Vec2& pos, double radius);

        void Draw() const;

        void Delete();
        void AddImpulse(const Vec2& impulse);

        Vec2 GetPos() const;
        void SetPos(const Vec2& pos);
        void SetState(bool isAwake);
    private:
        // Physics
        P2Body mBody;
};