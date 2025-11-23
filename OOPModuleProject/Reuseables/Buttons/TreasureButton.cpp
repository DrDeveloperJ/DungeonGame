#include "TreasureButton.h"
#include "../../GameMediator.h"


TreasureButton::TreasureButton(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY) : Button(newName, buttonAssetDirectory, hoverAssetDirectory, posX, posY, scaleX, scaleY)
{
	gameMediator = gameMediatorPtr;
}

Response TreasureButton::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void TreasureButton::notify(const std::string& message)
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
		gameMediator->notifyComponent("RoomSelector", "reset");
		gameMediator->notifyComponent("Game", "HomePage");
		gameMediator->notifyComponent("Player", "resetHealth");
		gameMediator->notifyComponent("Player", "resetGameplayAttributes");
		gameMediator->notifyComponent("ExploredDungeonsDisplay", "reset");
		gameMediator->notifyComponent("ExploredDungeonsDisplay", "setInvisible");
	}
}

void TreasureButton::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
	}
}
