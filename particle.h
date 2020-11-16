#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>

class Particle: public sf::RectangleShape
{
private:
    char type;
    bool isChanged;
public:
    Particle();
    void setType(char type_);
    char getType() const;
    void setState(bool setter);
    bool getState();

    bool checkIfContains(sf::Vector2i& posOfMouse, sf::RenderWindow& window);
};

#endif // PARTICLE_H
