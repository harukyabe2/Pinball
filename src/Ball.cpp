#include "Ball.hpp"

// Constructor
Ball::Ball(P2World& world, const Vec2& pos, double radius)
: mBody(world.createCircle(P2Dynamic, pos, radius))
{
}

// Draw ball
void Ball::Draw() const
{
    mBody.draw(Palette::White);
}

// Delete ball
void Ball::Delete()
{
    mBody.release();
}

// Apply impulse to ball
void Ball::AddImpulse(const Vec2& impulse)
{
    mBody.applyLinearImpulse(impulse);
}

// Get ball pos
Vec2 Ball::GetPos() const
{
    return mBody.getPos();
}

// Set ball pos
void Ball::SetPos(const Vec2& pos)
{
    mBody.setPos(pos);
}

// Set ball state
void Ball::SetState(bool isAwake)
{
    mBody.setAwake(isAwake);
}