#pragma once
#include <Siv3D.hpp>
#include "Item.hpp"
#include "Bumper.hpp"
#include "Flipper.hpp"
#include "Plunger.hpp"
#include "Ball.hpp"

class Stage
{
    public:
        Stage(P2World& world);

        void Update(double deltaTime, Ball& ball, bool keySpace, bool keyF, bool keyJ);
        void Draw() const;

        void UpdateItems();
        int32 CheckItemCollisions(const Vec2& ballPos, double ballRadius);
    private:
        LineString mCreateCircleWall(const Vec2& center, double radius, double angleOffset, int32 segments);
        void LoadFirstStage(P2World& world);

        Array<P2Body> mWalls;
        Array<Bumper> mBumpers;
        Array<Item> mItems;
        Plunger mPlunger;
        double mCharge;
        Vec2 mLeftFlipperAnchor;
        Vec2 mRightFlipperAnchor;
        Flipper mLeftFlipper;
        Flipper mRightFlipper;
};