#include "Game.hpp"

// Constructor
Game::Game()
: mGameTimer{StartImmediately::Yes}
, mFont{FontMethod::MSDF, 48, Typeface::Bold}
, mCamera{Vec2{0, 0}, 1.0, CameraControl::None_}
, mStepTime(1.0 / 200.0)
, mAccumulatedTime(0.0)
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
    Vec2{300 - SCENEW, -1 * SCENEH / 2 - 100},
    Vec2{300 - SCENEW, 100 + SCENEH / 2},
    Vec2{SCENEW / 2 - 300, 100 + SCENEH / 2},
    Vec2{SCENEW / 2 - 300, -1 * SCENEH / 2 - 100},
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

    mKeySpaceIsPressed = KeySpace.pressed();
}

// Update game state
void Game::UpdateGame()
{
    double deltaTime = Scene::DeltaTime();

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

    for (mAccumulatedTime += deltaTime; mStepTime <= mAccumulatedTime; mAccumulatedTime -= mStepTime)
    {
        mLeftFlipper.AddTorque(mKeyFIsPressed ? -80000 : 40000);
        mRightFlipper.AddTorque(mKeyJIsPressed ? 80000 : -40000);

        mWorld.update(mStepTime);
    }

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

    mBall.Draw();

    for (const auto& frame : mFrames)
    {
        frame.draw(Palette::Midnightblue);
    }

    mPlunger.Draw();

    mGameFrame.drawClosed(5, Palette::White);

    // Draw game elements
    mFont(U"SCORE\n{:0>5}"_fmt(mScore)).drawAt(SCENEW / 2 - 300, SCENEH / 2 - 600);
    mFont(U"BALL\n  {:0>2}"_fmt(mBallCount)).drawAt(SCENEW / 2 - 300, SCENEH / 2 - 200);
}

// Load game data
void Game::LoadData()
{
    LineString outerWall;
    outerWall << Vec2{-320, 390} << Vec2{-320, 360} << Vec2{-485, 290} << Vec2{-490, 15};
    outerWall.append(mCreateCircleFrame(Vec2{-250, -185}, 200, 225_deg, 46));
    outerWall << Vec2{-250, -385};
    outerWall.append(mCreateCircleFrame(Vec2{-13, -1 * SCENEH / 2 + 13}, 100, 0_deg, 31));
    outerWall << Vec2{85, 0} << Vec2{85, 390} << Vec2{35, 390};
    Polygon thickOuterWall = outerWall.calculateRoundBuffer(10);
    mFrames << mWorld.createPolygon(P2Static, Vec2{0, 0}, thickOuterWall, P2Material{}, P2Filter{0x0002, 0x0001});

    LineString innerWall;
    LineString tmp;
    tmp << Vec2{-13, -337} << Vec2{-43, -337};
    tmp.append(mCreateCircleFrame(Vec2{-250, -185}, 200, 60_deg, 26));
    tmp << Vec2{-15, 15} << Vec2{-15, 290} << Vec2{-180, 360} << Vec2{-180, 390};
    innerWall.append(mCreateCircleFrame(Vec2{-13, -1 * SCENEH / 2 + 13}, 50, 0_deg, 31));
    innerWall  << Vec2{35, 0} << Vec2{35, 390};
    innerWall.reverse();
    innerWall.append(tmp);
    Polygon thickInnerWall = innerWall.calculateRoundBuffer(10);
    mFrames << mWorld.createPolygon(P2Static, Vec2{0, 0}, thickInnerWall, P2Material{}, P2Filter{0x0002, 0x0001});

    LineString centerWall;
    centerWall.append(mCreateCircleFrame(Vec2{-250, -185}, 140, 60_deg, 21));
    Polygon thickCenterWall = centerWall.calculateRoundBuffer(10);
    mFrames << mWorld.createPolygon(P2Static, Vec2{0, 0}, thickCenterWall, P2Material{});
}

LineString Game::mCreateCircleFrame(const Vec2& center, double radius, double angleOffset, int32 segments)
{
    LineString frame;
    for (int32 i = 0; i < segments; ++i)
    {
        Vec2 point = OffsetCircular(center, radius, angleOffset + (i * 3_deg));
        frame << point;
    }
    return frame;
}

// Shutdown the game
void Game::Shutdown()
{

}