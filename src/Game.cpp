#include "Game.hpp"

// Constructor
Game::Game()
: mGameTimer{StartImmediately::Yes}
, mFont{FontMethod::MSDF, 48, Typeface::Bold}
, mCamera{Vec2{0, 0}, 1.0, CameraControl::None_}
, mStepTime(1.0 / 200.0)
, mAccumulatedTime(0.0)
, mStage(mWorld)
, mLeftFlipperAnchor(-320, 360)
, mRightFlipperAnchor(-180, 360)
, mLeftFlipper(mWorld, mLeftFlipperAnchor, Vec2{50, 0}, -20_deg, 20_deg)
, mRightFlipper(mWorld, mRightFlipperAnchor, Vec2{-50, 0}, -20_deg, 20_deg)
, mKeyFIsPressed(false)
, mKeyJIsPressed(false)
, mKeySpaceIsPressed(false)
, mBall(mWorld)
, mPlunger(mWorld)
, mCharge(0.0)
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
    if (KeyF.pressed())
    {
        mKeyFIsPressed = true;
    }
    else
    {
        mKeyFIsPressed = false;
    }
    if (KeyJ.pressed())
    {
        mKeyJIsPressed = true;
    }
    else
    {
        mKeyJIsPressed = false;
    }

    // Plunger control
    mKeySpaceIsPressed = KeySpace.pressed();
}

// Update game state
void Game::UpdateGame()
{
    double deltaTime = Scene::DeltaTime();

    // Update plunger and ball
    Vec2 plungerPos = Vec2{60, 200};
    if (mKeySpaceIsPressed)
    {
        mCharge += 180.0 * deltaTime;
        if (mCharge > 180.0)
        {
            mCharge = 180.0;
        }
        mBall.SetState(true);
        mPlunger.SetPosition(plungerPos + Vec2{0, mCharge});
    }
    else if (mCharge > 0.0)
    {
        if (mBall.GetPosition().x > 50 && mBall.GetPosition().y > 0)
        {
            mBall.SetPosition(plungerPos);
            double impulse = -1 * mCharge;
            mBall.AddImpulse(Vec2{0, impulse});
        }
        mPlunger.SetPosition(plungerPos);
        mCharge = 0.0;
    }

    // Update physics
    for (mAccumulatedTime += deltaTime; mStepTime <= mAccumulatedTime; mAccumulatedTime -= mStepTime)
    {
        mLeftFlipper.AddTorque(mKeyFIsPressed ? -80000 : 40000);
        mRightFlipper.AddTorque(mKeyJIsPressed ? 80000 : -40000);

        mWorld.update(mStepTime);
    }

    mScore += mStage.CheckItemCollisions(mBall.GetPosition(), 12.0);

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

    mLeftFlipper.Draw();
    mRightFlipper.Draw();

    mStage.Draw();

    mPlunger.Draw();

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