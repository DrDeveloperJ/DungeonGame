#include "MonsterRoom.h"
#include "../Game.h"

MonsterRoom::MonsterRoom(std::shared_ptr<GameMediator> gameMediatorPtr)
{
	gameMediator = gameMediatorPtr;
}

void MonsterRoom::notify(const std::string& message)
{
	if (message == "createRoom")
	{
		createRoomAssets();
	}
}

Response MonsterRoom::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void MonsterRoom::Draw(sf::RenderWindow& window)
{
}

void MonsterRoom::createRoomAssets()
{
	Response visitedRoom = gameMediator->requestData("RoomSelector", "Visited?");

	if (std::holds_alternative<bool>(visitedRoom)) {
		bool visited = std::get<bool>(visitedRoom);

		Response firstRoom = gameMediator->requestData("RoomSelector", "IsFirstRoom?");

		if (std::holds_alternative<bool>(firstRoom)) {
			bool first = std::get<bool>(firstRoom);

			if (first)
			{
				if (visited)
				{
					gameMediator->notifyComponent("ForwardButton", "setVisible");
					gameMediator->notifyComponent("BackButton", "setInvisible");
					gameMediator->notifyComponent("AttackButton", "setInvisible");
					gameMediator->notifyComponent("GuardButton", "setInvisible");
				}
				else
				{
					gameMediator->notifyComponent("RoomSelector", "setVisited");
					gameMediator->notifyComponent("AttackButton", "setVisible");
					gameMediator->notifyComponent("GuardButton", "setVisible");
					gameMediator->notifyComponent("CombatMediator", "inCombat");
					gameMediator->notifyComponent("MovesDisplay", "setInvisible");
					gameMediator->notifyComponent("ForwardButton", "setInvisible");
					gameMediator->notifyComponent("BackButton", "setInvisible");
					gameMediator->notifyComponent("Enemy", "setVisible");
					gameMediator->notifyComponent("Enemy", "setPositionDefault");
				}
			}
			else
			{
				if (visited)
				{
					gameMediator->notifyComponent("ForwardButton", "setVisible");
					gameMediator->notifyComponent("BackButton", "setVisible");
					gameMediator->notifyComponent("AttackButton", "setInvisible");
					gameMediator->notifyComponent("GuardButton", "setInvisible");
				}
				else
				{
					gameMediator->notifyComponent("RoomSelector", "setVisited");
					gameMediator->notifyComponent("AttackButton", "setVisible");
					gameMediator->notifyComponent("GuardButton", "setVisible");
					gameMediator->notifyComponent("CombatMediator", "inCombat");
					gameMediator->notifyComponent("MovesDisplay", "setInvisible");
					gameMediator->notifyComponent("ForwardButton", "setInvisible");
					gameMediator->notifyComponent("BackButton", "setInvisible");
					gameMediator->notifyComponent("Enemy", "setVisible");
					gameMediator->notifyComponent("Enemy", "setPositionDefault");

				}
			}
		}
		else {
			std::cerr << "Error: Expected firstRoom, but got " << firstRoom.index() << std::endl;
		}
	}
	else {
		std::cerr << "Error: Expected firstRoom, but got " << visitedRoom.index() << std::endl;
	}
}
