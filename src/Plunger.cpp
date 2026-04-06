#include "Plunger.hpp"

// Constructor
Plunger::Plunger(P2World& world, const Vec2& pos, const SizeF& size)
: mBody(world.createRect(P2Kinematic, pos, size))
{
}

// Draw plunger
void Plunger::Draw() const
{
    mBody.draw(Palette::Midnightblue);
}

// Set plunger pos
void Plunger::SetPosition(const Vec2& pos)
{
    mBody.setPos(pos);
}
