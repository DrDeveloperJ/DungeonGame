#include "Text.h"

// Constructor implementation
Text::Text(const sf::Font& font, const std::string& text)
    : sf::Text(font, text) // Explicitly call the sf::Text constructor
{
    setCharacterSize(30); // Default character size
}

void Text::Draw(sf::RenderWindow& window)
{
    if (visible)
    {
        window.draw(*this);
    }
}

Response Text::requestData(const std::string& request)
{
    Response hi = "hello";
    return hi;
}

void Text::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else
	{
		this->setString(message);
	}
}