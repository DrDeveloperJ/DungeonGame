#include "ExploreButton.h"
#include "../../GameMediator.h"

ExploreButton::ExploreButton(std::shared_ptr<GameMediator> gameMediatorPtr, std::string newName, std::string buttonAssetDirectory, std::string hoverAssetDirectory, float posX, float posY, float scaleX, float scaleY) : Button(newName, buttonAssetDirectory, hoverAssetDirectory, posX, posY, scaleX, scaleY)
{
	gameMediator = gameMediatorPtr;
}

Response ExploreButton::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void ExploreButton::notify(const std::string& message)
{
	ButtonState = 0;
	if (message == "setVisible")
	{
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else if (message == "Clicked")
	{
		gameMediator->notifyComponent("Game", "Explore");
		ButtonState = 0;
		visible = false;
	}
}

void ExploreButton::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		window.draw(*Sprite);
	}
}