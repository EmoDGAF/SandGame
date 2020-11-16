#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "particle.h"
#include "button.h"
#define frate 30
#define pWIDTH 20.f
float parWeight = pWIDTH;
int matrixSize = 30;
int particle_button;

void drawMatrix(std::vector<Particle*>& v, sf::RenderWindow& window)
{
    for (int i = 0; i < v.size(); ++i) {
        window.draw(*(v[i]));
        v[i]->setState(false);
    }
}

void drawOptionButtons(sf::RenderWindow& window, std::vector<Button>& buttons_v)
{
    for (auto i : buttons_v) {
        window.draw(i);
    }
}

void makeMatrix(std::vector<Particle*>& v)
{
    Particle* p = nullptr;

    v.reserve(140000); //200 x 200 = 40 000
    int moveX;
    int moveY = 140;

    for (int i = 0; i < matrixSize; ++i) {
        moveX  = 0;
        moveY += pWIDTH; //cause we dont want each line to add to Y so it must be beyond the inner loop
        for (int j = 0; j < matrixSize; ++j) {

            if(i != matrixSize-1)
            {
                p = new Particle();
                p->setPosition(moveX+=pWIDTH, moveY);

                //if(j==0 || j == matrixSize-1)  //mark as wall:
                //  a->markWall();
                v.push_back(p);

            }   //add bottom line (made of sand):
            else if(i == matrixSize-1)  //add after the matrix is created, thats why i cannot be smaller than current y
            {
                p = new Particle();
                p->setPosition(moveX+=pWIDTH, moveY);
                p->setType('r');
                v.push_back(p);
            }
        }
    }
}

void makeOptionButtons(sf::RenderWindow& window, std::vector<Button>& buttons_v)
{
    Button sandButton;
    sandButton.setPosition(0,0);
    sandButton.setType('s');

    Button rockButton;
    rockButton.setPosition(20,0);
    rockButton.setType('r');

    Button waterButton;
    waterButton.setPosition(40,0);
    waterButton.setType('w');

    buttons_v.push_back(sandButton);
    buttons_v.push_back(rockButton);
    buttons_v.push_back(waterButton);
}

void checkButtonsState(std::vector<Button>& buttons_v, sf::RenderWindow& window)
{
    sf::Vector2i clickPos = sf::Mouse::getPosition(window);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ //without it buttons functions would ba activated without clicking
        for (int i = 0; i < buttons_v.size(); ++i) {

            if(buttons_v[i].checkIfContains(clickPos, window)){
                buttons_v[i].setState(true);
                std::cout << "booom: " << i << std::endl;
                particle_button = i;

            }
        }
    }
}

void checkLeftClicks(std::vector<Particle*>& v, sf::RenderWindow& window)
{
    sf::Vector2i clickPos;
    enum particles_enum {SAND, ROCK, WATER};

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        clickPos = sf::Mouse::getPosition(window);
        std::cout << "particle_button: " << particle_button << std::endl;
        switch (particle_button) {
        case SAND:
        {
            std::cout << "SAND" << std::endl;
            for (int i = 0; i < v.size() ; ++i){
                if(v[i]->checkIfContains(clickPos, window)){
                    v[i]->setType('s');
                }
            }

        }
        break;
        case ROCK:
        {
            std::cout << "ROCK" << std::endl;
            for (int i = 0; i < v.size() ; ++i){
                if(v[i]->checkIfContains(clickPos, window)){
                    v[i]->setType('r');
                }
            }
        }
        break;
        case WATER:
        {
            std::cout << "WATER" << std::endl;
            for (int i = 0; i < v.size() ; ++i){
                if(v[i]->checkIfContains(clickPos, window)){
                    v[i]->setType('w');
                }
            }
        }
        break;
        default:
            break;
        }
    }
}

void airToWater(std::vector<Particle*>& v, int& i, int& pos)
{
    auto currentPos = v[i]->getPosition();
    auto NextPos = v[pos]->getPosition();
    v[i]->setState(true);
    v[pos]->setState(true);
    v[i]->setType('a');
    v[pos]->setType('w');
}

void updateWater(std::vector<Particle*>& v, int& i, int& down, int& downleft, int& downright, int& left, int& right)
{
    if(v[i]->getType() == 'w' && v[i]->getState() == false)//so changes (falls) arent instant
    {
        if(v[down]->getType() == 'a')
            airToWater(v, i, down);
        else if(v[downleft]->getType() == 'a' && v[i]->getPosition().x - v[downleft]->getPosition().x == pWIDTH) //v[i]->getPosition().x - v[downleft]->getPosition().x == 20 cause i dont want rec to land on the opposite side (right) of the matrix - THE position difference between the rec down below -1 one to left should be exact the width of rec
            airToWater(v, i, downleft);
        else if(v[downright]->getType() == 'a' && v[downright]->getPosition().x - v[i]->getPosition().x == pWIDTH )
            airToWater(v, i, downright);
        else if(v[left]->getType() == 'a' && v[i]->getPosition().x - v[left]->getPosition().x == pWIDTH )
            airToWater(v, i, left);
        else if(v[right]->getType() == 'a' && v[right]->getPosition().x - v[i]->getPosition().x == pWIDTH)
            airToWater(v, i, right);
    }
}

void airToSand(std::vector<Particle*>& v, int& i, int& pos)
{
    auto currentPos = v[i]->getPosition();
    auto NextPos = v[pos]->getPosition();
    v[i]->setState(true);
    v[pos]->setState(true);

    v[i]->setType('a');
    v[pos]->setType('s');
}

void waterToSand(std::vector<Particle*>& v, int& i, int& pos)
{
    auto currentPos = v[i]->getPosition();
    auto NextPos = v[pos]->getPosition();
    v[i]->setState(true);
    v[pos]->setState(true);
    v[i]->setType('w');
    v[pos]->setType('s');
}

void updateSand(std::vector<Particle*>& v, int& i, int& down, int& downleft, int& downright)
{
    if(v[i]->getType() == 's' && v[i]->getState() == false) //so changes (falls) arent instant
    {
        if(v[down]->getType() == 'a')
            airToSand(v, i, down);
        else if(v[down]->getType() == 'w' )
            waterToSand(v, i, down);

        //sand falls through air to the left:
        else if(v[downleft]->getType() == 'a' && v[i]->getPosition().x - v[downleft]->getPosition().x == pWIDTH  ) //v[downleft]->getPosition().x - v[i]->getPosition().x-20 <= 20 - cause we dont want sand to appear on the other side of matrix BUT the difference cannot be more than the size of particle (20)
            airToSand(v, i, downleft);
        //sand falls through water to the left:
        else if(v[downleft]->getType() == 'w' && v[i]->getPosition().x - v[downleft]->getPosition().x == pWIDTH)  //v[downleft]->getPosition().x - v[i]->getPosition().x-20 <= 20 - cause we dont want sand to appear on the other side of matrix BUT the difference cannot be more than the size of particle (20)
            waterToSand(v, i, downleft);

        //sand falls through air to the right:
        else if(v[downright]->getType() == 'a' && v[downright]->getPosition().x - v[i]->getPosition().x == pWIDTH  )  //v[right]->getPosition().x < matrixSize*20 cause i dont want rec to land on the opposite side (left) of the matrix
            airToSand(v, i, downright);
        //sand falls through water to the right:
        else if(v[downright]->getType() == 'w' && v[downright]->getPosition().x - v[i]->getPosition().x == pWIDTH )  //v[right]->getPosition().x < matrixSize*20 cause i dont want rec to land on the opposite side (left) of the matrix
            waterToSand(v, i, downright);
    }
}

void update(std::vector<Particle*>& v)
{
    for (int i = 0; i < v.size()- matrixSize; ++i) {  //- matrixSize to save the bottom belt
        int down;
        int downleft;
        int downright;
        int left;
        int right;
        if(i + matrixSize < v.size()) down  = i + matrixSize;
        if(i + matrixSize-1 < v.size()) downleft  = i + matrixSize-1;
        if(i + matrixSize+1 < v.size()) downright = i + matrixSize+1;
        if(i + 1 < v.size()) right = i + 1;
        if(i - 1 >= 0) left = i - 1;
        updateWater(v, i, down, downleft, downright, left, right);
        updateSand(v, i, down, downleft, downright);

    }
}

void checkEvents(sf::RenderWindow& window); //declaration of events
int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 800), "SFML");
    window.setFramerateLimit(frate);
    std::vector<Particle*> v;
    std::vector<Button> buttons_v;
    makeOptionButtons(window, buttons_v);
    makeMatrix(v);

    std::cout << sizeof(Button) << std::endl;
    while(window.isOpen())
    {
        checkEvents(window);
        window.clear();
        checkLeftClicks(v, window);
        update(v);
        checkButtonsState(buttons_v, window);
        drawOptionButtons(window, buttons_v);
        drawMatrix(v, window);
        window.display();
    }
}

void checkEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        }
    }
}
