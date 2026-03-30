#pragma once
#include <Siv3D.hpp>
#include "Ball.hpp"
#include "Flipper.hpp"
#include "Plunger.hpp"
#include "Stage.hpp"

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

        Font mFont;
        Camera2D mCamera;

        // Physics
        P2World mWorld;
        double mStepTime;
        double mAccumulatedTime;

        // Stage
        Stage mStage;

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

        // Game elements
        int32 mScore;
        int32 mBallCount;
        LineString mGameFrame;
};