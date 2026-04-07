#pragma once
#include <Siv3D.hpp>
#include "Item.hpp"
#include "Bumper.hpp"
#include "Flipper.hpp"
#include "Plunger.hpp"
#include "Ball.hpp"
#include "Slot.hpp"
#include "Trigger.hpp"

class Stage
{
    public:
        Stage(P2World& world);

        void Update(double deltaTime, Ball& ball, bool keySpace);
        void Draw() const;
        void Reset();

        void UpdateBumpers(const HashTable<P2ContactPair, P2Collision>& collisions);
        void UpdateItems();
        void UpdateFlippers(bool keyF, bool keyJ);
        int32 CheckItemCollisions(const Vec2& ballPos, double ballRadius);
        int32 CheckSlotJackpot();
        void PlayFlipperSound();
        void PlayPlungerSound();
    private:
        LineString CreateCircleWall(const Vec2& center, double radius, double angleOffset, int32 segments) const;
        void LoadFirstStage(P2World& world);

        // Flippers
        Vec2 mLeftFlipperAnchor;
        Vec2 mRightFlipperAnchor;
        Flipper mLeftFlipper;
        Flipper mRightFlipper;

        // Plunger
        Plunger mPlunger;
        double mCharge;

        // Walls
        Array<P2Body> mWalls;

        // Bumpers
        Array<Bumper> mBumpers;

        // Items
        Array<Item> mItems;

        // Slot
        Slot mSlot;

        // Trigger
        Trigger mTrigger;
};