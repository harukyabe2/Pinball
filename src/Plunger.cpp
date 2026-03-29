#include "Plunger.hpp"

Plunger::Plunger(P2World& world)
{
    mBody = world.createRect(P2Kinematic, Vec2{60, 200}, SizeF{30, 30});
}

void Plunger::Draw() const
{
    mBody.draw(Palette::Midnightblue);
}

void Plunger::SetPosition(const Vec2& pos)
{
    mBody.setPos(pos);
}
