#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Ship.h"
#include "Asteroid.h"

//forward decleration
class Ship;
class Asteroid;

class GameManager
{
public:
	GameManager();

	void SetupGame();
	void RunGame();

	void UpdateShips();
	void UpdateAsteroids();

	void SpawnAsteroids(int n);

	sf::RenderWindow* window;
	sf::Clock* clock;

private:
	//sfml game settings
	
	int FPS = 120;
	
	sf::Time deltaTime;

	std::shared_ptr<Ship> ship;
	//game object vectors
	std::vector< std::shared_ptr<Ship> > ships;
	
	std::vector< std::shared_ptr<Asteroid> > asteroids;

	
};

