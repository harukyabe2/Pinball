#pragma once
#include <Siv3D.hpp>

#define sceneW Scene::Width()
#define sceneH Scene::Height()

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

        Stopwatch mGameTimer;
        Font mFont;
        Camera2D mCamera;

        int32 mScore;
        int32 mBallCount;
};