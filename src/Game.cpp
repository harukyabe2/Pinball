#include "Game.hpp"

// Constants
constexpr double DEADZONE_Y = 400.0;
constexpr double BALL_RADIUS = 12.0;

// Constructor
Game::Game()
: mState(GameState::isPlaying)
, mCamera{Vec2{0, 0}, 1.0, CameraControl::None_}
, mStepTime(1.0 / 200.0)
, mAccumulatedTime(0.0)
, mBall(mWorld, Vec2{55.5, 0}, BALL_RADIUS)
, mStage(mWorld)
, mKeyFIsPressed(false)
, mKeyJIsPressed(false)
, mKeySpaceIsPressed(false)
, mKeyCIsPressed(false)
, mKeyEIsPressed(false)
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
    if (mState == GameState::isPlaying)
    {
        // Flipper controls
        mKeyFIsPressed = KeyF.pressed();
        if (KeyF.down())
        {
            mStage.PlayFlipperSound();
        }
        mKeyJIsPressed = KeyJ.pressed();
        if (KeyJ.down())
        {
            mStage.PlayFlipperSound();
        }

        // Plunger control
        mKeySpaceIsPressed = KeySpace.pressed();
        if (KeySpace.up())
        {
            mStage.PlayPlungerSound();
        }
    }
    // Game over controls
    else if (mState == GameState::isGameOver)
    {
        mKeyCIsPressed = KeyC.down();
        mKeyEIsPressed = KeyE.down();
    }
}

// Update game state
void Game::UpdateGame()
{
    if (mState == GameState::isPlaying)
    {
        double deltaTime = Scene::DeltaTime();

        // Update stage elements
        mBall.SetState(true);
        mStage.Update(deltaTime, mBall, mKeySpaceIsPressed);

        // Update physics
        for (mAccumulatedTime += deltaTime; mStepTime <= mAccumulatedTime; mAccumulatedTime -= mStepTime)
        {
            // Update Flippers
            mStage.UpdateFlippers(mKeyFIsPressed, mKeyJIsPressed);

            // Update physics world
            mWorld.update(mStepTime);

            // Update bumpers
            mStage.UpdateBumpers(mWorld.getCollisions());
        }

        // Check collisions and update score
        mScore += mStage.CheckItemCollisions(mBall.GetPos(), BALL_RADIUS);

        // Check slot jackpot and update score
        mScore += mStage.CheckSlotJackpot();

        // Update items
        mStage.UpdateItems();

        // Check if the ball is out of bounds
        if (mBallCount > 0 && mBall.GetPos().y > DEADZONE_Y)
        {
            mBall.Delete();
            --mBallCount;
            if (mBallCount > 0)
            {
                mBall = Ball(mWorld, Vec2{55.5, 0}, BALL_RADIUS);
            }
            else
            {
                mState = GameState::isGameOver;
            }
        }
    }
    else if (mState == GameState::isGameOver)
    {
        // Continue
        if (mKeyCIsPressed)
        {
            mScore = 0;
            mBallCount = 3;
            mStage.Reset();
            mBall = Ball(mWorld, Vec2{55.5, 0}, BALL_RADIUS);
            mState = GameState::isPlaying;
        }
        // End
        else if (mKeyEIsPressed)
        {
            System::Exit();
        }
    }
}

// Render the game
void Game::GenerateOutput() const
{
    // Set background color
    Scene::SetBackground(Palette::Black);

    // Set camera
    const auto t = mCamera.createTransformer();

    // Draw stage and ball
    mStage.Draw();
    mGameFrame.drawClosed(5, Palette::White);
    mBall.Draw();

    // Draw game UI
    FontAsset(U"UI")(U"SCORE\n{:0>5}"_fmt(mScore)).drawAt(300, -300);
    FontAsset(U"UI")(U"BALL\n  {:0>2}"_fmt(mBallCount)).drawAt(300, -100);

    if (mState == GameState::isGameOver)
    {
        RectF(Vec2{-800, -600}, SizeF{1600, 1200}).draw(ColorF{ 0.0, 0.7 });

        FontAsset(U"UI")(U"GAME OVER").drawAt(100, Vec2{0, -150}, Palette::Red);
        
        FontAsset(U"UI")(U"SCORE\n{:0>5}"_fmt(mScore)).drawAt(Vec2{0, 0});
        
        double alpha = Periodic::Sine0_1(2.0s);
        FontAsset(U"UI")(U"Press [C] to Continue").drawAt(40, Vec2{0, 120}, ColorF{1.0, alpha});
        FontAsset(U"UI")(U"Press [E] or [Esc] to End").drawAt(40, Vec2{0, 190}, ColorF{1.0, alpha});
    }
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
    AudioAsset::Register(U"Slot", U"sound/Slot.wav");
    
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