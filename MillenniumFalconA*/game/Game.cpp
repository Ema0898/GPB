#include "Game.h"

Game* Game::sInstance = nullptr;

Game* Game::instance()
{
    if (sInstance == nullptr)
        sInstance = new Game();

    return sInstance;
}

void Game::release()
{
    delete sInstance;
    sInstance = nullptr;
}

Game::Game()
{
    srand(time(0));

    mQuit = false;
    mGraphics = Graphics::instance();

    if (!Graphics::initialized())
        mQuit = true;

    assetManager = AssetManager::instance();
    inputManager = InputManager::instance();
    audioManager = AudioManager::instance();
    mTimer = Timer::instance();
    screenManager = ScreenManager::instance();
    grid = Grid::instance();
}

Game::~Game()
{
    ScreenManager::release();
    screenManager = nullptr;

    Grid::release();
    grid = nullptr;

    AudioManager::release();
    audioManager = nullptr;

    AssetManager::release();
    assetManager = nullptr;

    Graphics::release();
    mGraphics = nullptr;

    InputManager::release();
    inputManager = nullptr;

    Timer::release();
    mTimer = nullptr;


    std::cout << "Liberado" << std::endl;
}

void Game::early_update()
{
    inputManager->update();
}

void Game::update()
{
    screenManager->update();
}

void Game::late_update()
{
    inputManager->update_previous_input();
    mTimer->reset();
}

void Game::render()
{
    mGraphics->clear_back_buffer();

    // All the Draw Calls
    screenManager->render();

    mGraphics->render();
}

void Game::run()
{
    while (!mQuit)
    {
        mTimer->update();

        while (SDL_PollEvent(&mEvents) != 0)
        {
            if (mEvents.type == SDL_QUIT)
            {
                mQuit = true;
            }
        }

        if (mTimer->delta_time() >= (1.0f / FRAME_RATE))
        {
            early_update();
            update();
            late_update();
            render();
        }
    }
}

