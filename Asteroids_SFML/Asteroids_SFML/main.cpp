#include "main.h"
//#include <SFML/Graphics.hpp>
//#include "Ship.h"
//#include "Asteroid.h"




int main()
{
    /*sf::RenderWindow window(sf::VideoMode(1000, 1000), "Asteroids!");
    window.setFramerateLimit(120);

    std::vector<Ship*> ships;
    std::vector<Asteroid*> asteroids;


    sf::Clock clock;*/

    //Ship ship(window);
    //ships.push_back(&ship);
    
    //Asteroid asteroid1(window, ship);
    //asteroids.push_back(&asteroid1);

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