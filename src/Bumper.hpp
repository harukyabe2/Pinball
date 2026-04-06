#pragma once
#include <Siv3D.hpp>

class Bumper
{
    public:
        Bumper(P2World& world, Polygon& polygon);

        void Update(const HashTable<P2ContactPair, P2Collision>& collisions);
        void Draw() const;
    private:
        // Physics
        P2Body mBody;
        P2BodyID mBodyID;

        // Bumper state
        Stopwatch mTimer;
};