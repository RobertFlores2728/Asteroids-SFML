#pragma once

#include "main.h"

class GameManager;



class Button
{
private:
	GameManager* gm;


public:
	sf::Sprite buttonSprite;

	Button() = delete;

	Button(std::string text, sf::Vector2f position);

	void SetupSprite();


	void Draw();
	void Update();


};
