#include "UpgradeRoom.h"
#include "../Game.h"

UpgradeRoom::UpgradeRoom(std::shared_ptr<GameMediator> gameMediatorPtr)
{
	gameMediator = gameMediatorPtr;
}

void UpgradeRoom::notify(const std::string& message)
{
	if (message == "createRoom")
	{
		createRoomAssets();
	}
}

Response UpgradeRoom::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void UpgradeRoom::Draw(sf::RenderWindow& window)
{
}

void UpgradeRoom::createRoomAssets()
{
	Response firstRoom = gameMediator->requestData("RoomSelector", "IsFirstRoom?");

	if (std::holds_alternative<bool>(firstRoom)) {
		bool first = std::get<bool>(firstRoom);

		if (first)
		{
			gameMediator->notifyComponent("BackButton", "setInvisible");
		}
		else
		{
			gameMediator->notifyComponent("BackButton", "setVisible");
		}
	}
	else {
		std::cerr << "Error: Expected firstRoom, but got " << firstRoom.index() << std::endl;
	}

	gameMediator->notifyComponent("ForwardButton", "setVisible");

	Response claimedUpgrade = gameMediator->requestData("Player", "ClaimedUpgrade?");

	if (std::holds_alternative<bool>(claimedUpgrade)) {
		bool claimed = std::get<bool>(claimedUpgrade);

		if (claimed)
		{
			gameMediator->notifyComponent("UpgradeAttackButton", "setInvisible");
			gameMediator->notifyComponent("UpgradeMaxHealthButton", "setInvisible");
		}
		else
		{
			gameMediator->notifyComponent("UpgradeAttackButton", "setVisible");
			gameMediator->notifyComponent("UpgradeMaxHealthButton", "setVisible");
		}
	}
	else {
		std::cerr << "Error: Expected claimedUpgrade, but got " << claimedUpgrade.index() << std::endl;
	}

	Response visitedRoom = gameMediator->requestData("RoomSelector", "Visited?");

	if (std::holds_alternative<bool>(visitedRoom)) {
		bool visited = std::get<bool>(visitedRoom);
		if (!visited)
		{
			gameMediator->notifyComponent("RoomSelector", "setVisited");
		}
	}
	else {
		std::cerr << "Error: Expected visitedRoom, but got " << visitedRoom.index() << std::endl;
	}
}
