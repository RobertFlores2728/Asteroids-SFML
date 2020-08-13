#include "GameManager.h"

GameManager::GameManager() {
    SetupGame();
}


void GameManager::SetupGame() {
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Asteroids!");
	window->setFramerateLimit(FPS);

    clock = new sf::Clock();

	ship = new Ship(*window);
	ships.push_back(ship);

    SpawnAsteroids(1);
}

void GameManager::RunGame() {
    while (window->isOpen())
    {
        deltaTime = clock->getElapsedTime();
        clock->restart();


        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();

        UpdateShips();
        UpdateAsteroids();

        window->display();

    }
}

void GameManager::UpdateShips() {
    for (Ship* ship : ships) {
        ship->Update(deltaTime);
        ship->Draw();
    }
}

void GameManager::UpdateAsteroids() {
    for (Asteroid* asteroid : asteroids) {
        asteroid->Update(deltaTime);
        asteroid->Draw();
    }
}

void GameManager::SpawnAsteroids(int n) {
    for (int i = 0; i < n; i++) {
        Asteroid* a = new Asteroid(*window, *ship);
        asteroids.push_back(a);
    }
}
