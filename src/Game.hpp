#pragma once
#include <Siv3D.hpp>

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
};