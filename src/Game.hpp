#pragma once
#include <Siv3D.hpp>
#include "Ball.hpp"
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

        // Ball
        Ball mBall;

        // Stage
        Stage mStage;

        // Process input
        bool mKeyFIsPressed;
        bool mKeyJIsPressed;
        bool mKeySpaceIsPressed;

        // Game elements
        int32 mScore;
        int32 mBallCount;
        LineString mGameFrame;
};