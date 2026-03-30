#include "Bumper.hpp"

Bumper::Bumper(P2World& world, Polygon polygon)
{
    P2Material material;
    material.restitution = 0.8;

    mBody = world.createPolygon(P2Static, Vec2{0, 0}, polygon, material);
}

void Bumper::Draw() const
{
    mBody.draw(Palette::Red);
}