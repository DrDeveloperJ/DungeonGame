#include "CustomizeButton.h"
#include "../../GameMediator.h"

CustomizeButton::CustomizeButton(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY) : Button(newName, buttonAssetDirectory, hoverAssetDirectory, posX, posY, scaleX, scaleY)
{
	gameMediator = gameMediatorPtr;
}

Response CustomizeButton::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void CustomizeButton::notify(const std::string& message)
{
	ButtonState = 0;
	if (message == "setVisible")
	{
		setVisible(true);
		std::cout << visible;
	}
	else if (message == "setInvisible")
	{
		setVisible(false);
		std::cout << visible;
	}
	else if (message == "Clicked")
	{
		gameMediator->notifyComponent("Game", "Customize");
	}
}

void CustomizeButton::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
	}

}
