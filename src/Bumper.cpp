#include "Bumper.hpp"

// Constructor
Bumper::Bumper(P2World& world, Polygon& polygon)
: mTimer()
{
    P2Material material;
    material.restitution = 0.8;

    mBody = world.createPolygon(P2Static, Vec2{0, 0}, polygon, material);
    mBodyID = mBody.id();
}

// Update bumper state
void Bumper::Update(const HashTable<P2ContactPair, P2Collision>& collisions)
{
    bool isCollided = false;

    for (auto&& [pair, collision] : collisions)
	{
		if (pair.a == mBodyID || pair.b == mBodyID)
		{                
            isCollided = true;
            break;
		}
	}

    if (isCollided && (not mTimer.isRunning() || mTimer.sF() > 0.1))
    {
        mTimer.restart();
        AudioAsset(U"Bumper").playOneShot();
    }
}

// Draw bumper
void Bumper::Draw() const
{
    mBody.draw(Palette::Red);

    if (mTimer.isRunning() && mTimer.sF() < 0.20)
    {
        mBody.draw(Palette::White);
    }
}