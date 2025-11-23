#include "UiElement.h"
#include "../GameMediator.h"

UiElement::UiElement(std::string newName, std::string elementAssetDirectory, float posX, float posY, float scaleX, float scaleY)
{
	name = newName;

	// Load texture for element
	if (elementTexture.loadFromFile(elementAssetDirectory))
	{
		std::cout << "Loaded Button Texture" << std::endl;
		Sprite = std::make_unique<sf::Sprite>(elementTexture);
	}
	else
	{
		throw std::runtime_error("Failed to load Element texture!");
	}

	Sprite->setPosition({ posX, posY });
	Sprite->setScale({ scaleX, scaleY });
}

void UiElement::Draw(sf::RenderWindow& window)
{
	// Draws the element if visible
	if (visible)
	{
		window.draw(*Sprite);
	}
}

Response UiElement::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void UiElement::notify(const std::string& message)
{
}

std::string UiElement::getName()
{
	return name;
}