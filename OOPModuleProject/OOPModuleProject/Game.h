#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Component.h"

#include "RoomLogic/RoomTypes.h"
#include "Reuseables/UiElement.h"
#include "Reuseables/Button.h"
#include "RoomLogic/EmptyRoom.h"
#include "Player.h"
#include "EnemyLogic/CombatMediator.h"
#include "DungeonBackground/DungeonBackgroundCache.h"
#include "Reuseables/PreLoadedElement.h"
#include "RoomLogic/DungeonExploredDisplay.h"
#include "Reuseables/TextInput.h"
#include "EnemyLogic/MovesDisplay.h"
#include "GameMediator.h"

class Game:
	public Component
{
private :
	sf::RenderWindow* window;
	sf::Font font = sf::Font("JdmgtR34raz9.ttf");

	std::shared_ptr<GameMediator> gameMediator = std::make_shared<GameMediator>(this);

	bool allButtonsDisableFlag = false;
	std::string shouldRebuildButtons = "";
	std::string eventString = "";

public :
	Game(std::shared_ptr<GameMediator> gameMediatorPtr);
	~Game();

	virtual void Draw(sf::RenderWindow& window) override;
	virtual Response requestData(const std::string& request) override;
	virtual void notify(const std::string& message) override;

	void generateRoomFlag(std::string type);
	void generateDungeonRoom(std::string direction);
	void generateHomePage();
	void generateCustomizeRoom();
	void generateTextInputPage(std::string which);
	void update();
	void render();
	void run();
	void allButtonsDisableFlagON();
	void allButtonsDisableFlagOFF();
};

