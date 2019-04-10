#include "input.h"
#include "QKeyEvent"

Input::Input()
{

}
void Input::KeyPressedEvent(QKeyEvent *event)
{
 if(event->key()<0 || event->key() > MAX_KEYS)
     return;
    keys[event->key()] = InputState::PRESSED;
}
void Input::KeyUpEvent(QKeyEvent *event)
{
    if(event->key()<0 || event->key() > MAX_KEYS)
        return;
    keys[event->key()] = InputState::UP;

}
void Input::KeyDownEvent(QKeyEvent *event)
{

    if(event->key()<0 || event->key() > MAX_KEYS)
        return;
    keys[event->key()] = InputState::DOWN;

}

void Input::MouseButtonPressedEvent(QKeyEvent *event)
{
    if(event->key()<0 || event->key() > MAX_BUTTON)
        return;
    mouseButtons[event->key()] = InputState::PRESSED;

}
void Input::MouseButtonUpEvent(QKeyEvent *event)
{
    if(event->key()<0 || event->key() > MAX_BUTTON)
        return;
    mouseButtons[event->key()] = InputState::UP;

}
void Input::MouseButtonDownEvent(QKeyEvent *event)
{
    if(event->key()<0 || event->key() > MAX_BUTTON)
        return;
    mouseButtons[event->key()] = InputState::DOWN;

}


bool Input::GetKeyPressed(int key)
{
    if(key<0 || key > MAX_KEYS)
        return false;
    return keys[key] == InputState::PRESSED;
}
bool Input::GetKeyUp(int key)
{
    if(key<0 || key > MAX_KEYS)
        return false;
    return keys[key] == InputState::UP;

}
bool Input::GetKeyDown(int key)
{
    if(key<0 || key > MAX_KEYS)
        return false;
    return keys[key] == InputState::DOWN;
}

bool Input::GetMouseButtonPressed(int key)
{
    if(key<0 || key > MAX_BUTTON)
        return false;
    return mouseButtons[key] == InputState::PRESSED;

}
bool Input::GetMouseButtonUp(int key)
{
    if(key<0 || key > MAX_BUTTON)
        return false;
    return mouseButtons[key] == InputState::UP;

}
bool Input::GetMouseButtonDown(int key)
{
    if(key<0 || key > MAX_BUTTON)
        return false;
    return mouseButtons[key] == InputState::DOWN;
}

void Input::PostUpdate()
{

}

/*
 for (int i = 0; i < MAX_KEYS; ++i)
    {
        if (keys[i] == 1)
        {
            if (keyboard[i] == KEY_IDLE)
                keyboard[i] = KEY_DOWN;
            else
                keyboard[i] = KEY_REPEAT;
        }
        else
        {
            if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
                keyboard[i] = KEY_UP;
            else
                keyboard[i] = KEY_IDLE;
        }
    }

 */
