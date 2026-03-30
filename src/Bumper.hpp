#pragma once
#include <Siv3D.hpp>

class Bumper
{
    public:
        Bumper(P2World& world, Polygon polygon);

        void Draw() const;
    private:
        P2Body mBody;
};