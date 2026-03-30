#pragma once
#include <Siv3D.hpp>
#include "Item.hpp"
#include "Bumper.hpp"

class Stage
{
    public:
        Stage(P2World& world);

        void Update();
        void Draw() const;

        int32 CheckItemCollisions(const Vec2& ballPos, double ballRadius);
    private:
        LineString mCreateCircleWall(const Vec2& center, double radius, double angleOffset, int32 segments);
        void LoadStage(P2World& world);

        Array<P2Body> mWalls;
        Array<Bumper> mBumpers;
        Array<Item> mItems;
};