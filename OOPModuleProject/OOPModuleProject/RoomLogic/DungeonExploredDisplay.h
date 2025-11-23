#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Component.h"
#include "../Reuseables/PreLoadedElement.h"
#include "RoomTypes.h"

class DungeonExploredDisplay :
	public Component
{
protected :
	sf::Texture emptyRoomTexture;
	sf::Texture monsterRoomTexture;
	sf::Texture upgradeRoomTexture;
	sf::Texture treasureRoomTexture;
	std::vector<std::shared_ptr<PreLoadedElement>> explored;
	std::pair<float, float> origin;
	std::pair<float, float> currentIncrement;
	std::pair<float, float> eachIncrement;

public :
	DungeonExploredDisplay(std::shared_ptr<GameMediator> gameMediatorPtr, std::string emptyRoomVisitedDir, std::string monsterRoomVisitedDir, std::string upgradeRoomVisitedDir, std::string treasureRoomVisitedDir, float xOrigin, float yOrigin, float xIncr, float yIncr);
	
	virtual void Draw(sf::RenderWindow& window) override;
	virtual Response requestData(const std::string& request) override;
	virtual void notify(const std::string& message) override;

	virtual void addExploredDungeonDisplay(int type);
	virtual void reset();
};

