#include "main.h"
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Asteroid.h"
#include <iostream>



int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setFramerateLimit(120);


    sf::Clock clock;

    Ship ship(window);
    Asteroid asteroid1(window, ship);

    while (window.isOpen())
    {
        sf::Time deltaTime = clock.getElapsedTime();
        clock.restart();


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        ship.Draw();
        asteroid1.Draw();
        asteroid1.Update(deltaTime);
        ship.Update(deltaTime);
        window.display();

    }

    return 0;
}