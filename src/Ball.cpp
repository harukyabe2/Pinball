#include "Ball.hpp"

Ball::Ball(P2World& world)
{
    mBody = world.createCircle(P2Dynamic, Vec2{55.5, 0}, 12.0);
}

void Ball::Draw() const
{
    mBody.draw(Palette::White);
}

void Ball::Delete()
{
    mBody.release();
}

void Ball::AddImpulse(const Vec2& impulse)
{
    mBody.applyLinearImpulse(impulse);
}

const Vec2 Ball::GetPosition()
{
    return mBody.getPos();
}

void Ball::SetPosition(const Vec2& pos)
{
    mBody.setPos(pos);
}

void Ball::SetState(bool isAwake)
{
    mBody.setAwake(isAwake);
}