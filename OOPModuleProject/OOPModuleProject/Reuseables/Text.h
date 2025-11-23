#pragma once
#include <SFML/Graphics.hpp>
#include "../Component.h"

class Text : public sf::Text, public Component
{
public:
    // Constructor accepting font and string
    Text(const sf::Font& font, const std::string& text);

    // Override Component methods
    void Draw(sf::RenderWindow& window) override;
    Response requestData(const std::string& request) override;
    void notify(const std::string& message) override;
};