#pragma once
#include <Siv3D.hpp>
#include "Ball.hpp"
#include "Flipper.hpp"
#include "Plunger.hpp"
#include "Bumper.hpp"

#define SCENEW Scene::Width()
#define SCENEH Scene::Height()

class Game
{
    public:
        Game();
        bool Initialize();
        void RunLoop();
        void Shutdown();
    private:
        void ProcessInput();
        void UpdateGame();
        void GenerateOutput();
        void LoadData();

        LineString mCreateCircleFrame(const Vec2& center, double radius, double angleOffset, int32 segments);

        Stopwatch mGameTimer;
        Font mFont;
        Camera2D mCamera;

        // Physics
        P2World mWorld;
        double mStepTime;
        double mAccumulatedTime;

        // Flipper
        Vec2 mLeftFlipperAnchor;
        Vec2 mRightFlipperAnchor;
        Flipper mLeftFlipper;
        Flipper mRightFlipper;

        // Process input
        bool mKeyFIsPressed;
        bool mKeyJIsPressed;
        bool mKeySpaceIsPressed;

        // Ball
        Ball mBall;

        // Plunger
        Plunger mPlunger;
        double mCharge;

        // Bumper
        Array<Bumper> mBumpers;

        // Game elements
        int32 mScore;
        int32 mBallCount;
        LineString mGameFrame;
        Array<P2Body> mFrames;
};