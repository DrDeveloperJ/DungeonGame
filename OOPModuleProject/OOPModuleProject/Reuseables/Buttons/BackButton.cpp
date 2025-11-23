#include "BackButton.h"
#include "../../GameMediator.h"


BackButton::BackButton(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY) : Button(newName, buttonAssetDirectory, hoverAssetDirectory, posX, posY, scaleX, scaleY)
{
	gameMediator = gameMediatorPtr;
}

Response BackButton::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void BackButton::notify(const std::string& message)
{
	ButtonState = 0;
	if (message == "setVisible")
	{
		this->setVisible(true);
	}
	else if (message == "setInvisible")
	{
		this->setVisible(false);
	}
	else if (message == "Clicked")
	{
		gameMediator->notifyComponent("Game", "MoveBackward");
	}
}

void BackButton::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
	}
}
