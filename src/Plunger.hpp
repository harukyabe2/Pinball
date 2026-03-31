#pragma once
#include <Siv3D.hpp>

class Plunger
{
    public:
        Plunger() = default;
        Plunger(P2World& world, const Vec2& pos, const SizeF& size);

        void Draw() const;

        void PlaySound() const;

        void SetPosition(const Vec2& pos);
    private:
        P2Body mBody;
};