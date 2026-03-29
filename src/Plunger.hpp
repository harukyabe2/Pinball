#pragma once
#include <Siv3D.hpp>

class Plunger
{
    public:
        Plunger(P2World& world);

        void Draw() const;

        void SetPosition(const Vec2& pos);
    private:
        P2Body mBody;
};