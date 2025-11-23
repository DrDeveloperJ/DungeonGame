#include "DungeonBackgroundCache.h"
#include "../GameMediator.h"

DungeonBackgroundCache::DungeonBackgroundCache(std::shared_ptr<GameMediator> gameMediatorPtr)
{
	gameMediator = gameMediatorPtr;
}

Response DungeonBackgroundCache::requestData(const std::string& request)
{
	Response hi = "Hello";
	return hi;
}

void DungeonBackgroundCache::notify(const std::string& message)
{
	if (message == "setVisible")
	{
		visible = true;
	}
	else if (message == "setInvisible")
	{
		visible = false;
	}
	else if (message == "assignRandomBackground")
	{
		currentBackgroundIndex = rand() % backgrounds.size();
	}
	else if (message == "assignCurrentBackground")
	{
		Response dungeonRoomBG = gameMediator->requestData("RoomSelector", "currentDungeonBG");

		if (std::holds_alternative<int>(dungeonRoomBG)) {
			int dungeonBGIncrement = std::get<int>(dungeonRoomBG);
			currentBackgroundIndex = dungeonBGIncrement;
		}
		else {
			std::cerr << "Error: Expected currentDungeonBG, but got " << dungeonRoomBG.index() << std::endl;
		}
	}
}

void DungeonBackgroundCache::Draw(sf::RenderWindow& window)
{
	if (visible)
	{
		backgrounds[currentBackgroundIndex]->Draw(window);
	}
}

void DungeonBackgroundCache::addBackground(std::shared_ptr<PreLoadedElement> background)
{
	backgrounds.push_back(background);
}

int DungeonBackgroundCache::getDungeonBgCount()
{
	return backgrounds.size();
}
