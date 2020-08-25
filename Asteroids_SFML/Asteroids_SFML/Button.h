#pragma once

#include "main.h"

class GameManager;



class Button
{
private:
	GameManager* gm;


public:
	sf::RectangleShape rectangleShape;
	sf::Sprite buttonSprite;
	sf::RenderTexture buttonTexture;

	sf::Vector2<float> position;
	sf::Vector2<float> size;

	float outlineThickness = 5.0f;

	sf::Text buttonText;
	sf::Font font;


	Button() = delete;

	Button(GameManager& gameManager, std::string text, sf::Vector2f position);

	void SetupRectangleShape();
	void SetupSprite(std::string text, sf::Vector2f position);
	void SetupText();


	void Draw();
	void Update();


};

