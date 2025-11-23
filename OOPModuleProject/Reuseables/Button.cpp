#include "Button.h"
#include "../GameMediator.h"

Button::Button(std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY)
{
	name = newName;

	// Load texture for element
	if (ButtonTexture.loadFromFile(buttonAssetDirectory))
	{
		std::cout << "Loaded Button Texture" << std::endl;
		Sprite = std::make_unique<sf::Sprite>(ButtonTexture);
	}
	else
	{
		throw std::runtime_error("Failed to load Button texture!");
	}

	Sprite->setPosition({ posX, posY });
	Sprite->setScale({ scaleX, scaleY });

	name = newName;

	// Loads Hover texture for button
	if (OnButtonTexture.loadFromFile(hoverAssetDirectory))
	{
		std::cout << "Loaded Button Hover Texture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load Button Hover texture!");
	}
}

Button::~Button()
{

}

void Button::disableButton()
{
	Sprite->setTexture(ButtonTexture);
	ButtonState = 0;
	visible = false;
}

void Button::enableButton()
{
	visible = true;
}

std::string Button::getName()
{
	return name;
}

void Button::switchState(int state)
{
	if (visible)
	{
		// Switches button state
		switch (state)
		{
		case 0:
			Sprite->setTexture(ButtonTexture);
			ButtonState = 0;
			break;
		case 1:
			Sprite->setTexture(OnButtonTexture);
			ButtonState = 1;
			break;
		}
	}
}

int Button::getState()
{
	return ButtonState;
}

void Button::checkMouseIsOver(sf::RenderWindow& window)
{
	// Checks if mouse is over the button area, setting its state based on this
	if (visible)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		bool overButton = Sprite->getGlobalBounds().contains({ mouseX, mouseY });

		if (overButton)
		{
			switchState(1);
		}
		else
		{
			switchState(0);
		}
	}
}