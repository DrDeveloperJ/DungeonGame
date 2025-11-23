#include "EmptyRoom.h"
#include "../Game.h"

EmptyRoom::EmptyRoom(std::shared_ptr<GameMediator> gameMediatorPtr)
{
	gameMediator = gameMediatorPtr;
}

void EmptyRoom::notify(const std::string& message)
{
	if (message == "createRoom")
	{
		createRoomAssets();
	}
}

Response EmptyRoom::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void EmptyRoom::Draw(sf::RenderWindow& window)
{
}

void EmptyRoom::createRoomAssets()
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

	gameMediator->notifyComponent("ForwardButton", "setVisible");

	gameMediator->notifyComponent("MeditateButton", "setVisible");
}

