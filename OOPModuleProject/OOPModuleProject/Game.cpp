#include "Game.h"
#include <sstream>

Game::Game(std::shared_ptr<GameMediator> gameMediatorPtr) : gameMediator(gameMediatorPtr)
{
	this->window = new sf::RenderWindow(sf::VideoMode({ 1280, 720 }), "Dungeon Game");
	this->window->setPosition({ 0, 0 });
	this->window->setFramerateLimit(60);

	generateRoomFlag("HomePage");
}

Game::~Game()
{
	delete this->window;
}

void Game::Draw(sf::RenderWindow& window)
{
}

Response Game::requestData(const std::string& request)
{
	Response hi = "hello";

	if (request == "RenderWindow")
	{
		return this->window;
	}
	else if (request == "EventString")
	{
		return eventString;
	}

	return hi;
}

void Game::notify(const std::string& message)
{
	if (message == "Explore")
	{
		generateRoomFlag("DungeonGenerate");
	}
	else if (message == "MoveForward")
	{
		generateRoomFlag("MoveForward");
	}
	else if (message == "MoveBackward")
	{
		generateRoomFlag("MoveBackward");
	}
	else if (message == "Customize")
	{
		generateRoomFlag("CustomizePage");
	}
	else if (message == "HomePage")
	{
		generateRoomFlag("HomePage");
	}
	else if (message == "ChangeName")
	{
		generateRoomFlag("CustomizeNamePage");
	}
	else if (message == "ChangeDescription")
	{
		generateRoomFlag("CustomizeDescriptionPage");
	}
}

void Game::generateRoomFlag(std::string type) {
	shouldRebuildButtons = type;
}

void Game::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}

void Game::allButtonsDisableFlagON()
{
	allButtonsDisableFlag = true;
}

void Game::allButtonsDisableFlagOFF()
{
	allButtonsDisableFlag = false;
}

void Game::update()
{
	Response inCombatCurrently = gameMediator->requestData("CombatMediator", "inCombat?");

	if (std::holds_alternative<bool>(inCombatCurrently)) {
		bool inCombat = std::get<bool>(inCombatCurrently);
		if (inCombat)
		{
			gameMediator->notifyComponent("EnemyHealthBar", "setVisible");
		}
		else
		{
			gameMediator->notifyComponent("EnemyHealthBar", "setInvisible");
			gameMediator->notifyComponent("MovesDisplay", "setInvisible");
		}
	}
	else {
		std::cerr << "Error: Expected inCombatCurrently, but got " << inCombatCurrently.index() << std::endl;
	}

	if (shouldRebuildButtons == "HomePage")
	{
		generateHomePage();
		shouldRebuildButtons = "";
	}
	else if (shouldRebuildButtons == "CustomizePage")
	{
		generateCustomizeRoom();
		shouldRebuildButtons = "";
	}
	else if (shouldRebuildButtons == "DungeonGenerate")
	{
		generateDungeonRoom("First");
		shouldRebuildButtons = "";
	}
	else if (shouldRebuildButtons == "MoveForward")
	{
		generateDungeonRoom("Forward");
		shouldRebuildButtons = "";
	}
	else if (shouldRebuildButtons == "MoveBackward")
	{
		generateDungeonRoom("Backward");
		shouldRebuildButtons = "";
	}
	else if (shouldRebuildButtons == "CustomizeNamePage")
	{
		generateTextInputPage("Name");
		shouldRebuildButtons = "";
	}
	else if (shouldRebuildButtons == "CustomizeDescriptionPage")
	{
		generateTextInputPage("Description");
		shouldRebuildButtons = "";
	}

	gameMediator->notifyComponent("Player", "checkMeditating");

	Response inCombat = gameMediator->requestData("CombatMediator", "inCombat?");

	if (std::holds_alternative<bool>(inCombat))
	{
		if (std::get<bool>(inCombat))
		{
			gameMediator->notifyComponent("EnemyHealthBar", "setVisible");

			gameMediator->notifyComponent("CombatMediator", "CheckBothHealth");
		}
		else if (!(std::get<bool>(inCombat)))
		{
		}
	}

	if (!allButtonsDisableFlag)
	{
		gameMediator->updateButtonStates();
	}

	while (const std::optional Event = this->window->pollEvent())
	{
		if ((!allButtonsDisableFlag) && (Event->is<sf::Event::MouseButtonPressed>()))
		{
			gameMediator->notifyButtonClick();
		}
		else if (Event->is<sf::Event::Closed>())
		{
			window->close();
		}
		else if (Event->is<sf::Event::TextEntered>())
		{
			Response textInputResponse = gameMediator->requestData("TextInput", "getVisible");

			if (std::holds_alternative<bool>(textInputResponse)) {
				bool textInput = std::get<bool>(textInputResponse);
				if (textInput)
				{
					const auto& textEvent = Event->getIf<sf::Event::TextEntered>();
					uint32_t unicode = textEvent->unicode;

					Response textInputLimit = gameMediator->requestData("TextInput", "charLimit");

					if (std::holds_alternative<int>(textInputLimit)) {
						int inputLimit = std::get<int>(textInputLimit);
						if (eventString.length() < inputLimit)
						{
							if ((unicode >= 'A' && unicode <= 'Z') || (unicode >= 'a' && unicode <= 'z')) {
								// Handle alphabetical characters only

								eventString += (char)unicode;
								gameMediator->notifyComponent("TextInput", "handleTextEntered");
							}
						}
					}
				}
			}
			else {
				std::cerr << "Error: Expected textInputResponse, but got " << textInputResponse.index() << std::endl;
			}			
		}
		else if (Event->is<sf::Event::KeyPressed>())
		{
			Response textInputResponse = gameMediator->requestData("TextInput", "getVisible");

			if (std::holds_alternative<bool>(textInputResponse)) {
				bool textInput = std::get<bool>(textInputResponse);
				if (textInput)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace))
					{
						if (!eventString.empty()) {
							eventString.pop_back(); // Remove the last character
							gameMediator->notifyComponent("TextInput", "handleTextEntered");
						}
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
					{
						eventString += ' '; // Add a space
						gameMediator->notifyComponent("TextInput", "handleTextEntered");
					}
				}
			}
			else {
				std::cerr << "Error: Expected textInputResponse, but got " << textInputResponse.index() << std::endl;
			}
		}
	}

	// Player Health Bar
	gameMediator->notifyComponent("PlayerHealthBar", "setVisible");

	// Player AttackPoints Bar
	gameMediator->notifyComponent("AttackPointsBar", "setVisible");
}

void Game::render()
{
	window->clear();

	gameMediator->drawAll();

	window->display();
}

void Game::generateHomePage()
{
	allButtonsDisableFlag = true;

	gameMediator->notifyComponent("ExploredDungeonsDisplay", "reset");
	gameMediator->makeAllInvisible();
	gameMediator->notifyComponent("Player", "setVisible");

	gameMediator->notifyComponent("DungeonBackgroundCache", "assignRandomBackground");
	gameMediator->notifyComponent("DungeonBackgroundCache", "setVisible");

	gameMediator->notifyComponent("CustomizeButton", "setVisible");
	gameMediator->notifyComponent("ExploreButton", "setVisible");
	gameMediator->notifyComponent("EasyDifficultyButton", "setVisible");
	gameMediator->notifyComponent("HardDifficultyButton", "setVisible");

	allButtonsDisableFlag = false;
}

void Game::generateCustomizeRoom()
{
	allButtonsDisableFlag = true;
	gameMediator->makeAllInvisible();

	gameMediator->notifyComponent("Player", "setVisible");
	gameMediator->notifyComponent("DungeonBackgroundCache", "assignRandomBackground");
	gameMediator->notifyComponent("DungeonBackgroundCache", "setVisible");

	gameMediator->notifyComponent("NameDisplay", "setVisible");

	gameMediator->notifyComponent("DescriptionDisplay", "setVisible");

	gameMediator->notifyComponent("HomePageButton", "setVisible");

	gameMediator->notifyComponent("CustomizeNameButton", "setVisible");

	gameMediator->notifyComponent("CustomizeDescriptionButton", "setVisible");
	
	allButtonsDisableFlag = false;
}

void Game::generateTextInputPage(std::string which)
{
	allButtonsDisableFlag = true;
	gameMediator->makeAllInvisible();

	if (which == "Name")
	{
		gameMediator->notifyComponent("Player", "setVisible");
		gameMediator->notifyComponent("DungeonBackgroundCache", "assignRandomBackground");
		gameMediator->notifyComponent("DungeonBackgroundCache", "setVisible");

		gameMediator->notifyComponent("NameDisplay", "setVisible");
		gameMediator->notifyComponent("DescriptionDisplay", "setInvisible");

		gameMediator->notifyComponent("TextInput", "setVisible");

		gameMediator->notifyComponent("ChangeNameButton", "setVisible");
	}
	else if (which == "Description")
	{
		gameMediator->notifyComponent("Player", "setVisible");
		gameMediator->notifyComponent("DungeonBackgroundCache", "assignRandomBackground");
		gameMediator->notifyComponent("DungeonBackgroundCache", "setVisible");

		gameMediator->notifyComponent("DescriptionDisplay", "setVisible");
		gameMediator->notifyComponent("NameDisplay", "setInvisible");

		gameMediator->notifyComponent("TextInput", "setVisible");

		gameMediator->notifyComponent("ChangeDescriptionButton", "setVisible");
	}

	allButtonsDisableFlag = false;
}

void Game::generateDungeonRoom(std::string direction)
{
	allButtonsDisableFlag = true;
	gameMediator->makeAllInvisible();
	gameMediator->notifyComponent("Player", "setVisible");
	gameMediator->notifyComponent("ExploredDungeonsDisplay", "setVisible");

	if (direction == "First")
	{
		std::cout << "First Room" << std::endl;

		Response dungeonRoom = gameMediator->requestData("RoomSelector", "FirstRoom");

		if (std::holds_alternative<std::pair<std::pair<RoomType, int>, bool>>(dungeonRoom)) {
			std::pair<std::pair<RoomType, int>, bool> dungeonRoomChosen = std::get<std::pair<std::pair<RoomType, int>, bool>>(dungeonRoom);

			RoomType type = dungeonRoomChosen.first.first;
			int dungeonBackground = dungeonRoomChosen.first.second;
			bool visited = false;

            std::ostringstream oss;
            oss << type;
            gameMediator->notifyComponent("ExploredDungeonsDisplay", "addExploredDungeonDisplay");

			gameMediator->notifyComponent("DungeonBackgroundCache", "assignCurrentBackground");
			gameMediator->notifyComponent("DungeonBackgroundCache", "setVisible");

			gameMediator->notifyComponent(oss.str(), "createRoom");

			std::cout << oss.str() << std::endl;
		}
		else {
			std::cerr << "Error: Expected dungeonRoomChosen, but got " << dungeonRoom.index() << std::endl;
		}
	}
	else if (direction == "Forward")
	{
		std::cout << "Forward" << std::endl;

		Response dungeonRoom = gameMediator->requestData("RoomSelector", "Forward");

		if (std::holds_alternative<std::pair<std::pair<RoomType, int>, bool>>(dungeonRoom)) {
			std::pair<std::pair<RoomType, int>, bool> dungeonRoomChosen = std::get<std::pair<std::pair<RoomType, int>, bool>>(dungeonRoom);

			RoomType type = dungeonRoomChosen.first.first;
			int dungeonBackground = dungeonRoomChosen.first.second;
			bool visited = dungeonRoomChosen.second;

			std::ostringstream oss;
			oss << type;

			gameMediator->notifyComponent("ExploredDungeonsDisplay", "setVisible");

			if (!visited)
			{
				gameMediator->notifyComponent("ExploredDungeonsDisplay", "addExploredDungeonDisplay");
			}

			gameMediator->notifyComponent("DungeonBackgroundCache", "assignCurrentBackground");
			gameMediator->notifyComponent("DungeonBackgroundCache", "setVisible");

			gameMediator->notifyComponent(oss.str(), "createRoom");

			std::cout << oss.str() << std::endl;
		}
		else {
			std::cerr << "Error: Expected dungeonRoomChosen, but got " << dungeonRoom.index() << std::endl;
		}
	}
	else if (direction == "Backward")
	{
		std::cout << "Backward" << std::endl;

		Response dungeonRoom = gameMediator->requestData("RoomSelector", "Backward");

		if (std::holds_alternative<std::pair<std::pair<RoomType, int>, bool>>(dungeonRoom)) {
			std::pair<std::pair<RoomType, int>, bool> dungeonRoomChosen = std::get<std::pair<std::pair<RoomType, int>, bool>>(dungeonRoom);

			RoomType type = dungeonRoomChosen.first.first;
			int dungeonBackground = dungeonRoomChosen.first.second;

			std::ostringstream oss;
			oss << type;

			gameMediator->notifyComponent("ExploredDungeonsDisplay", "setVisible");

			Response visitedRoom = gameMediator->requestData("RoomSelector", "Visited?");

			if (std::holds_alternative<bool>(visitedRoom)) {
				bool visited = std::get<bool>(visitedRoom);
				if (!visited)
				{
					gameMediator->notifyComponent("ExploredDungeonsDisplay", oss.str());
				}
			}
			else {
				std::cerr << "Error: Expected visitedRoom, but got " << visitedRoom.index() << std::endl;
			}

			gameMediator->notifyComponent("DungeonBackgroundCache", "assignCurrentBackground");
			gameMediator->notifyComponent("DungeonBackgroundCache", "setVisible");

			gameMediator->notifyComponent(oss.str(), "createRoom");

			std::cout << oss.str() << std::endl;
		}
		else {
			std::cerr << "Error: Expected dungeonRoomChosen, but got " << dungeonRoom.index() << std::endl;
		}
	}

	allButtonsDisableFlag = false;
}