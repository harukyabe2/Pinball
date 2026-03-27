#include "Game.hpp"

// Constructor
Game::Game()
: mGameTimer{StartImmediately::Yes}
, mFont{FontMethod::MSDF, 48, Typeface::Bold}
, mCamera{Vec2{0, 0}, 1.0, CameraControl::None_}
, mScore(0)
, mBallCount(3)
{

}

// Initialize the game
bool Game::Initialize()
{
    // Set up the window
    Window::SetStyle(WindowStyle::Sizable);
    Window::Maximize();
    Window::SetTitle(U"Pinball Game");

    LoadData();
    return true;
}

// Main game loop
void Game::RunLoop()
{
    while (System::Update())
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

// Process user input
void Game::ProcessInput()
{

}

// Update game state
void Game::UpdateGame()
{

}

// Render the game
void Game::GenerateOutput()
{
    Scene::SetBackground(Palette::Black);

    const auto t = mCamera.createTransformer();

    // Draw game elements
    mFont(U"SCORE\n{:0>5}"_fmt(mScore)).drawAt(sceneW / 2 - 300, sceneH / 2 - 600);
    mFont(U"BALL\n  {:0>2}"_fmt(mBallCount)).drawAt(sceneW / 2 - 300, sceneH / 2 - 200);
}

// Load game data
void Game::LoadData()
{

}

// Shutdown the game
void Game::Shutdown()
{

}