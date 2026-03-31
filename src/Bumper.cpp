#include "Bumper.hpp"

Bumper::Bumper(P2World& world, Polygon polygon)
: mTimer(StartImmediately::Yes)
{
    P2Material material;
    material.restitution = 0.8;

    mBody = world.createPolygon(P2Static, Vec2{0, 0}, polygon, material);
    mBodyID = mBody.id();

    mPolygon = polygon;
}

void Bumper::Update(const HashTable<P2ContactPair, P2Collision>& collisions)
{
    bool isCollided = false;

    for (auto&& [pair, collision] : collisions)
	{
				if (pair.a == mBodyID)
				{
                    isCollided = true;
				}
				else if (pair.b == mBodyID)
				{
                    isCollided = true;
				}
	}

    if (isCollided && mTimer.sF() > 0.1)
    {
        mTimer.restart();
        AudioAsset(U"Bumper").playOneShot();
    }
}

void Bumper::Draw() const
{
    mBody.draw(Palette::Red);
}