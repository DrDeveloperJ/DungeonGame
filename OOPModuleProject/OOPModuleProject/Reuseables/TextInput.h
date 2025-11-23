#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Component.h"

class TextInput :
    public Component
{
protected:
    sf::Font font;
    sf::RectangleShape rect;
    sf::Text text;
    std::string inputString;
    int characterLimit;
    bool active = true;

    void updateText() {
        text.setString(inputString);
    }

    void backspaceText() {
        inputString.pop_back();
        if (!inputString.empty())
        {
            inputString.pop_back();
        }
    }

public:
    TextInput(std::shared_ptr<GameMediator> gameMediatorPtr, float posX, float posY, unsigned int characterSize, sf::Vector2f size, int charLimit);
    std::string getText();
    void handleTextEntered(const char32_t unicode);
    void handleKeyPress(const sf::Keyboard::Key key);

    virtual void Draw(sf::RenderWindow& window)override;
    virtual Response requestData(const std::string& request) override;
    virtual void notify(const std::string& message) override;
};

