#include "TreasureRoom.h"
#include "../Game.h"

TreasureRoom::TreasureRoom(std::shared_ptr<GameMediator> gameMediatorPtr)
{
	gameMediator = gameMediatorPtr;
}

void TreasureRoom::notify(const std::string& message)
{
	if (message == "createRoom")
	{
		createRoomAssets();
	}
}

Response TreasureRoom::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void TreasureRoom::Draw(sf::RenderWindow& window)
{
}

void TreasureRoom::createRoomAssets()
{
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

	gameMediator->notifyComponent("BackButton", "setVisible");
	gameMediator->notifyComponent("Treasure", "setVisible");
}