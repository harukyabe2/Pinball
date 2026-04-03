#include "Game.hpp"

// Constructor
Game::Game()
: mCamera{Vec2{0, 0}, 1.0, CameraControl::None_}
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
    if (KeyF.down())
    {
        mStage.GetFlipper(true).PlaySound();
    }
    mKeyFIsPressed = KeyF.pressed();
    if (KeyJ.down())
    {
        mStage.GetFlipper(false).PlaySound();
    }
    mKeyJIsPressed = KeyJ.pressed();

    // Plunger control
    mKeySpaceIsPressed = KeySpace.pressed();
    if (KeySpace.up())
    {
        mStage.GetPlunger().PlaySound();
    }
}

// Update game state
void Game::UpdateGame()
{
    double deltaTime = Scene::DeltaTime();

    // Update stage elements
    mBall.SetState(true);
    mStage.Update(deltaTime, mBall, mKeySpaceIsPressed);

    // Update physics
    for (mAccumulatedTime += deltaTime; mStepTime <= mAccumulatedTime; mAccumulatedTime -= mStepTime)
    {
        mStage.UpdateFlippers(mKeyFIsPressed, mKeyJIsPressed);
        mWorld.update(mStepTime);

        // Update bumpers
        mStage.UpdateBumpers(mWorld.getCollisions());
    }

    // Check collisions and update score
    mScore += mStage.CheckItemCollisions(mBall.GetPos(), 12.0);

    // Check slot jackpot
    mScore += mStage.GetSlot().CheckJackpot();

    // Update items
    mStage.UpdateItems();

    // Check if the ball is out of bounds
    if (mBallCount > 0 && mBall.GetPos().y > 400)
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
    FontAsset(U"UI")(U"SCORE\n{:0>5}"_fmt(mScore)).drawAt(300, -300);
    FontAsset(U"UI")(U"BALL\n  {:0>2}"_fmt(mBallCount)).drawAt(300, -100);
}

// Load game data
void Game::LoadData()
{
    // Register font
    FontAsset::Register(U"UI", FontMethod::MSDF, 48, Typeface::Bold);

    // Register sound
    AudioAsset::Register(U"Coin", U"sound/ItemCoin.wav");
    AudioAsset::Register(U"Bumper", U"sound/Bumper.wav");
    AudioAsset::Register(U"Flipper", U"sound/Flipper.wav");
    AudioAsset::Register(U"Plunger", U"sound/Plunger.wav");
    
    // Register texture
    TextureAsset::Register(U"Seven", U"7️⃣"_emoji);
    TextureAsset::Register(U"Diamond", U"💎"_emoji);
    TextureAsset::Register(U"Trump", U"🃏"_emoji);
    TextureAsset::Register(U"Grape", U"🍇"_emoji);
    TextureAsset::Register(U"Cherry", U"🍒"_emoji);
    TextureAsset::Register(U"Trigger", U"👾"_emoji);
}


// Shutdown the game
void Game::Shutdown()
{
}