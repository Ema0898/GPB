#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <cstring>
#include "../tools/MathHelper.h"

class InputManager
{
public:

    enum MOUSE_BUTTON { left = 0, right, middle, back, forward };

private:

    static InputManager* sInstance;

    Uint8* mPrevKeyBoardState;
    const Uint8* mKeyBoardStates;

    int mKeyLength;

    Uint32 mPrevMouseState;
    Uint32 mMouseState;

    int mMouseXPos;
    int mMouseYPos;

public:

    static InputManager* instance();
    static void release();

    bool key_down(SDL_Scancode scancode);
    bool key_pressed(SDL_Scancode scancode);
    bool key_released(SDL_Scancode scancode);

    bool mouse_button_down(MOUSE_BUTTON button);
    bool mouse_button_pressed(MOUSE_BUTTON button);
    bool mouse_button_released(MOUSE_BUTTON button);

    Vector2 get_mouse_pos();

    void update();
    void update_previous_input();

private:

    InputManager();
    ~InputManager();

};


#endif //_INPUTMANAGER_H