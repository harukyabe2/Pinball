#include "Stage.hpp"

// Constructor
Stage::Stage(P2World& world)
: mCharge(0.0)
{
    LoadFirstStage(world);
}

// Update stage
void Stage::Update(double deltaTime, Ball& ball, bool keySpace, bool keyF, bool keyJ)
{
    // Update plunger and ball
    Vec2 plungerPos = Vec2{60, 200};
    if (keySpace)
    {
        mCharge += 180.0 * deltaTime;
        if (mCharge > 180.0)
        {
            mCharge = 180.0;
        }
        mPlunger.SetPosition(plungerPos + Vec2{0, mCharge});
    }
    else if (mCharge > 0.0)
    {
        Vec2 ballPos = ball.GetPosition();
        if (ballPos.x > 50 && ballPos.y > 0)
        {
            ball.SetPosition(plungerPos);
            double impulse = -1 * mCharge;
            ball.AddImpulse(Vec2{0, impulse});
        }
        mPlunger.SetPosition(plungerPos);
        mCharge = 0.0;
    }

    // Update flippers
    mLeftFlipper.AddTorque(keyF ? -80000 : 40000);
    mRightFlipper.AddTorque(keyJ ? 80000 : -40000);
}

// Draw
void Stage::Draw() const
{
    // Draw flippers
    mLeftFlipper.Draw();
    mRightFlipper.Draw();

    // Draw walls
    for (const auto& wall : mWalls)
    {
        wall.draw(Palette::Midnightblue);
    }

    // Draw plunger
    mPlunger.Draw();

    // Draw bumpers
    for (const auto& bumper : mBumpers)
    {
        bumper.Draw();
    }

    // Draw items
    for (const auto& item : mItems)
    {
        item.Draw();
    }
}

// Update items
void Stage::UpdateItems()
{
    for (auto& item : mItems)
    {
        item.Update();
    }
}

// Check item collisions and return the score
int32 Stage::CheckItemCollisions(const Vec2& ballPos, double ballRadius)
{
    int32 score = 0;

    for (auto& item : mItems)
    {
        if (item.CheckHit(ballPos, ballRadius))
        {
            score = 100;
        }
    }

    return score;
}

// Create circle wall points
LineString Stage::mCreateCircleWall(const Vec2& center, double radius, double angleOffset, int32 segments)
{
    LineString wall;
    for (int32 i = 0; i < segments; ++i)
    {
        Vec2 point = OffsetCircular(center, radius, angleOffset + (i * 3_deg));
        wall << point;
    }
    return wall;
}

// Load Stage
void Stage::LoadFirstStage(P2World& world)
{
    // Create flippers
    mLeftFlipperAnchor = Vec2{-320, 360};
    mRightFlipperAnchor = Vec2{-180, 360};
    mLeftFlipper = Flipper(world, mLeftFlipperAnchor, Vec2{50, 0}, -20_deg, 20_deg);
    mRightFlipper = Flipper(world, mRightFlipperAnchor, Vec2{-50, 0}, -20_deg, 20_deg);

    // Create plunger
    mPlunger = Plunger(world, Vec2{60, 200}, SizeF{30, 30});

    // Create walls
    LineString outerWall;
    outerWall << Vec2{-320, 390} << Vec2{-320, 360} << Vec2{-485, 290} << Vec2{-490, 15};
    outerWall.append(mCreateCircleWall(Vec2{-250, -185}, 200, 225_deg, 46));
    outerWall << Vec2{-250, -385};
    outerWall.append(mCreateCircleWall(Vec2{-13, -287}, 100, 0_deg, 31));
    outerWall << Vec2{85, 0} << Vec2{85, 390} << Vec2{35, 390};
    Polygon thickOuterWall = outerWall.calculateRoundBuffer(10);
    mWalls << world.createPolygon(P2Static, Vec2{0, 0}, thickOuterWall, P2Material{}, P2Filter{0x0002, 0x0001});

    LineString innerWall;
    LineString tmp;
    tmp << Vec2{-13, -337} << Vec2{-43, -337};
    tmp.append(mCreateCircleWall(Vec2{-250, -185}, 200, 60_deg, 26));
    tmp << Vec2{-15, 15} << Vec2{-15, 290} << Vec2{-180, 360} << Vec2{-180, 390};
    innerWall.append(mCreateCircleWall(Vec2{-13, -287}, 50, 0_deg, 31));
    innerWall  << Vec2{35, 0} << Vec2{35, 390};
    innerWall.reverse();
    innerWall.append(tmp);
    Polygon thickInnerWall = innerWall.calculateRoundBuffer(10);
    mWalls << world.createPolygon(P2Static, Vec2{0, 0}, thickInnerWall, P2Material{}, P2Filter{0x0002, 0x0001});

    LineString centerWall;
    centerWall.append(mCreateCircleWall(Vec2{-250, -185}, 140, 60_deg, 21));
    Polygon thickCenterWall = centerWall.calculateRoundBuffer(10);
    mWalls << world.createPolygon(P2Static, Vec2{0, 0}, thickCenterWall, P2Material{});

    // Create bumpers
    LineString leftTriangleBumper;
    leftTriangleBumper << Vec2{-373, 286} << Vec2{-439, 258} << Vec2{-439, 168} << Vec2{-371, 286};
    Polygon thickleftTriangleBumper = leftTriangleBumper.calculateRoundBuffer(3);
    mBumpers.push_back(Bumper(world, thickleftTriangleBumper));

    LineString rightTriangleBumper;
    rightTriangleBumper << Vec2{-127, 286} << Vec2{-61, 258} << Vec2{-61, 168} << Vec2{-129, 286};
    Polygon thickRightTriangleBumper = rightTriangleBumper.calculateRoundBuffer(3);
    mBumpers.push_back(Bumper(world, thickRightTriangleBumper));

    LineString circleBumper;
    circleBumper.append(mCreateCircleWall(Vec2{-250, -185}, 20, 0_deg, 120));
    Polygon thickCircleBumper = circleBumper.calculateRoundBuffer(3);
    mBumpers.push_back(Bumper(world, thickCircleBumper));

    // Create items
    for (int32 i = 0; i < 46; i += 4)
    {
        Vec2 pos = OffsetCircular(Vec2{-250, -185}, 170, 225_deg + (i * 3_deg));
        mItems << Item(pos, 7);
    }
    for (int32 i = 0; i < 21; i += 4)
    {
        Vec2 pos = OffsetCircular(Vec2{-250, -185}, 170, 60_deg + (i * 3_deg));
        mItems << Item(pos, 7);
    }
}