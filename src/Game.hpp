#pragma once
#include <Siv3D.hpp>
#include "Ball.hpp"
#include "Stage.hpp"

// Game state
enum class GameState
{
    isPlaying,
    isGameOver
};

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
        void GenerateOutput() const;
        void LoadData();

        // Game state
        GameState mState;

        // Camera
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
        bool mKeyCIsPressed;
        bool mKeyEIsPressed;

        // Game elements
        int32 mScore;
        int32 mBallCount;
        LineString mGameFrame;
};