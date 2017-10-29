#include "InputManager.h"

InputManager* InputManager::sInstance = nullptr;

InputManager* InputManager::instance()
{
    if (sInstance == nullptr)
        sInstance = new InputManager();

    return sInstance;
}

void InputManager::release()
{
    delete sInstance;
    sInstance = nullptr;
}

InputManager::InputManager()
{
    mKeyBoardStates = SDL_GetKeyboardState(&mKeyLength);
    mPrevKeyBoardState = new Uint8(mKeyLength);
    memcpy(mPrevKeyBoardState, mKeyBoardStates, mKeyLength);
}

InputManager::~InputManager()
{
    delete[] mPrevKeyBoardState;
    mPrevKeyBoardState = nullptr;
}

bool InputManager::key_down(SDL_Scancode scancode)
{
    return mKeyBoardStates[scancode];
}

bool InputManager::key_pressed(SDL_Scancode scancode)
{
    return !mPrevKeyBoardState[scancode] && mKeyBoardStates[scancode];
}

bool InputManager::key_released(SDL_Scancode scancode)
{
    return mPrevKeyBoardState[scancode] && !mKeyBoardStates[scancode];
}

Vector2 InputManager::get_mouse_pos()
{
    return Vector2((float) mMouseXPos, (float) mMouseYPos);
}

bool InputManager::mouse_button_down(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
        case left:
            mask = SDL_BUTTON_LMASK;
            break;

        case right:
            mask = SDL_BUTTON_RMASK;
            break;

        case middle:
            mask = SDL_BUTTON_MMASK;
            break;

        case back:
            mask = SDL_BUTTON_X1MASK;
            break;

        case forward:
            mask = SDL_BUTTON_X2MASK;
            break;
    }

    return (mMouseState & mask);

}

bool InputManager::mouse_button_pressed(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
        case left:
            mask = SDL_BUTTON_LMASK;
            break;

        case right:
            mask = SDL_BUTTON_RMASK;
            break;

        case middle:
            mask = SDL_BUTTON_MMASK;
            break;

        case back:
            mask = SDL_BUTTON_X1MASK;
            break;

        case forward:
            mask = SDL_BUTTON_X2MASK;
            break;
    }

    return !(mPrevMouseState & mask) && (mMouseState & mask);

}

bool InputManager::mouse_button_released(MOUSE_BUTTON button)
{
    Uint32 mask = 0;

    switch (button)
    {
        case left:
            mask = SDL_BUTTON_LMASK;
            break;

        case right:
            mask = SDL_BUTTON_RMASK;
            break;

        case middle:
            mask = SDL_BUTTON_MMASK;
            break;

        case back:
            mask = SDL_BUTTON_X1MASK;
            break;

        case forward:
            mask = SDL_BUTTON_X2MASK;
            break;
    }

    return (mPrevMouseState & mask) && !(mMouseState & mask);

}

void InputManager::update()
{
    mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void InputManager::update_previous_input()
{
    memcpy(mPrevKeyBoardState, mKeyBoardStates, mKeyLength);
    mPrevMouseState = mMouseState;
}
