#pragma once

#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Asteroid.h"

//forward decleration
class Ship;
class Asteroid;

class GameManager
{
public:


private:
	sf::RenderWindow* window;
	int FPS = 120;
	sf::Clock* clock;

	std::vector<Ship*> ships;
	std::vector<Asteroid*> asteroids;



	void SetupGame();
	void RunGame();

	void UpdateShips();
	void UpdateAsteroids();
};

