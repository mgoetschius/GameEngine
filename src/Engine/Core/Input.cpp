#include "Input.h"

bool Input::keys[122];
bool Input::downkeys[122];

Input::Input()
{

}

void Input::setKeyTrue(int key)
{
    keys[key] = true;
}

void Input::setKeyFalse(int key)
{
    keys[key] = false;
    downkeys[key] = false;
}

bool Input::IsDown(int key)
{
    return keys[key];
}

bool Input::IsPressed(int key)
{
    if(IsDown(key) && !downkeys[key])
    {
        downkeys[key] = true;
        return true;
    }
    else
        return false;
}

Input::~Input()
{
    //dtor
}
