#include "DungeonExploredDisplay.h"
#include "../GameMediator.h"

DungeonExploredDisplay::DungeonExploredDisplay(std::shared_ptr<GameMediator> gameMediatorPtr, std::string emptyRoomVisitedDir, std::string monsterRoomVisitedDir, std::string upgradeRoomVisitedDir, std::string treasureRoomVisitedDir, float xOrigin, float yOrigin, float xIncr, float yIncr)
{
	gameMediator = gameMediatorPtr;

	origin = { xOrigin, yOrigin };
	currentIncrement = { xOrigin, yOrigin };
	eachIncrement = { xIncr, yIncr };

	if (emptyRoomTexture.loadFromFile(emptyRoomVisitedDir))
	{
		std::cout << "Loaded emptyRoomTexture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load emptyRoomTexture!");
	}

	if (monsterRoomTexture.loadFromFile(monsterRoomVisitedDir))
	{
		std::cout << "Loaded monsterRoomTexture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load monsterRoomTexture!");
	}

	if (upgradeRoomTexture.loadFromFile(upgradeRoomVisitedDir))
	{
		std::cout << "Loaded upgradeRoomTexture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load upgradeRoomTexture!");
	}

	if (treasureRoomTexture.loadFromFile(treasureRoomVisitedDir))
	{
		std::cout << "Loaded treasureRoomTexture" << std::endl;
	}
	else
	{
		throw std::runtime_error("Failed to load treasureRoomTexture!");
	}
}

void DungeonExploredDisplay::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		for (const auto& exploredDungeon : explored)
		{
			exploredDungeon->Draw(window);
		}
	}
}

Response DungeonExploredDisplay::requestData(const std::string& request)
{
	Response hi = "hello";
	return hi;
}

void DungeonExploredDisplay::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else if (message == "reset")
	{
		reset();
	}
	else if (message == "addExploredDungeonDisplay")
	{
		Response roomTypeResponse = gameMediator->requestData("RoomSelector", "currentRoomType?");

		if (std::holds_alternative<int>(roomTypeResponse)) {
			int roomType = std::get<int>(roomTypeResponse);
			addExploredDungeonDisplay(roomType);
		}
		else {
			std::cerr << "Error: Expected roomType, but got " << roomTypeResponse.index() << std::endl;
		}
	}
}

void DungeonExploredDisplay::addExploredDungeonDisplay(int type)
{
	currentIncrement.first += eachIncrement.first;
	currentIncrement.second += eachIncrement.second;

	if (type == 1)
	{
		std::shared_ptr<PreLoadedElement> emptyRoomDisplay = std::make_shared<PreLoadedElement>("EmptyRoomDisplay", emptyRoomTexture, currentIncrement.first, currentIncrement.second, 0.3f, 0.3f);
		explored.push_back(emptyRoomDisplay);
	}
	else if (type == 2)
	{
		std::shared_ptr<PreLoadedElement> monsterRoomDisplay = std::make_shared<PreLoadedElement>("MonsterRoomDisplay", monsterRoomTexture, currentIncrement.first, currentIncrement.second, 0.3f, 0.3f);
		explored.push_back(monsterRoomDisplay);
	}
	else if (type == 3)
	{
		std::shared_ptr<PreLoadedElement> upgradeRoomDisplay = std::make_shared<PreLoadedElement>("UpgradeRoomDisplay", upgradeRoomTexture, currentIncrement.first, currentIncrement.second, 0.3f, 0.3f);
		explored.push_back(upgradeRoomDisplay);
	}
	else if (type == 0)
	{
		std::shared_ptr<PreLoadedElement> treasureRoomDisplay = std::make_shared<PreLoadedElement>("TreasureRoomDisplay", treasureRoomTexture, currentIncrement.first, currentIncrement.second, 0.3f, 0.3f);
		explored.push_back(treasureRoomDisplay);
	}
}

void DungeonExploredDisplay::reset()
{
	explored.clear();
	currentIncrement = origin;
}
