#pragma once
#include <Siv3D.hpp>

class Ball
{
    public:
        Ball(P2World& world);

        void Draw() const;

        void Delete();
        void AddImpulse(const Vec2& impulse);

        const Vec2 GetPosition();
        void SetPosition(const Vec2& pos);
        void SetState(bool isAwake);
    private:
        P2Body mBody;
};