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

private:
	//sfml game settings
	sf::RenderWindow* window;
	int FPS = 120;
	sf::Clock* clock;
	sf::Time deltaTime;

	//game object vectors
	std::vector<Ship*> ships;
	std::vector<Asteroid*> asteroids;

	
};

