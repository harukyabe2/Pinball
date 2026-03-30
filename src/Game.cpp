#include "Game.hpp"

// Constructor
Game::Game()
: mFont{FontMethod::MSDF, 48, Typeface::Bold}
, mCamera{Vec2{0, 0}, 1.0, CameraControl::None_}
, mStepTime(1.0 / 200.0)
, mAccumulatedTime(0.0)
, mBall(mWorld)
, mStage(mWorld)
, mKeyFIsPressed(false)
, mKeyJIsPressed(false)
, mKeySpaceIsPressed(false)
, mScore(0)
, mBallCount(3)
, mGameFrame{
    Vec2{-500, -400},
    Vec2{-500, 400},
    Vec2{100, 400},
    Vec2{100, -400},
  }
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
    // Flipper controls
    mKeyFIsPressed = KeyF.pressed();
    mKeyJIsPressed = KeyJ.pressed();

    // Plunger control
    mKeySpaceIsPressed = KeySpace.pressed();
}

// Update game state
void Game::UpdateGame()
{
    double deltaTime = Scene::DeltaTime();

    // Update stage elements
    mBall.SetState(true);
    mStage.Update(deltaTime, mBall, mKeySpaceIsPressed, mKeyFIsPressed, mKeyJIsPressed);

    // Update physics
    for (mAccumulatedTime += deltaTime; mStepTime <= mAccumulatedTime; mAccumulatedTime -= mStepTime)
    {
        mWorld.update(mStepTime);
    }

    // Check collisions and update score
    mScore += mStage.CheckItemCollisions(mBall.GetPosition(), 12.0);

    // Update items
    mStage.UpdateItems();

    // Check if the ball is out of bounds
    if (mBallCount > 0 && mBall.GetPosition().y > 400)
    {
        mBall.Delete();
        --mBallCount;
        if (mBallCount > 0)
        {
            mBall = Ball(mWorld);
        }
    }
}

// Render the game
void Game::GenerateOutput()
{
    Scene::SetBackground(Palette::Black);

    const auto t = mCamera.createTransformer();

    mStage.Draw();
    mBall.Draw();
    mGameFrame.drawClosed(5, Palette::White);

    // Draw game elements
    mFont(U"SCORE\n{:0>5}"_fmt(mScore)).drawAt(300, -300);
    mFont(U"BALL\n  {:0>2}"_fmt(mBallCount)).drawAt(300, -100);
}

// Load game data
void Game::LoadData()
{
}


// Shutdown the game
void Game::Shutdown()
{
}