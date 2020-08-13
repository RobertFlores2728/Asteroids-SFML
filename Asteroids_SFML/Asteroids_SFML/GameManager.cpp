#include "GameManager.h"

void GameManager::SetupGame() {
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Asteroids!");
	window->setFramerateLimit(FPS);

	Ship* ship = new Ship(*window);
	ships.push_back(ship);
}

void GameManager::RunGame() {
    while (window->isOpen())
    {
        sf::Time deltaTime = clock->getElapsedTime();
        clock->restart();


        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        ship.Draw();
        asteroid1.Draw();
        asteroid1.Update(deltaTime);
        ship.Update(deltaTime);
        window.display();

    }
}

void GameManager::UpdateShips() {
    for (Bullet* bullet : bullets) {
        bullet->Update(deltaTime);
        bullet->Draw();
    }
}
