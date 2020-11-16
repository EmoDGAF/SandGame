#include "button.h"

Button::Button()
{
    isActive = false;
}

void Button::setState(bool on_off)
{
    isActive = on_off;
}

bool Button::getState() const
{
    return isActive;
}
