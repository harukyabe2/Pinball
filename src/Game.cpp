#include "Game.hpp"

Game::Game()
{

}

bool Game::Initialize()
{
    return true;
}

void Game::RunLoop()
{
    while (System::Update())
    {
    }
}

void Game::ProcessInput()
{

}

void Game::UpdateGame()
{

}

void Game::GenerateOutput()
{
    Scene::SetBackground(ColorF(0.1, 0.2, 0.2));
}

void Game::LoadData()
{

}

void Game::Shutdown()
{

}