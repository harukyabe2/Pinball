#include "Plunger.hpp"

Plunger::Plunger(P2World& world, const Vec2& pos, const SizeF& size)
{
    mBody = world.createRect(P2Kinematic, pos, size);
}

void Plunger::Draw() const
{
    mBody.draw(Palette::Midnightblue);
}

void Plunger::PlaySound() const
{
    AudioAsset(U"Plunger").playOneShot();
}

void Plunger::SetPosition(const Vec2& pos)
{
    mBody.setPos(pos);
}
