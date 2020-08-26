#include "Button.h"

Button::Button(GameManager& gameManager, std::string text, sf::Vector2f pos, void (*f)()) {
    
    gm = &gameManager;

    func = f;

    this->text = text;
    this->position = pos;
    size = sf::Vector2f(150, 50);

    SetupRectangleShape();
	SetupSprite();

}

void Button::SetupRectangleShape() {
    
    rectangleShape.setSize(size);
    rectangleShape.setPosition(outlineThickness, outlineThickness);
    rectangleShape.setOutlineColor(sf::Color::White);
    rectangleShape.setOutlineThickness(outlineThickness);
    rectangleShape.setFillColor(sf::Color::Black);
}

void Button::SetupSprite() {

    buttonTexture.create(size.x + outlineThickness*2, size.y + outlineThickness*2);
    buttonSprite = sf::Sprite(buttonTexture.getTexture());
    buttonSprite.setOrigin(size.x/2, size.y/2);
    buttonSprite.setPosition(position);
    buttonTexture.clear(sf::Color::Black);
    buttonTexture.draw(rectangleShape);
    SetupText();
    buttonTexture.display();

}

void Button::SetupText() {
    font.loadFromFile("res/Boba Panda Font/Boba Panda Font by 7NTypes.otf");

    buttonText.setFont(font);

    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::White);


    buttonText.setOrigin(buttonText.getCharacterSize()/ text.length(), buttonText.getCharacterSize() / text.length());

    sf::Vector2<float> position;
    position.x = size.x / (text.length()/2);
    position.y = size.y / (text.length()/2);
    buttonText.setPosition(position);

    

    buttonTexture.draw(buttonText);
}

void Button::Draw() {
    //gm->window->draw(rectangleShape);
    gm->window->draw(buttonSprite);
}

void Button::Update() {
    //check for mouse hovering, click, etc.
    CheckMouseHover();
    CheckMouseInput();
}


void Button::CheckMouseHover() {

    if (mouse.getPosition(*gm->window).x > this->position.x - (size.x / 2) && mouse.getPosition(*gm->window).x < this->position.x + (size.x / 2) + outlineThickness) {
        
        if (mouse.getPosition(*gm->window).y > this->position.y - (size.y / 2) && mouse.getPosition(*gm->window).y < this->position.y + (size.y / 2)) {
            //std::cout << "Mouse pos. X: " << mouse.getPosition(*gm->window).x << " Y: " << mouse.getPosition(*gm->window).y << std::endl;
            mouseOver = true;
            return;
        }
    }

    mouseOver = false;
}


void Button::CheckMouseInput() {
    if (!mouseOver)
        return;

    if (mouse.isButtonPressed(sf::Mouse::Button::Left)) {
        std::cout << "Mouse pos. X: " << mouse.getPosition(*gm->window).x << " Y: " << mouse.getPosition(*gm->window).y << std::endl;
        (*func)();
    }

}