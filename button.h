#ifndef BUTTON_H
#define BUTTON_H
#include "particle.h"

class Button: public Particle
{
private:
    bool isActive;
public:
    Button();
    void setState(bool on_off);
    bool getState()const;
};

#endif // BUTTON_H
