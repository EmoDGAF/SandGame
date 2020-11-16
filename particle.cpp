#include "particle.h"

Particle::Particle()
{
    extern float parWeight;
    this->setSize(sf::Vector2f(parWeight,parWeight));
    this->setOutlineColor(sf::Color::Green);
    this->setOutlineThickness(1.f);
    this->setType('a');
}

void Particle::setType(char type_)
{
    type = type_;
    if(type == 'a')
        this->setFillColor(sf::Color::Cyan);
    if(type == 's')
        this->setFillColor(sf::Color::Yellow);
    if(type == 'r')
        this->setFillColor(sf::Color::Magenta);
    if(type == 'w')
        this->setFillColor(sf::Color::Blue);
}

char Particle::getType() const
{
    return type;
}

bool Particle::checkIfContains(sf::Vector2i& posOfMouse, sf::RenderWindow& window)
{
    ///here we want to check the exact rectangle
    //std::cout << "this: " << this << std::endl;
    return this->getGlobalBounds().contains(window.mapPixelToCoords(posOfMouse));
}



void Particle::setState(bool setter)
{
    isChanged = setter;
}

bool Particle::getState()
{
    return isChanged;
}
