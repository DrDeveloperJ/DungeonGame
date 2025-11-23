#include "RoomSelector.h"

std::pair<int, int> RoomSelector::dungeonRoomSelector()
{
	// Increment will be -1 anyway because it's reset when treasure is opened

	increment++;
	currentDungeonIncrement++;
	visited[increment] = false; // The room generated will set this to visited

	if (increment > 0)
	{
		if (increment == maxDungeonRooms)
		{
			int chosenDungeonBackground = rand() % numOfDungeonBGs;
			std::pair<int, int> treasureRoom;
			treasureRoom = { 0, chosenDungeonBackground };
			currentDungeonRoomsList.push_back(treasureRoom);
			return treasureRoom;
		}
		else
		{
			firstRoom = false;
			int chosenDungeonBackground = rand() % numOfDungeonBGs;
			int chosenDungeon = rand() % numOfDungeonRooms;
			chosenDungeon++; // Can't be a treasureRoom yet

			// So never have same dungeon twice in a row
			while (chosenDungeon == currentDungeonRoomsList[increment - 1].first)
			{
				chosenDungeon = rand() % (numOfDungeonRooms - 1);
				chosenDungeon++;
			}

			std::pair<int, int> dungeonRoom;
			dungeonRoom = { chosenDungeon, chosenDungeonBackground };
			currentDungeonRoomsList.push_back(dungeonRoom);
			return dungeonRoom;
		}
	}
	else
	{
		// First Room Generated

		if (difficulty == 1)
		{
			std::srand(std::time(nullptr)); // Seeds the random number generator using current time
			maxDungeonRooms = easyDifficultyMinRooms + std::rand() % (easyDifficultyMaxRooms - easyDifficultyMinRooms + 1);

		}
		else
		{
			std::srand(std::time(nullptr)); // Seeds the random number generator using current time
			maxDungeonRooms = hardDifficultyMinRooms + std::rand() % (hardDifficultyMaxRooms - hardDifficultyMinRooms + 1);
		}

		firstRoom = true;
		int chosenDungeonBackground = rand() % numOfDungeonBGs;
		int chosenDungeon = rand() % numOfDungeonRooms;
		chosenDungeon++; // Can't be a treasureRoom yet

		std::pair<int, int> dungeonRoom;
		dungeonRoom = { chosenDungeon, chosenDungeonBackground };
		currentDungeonRoomsList.push_back(dungeonRoom);
		return dungeonRoom;
	}
}

RoomType RoomSelector::intToRoom(int integer)
{
	switch (integer) {
	case 0: return RoomType::TreasureRoom;
	case 1: return RoomType::EmptyRoom;
	case 2: return RoomType::MonsterRoom;
	case 3: return RoomType::UpgradeRoom;
	default: throw std::invalid_argument("Invalid RoomType value.");
	}

}

bool RoomSelector::checkIfFirstRoom()
{
	return firstRoom;
}

bool RoomSelector::isCurrentRoomVisited()
{
	return visited[currentDungeonIncrement];
}

std::pair<int, int> RoomSelector::moveBackward()
{
	currentDungeonIncrement--;

	if (currentDungeonIncrement == 0)
	{
		firstRoom = true;
	}

	return currentDungeonRoomsList[currentDungeonIncrement];
}

std::pair<std::pair<int, int>, bool> RoomSelector::moveForward()
{
	if (currentDungeonIncrement < increment)
	{
		currentDungeonIncrement++;

		if (firstRoom)
		{
			firstRoom = false;
		}
	}
	else
	{
		std::pair<std::pair<int, int>, bool> pairWithVisitedCheck;
		pairWithVisitedCheck = { dungeonRoomSelector(), false };
		return pairWithVisitedCheck;
	}

	std::pair<std::pair<int, int>, bool> pairWithVisitedCheck;
	pairWithVisitedCheck = { currentDungeonRoomsList[currentDungeonIncrement], true };
	return pairWithVisitedCheck;
}

void RoomSelector::reset()
{
	increment = -1;
	currentDungeonIncrement = -1;
	firstRoom = true;

	std::unordered_map<int, bool> newVisited;
	visited = newVisited;

	std::vector<std::pair<int, int>> newCurrentDungeonRoomsList;
	currentDungeonRoomsList = newCurrentDungeonRoomsList;
}

int RoomSelector::getCurrentDungeonIncr()
{
	return currentDungeonIncrement;
}

Response RoomSelector::requestData(const std::string& request)
{
	if (request == "FirstRoom")
	{

		std::pair<int, int> which = dungeonRoomSelector();
		int chosenDungeon = which.first;
		int chosenDungeonBackground = which.second;

		std::pair<RoomType, int> room = { intToRoom(chosenDungeon), chosenDungeonBackground };
		Response roomToReturn = std::make_pair(room, isCurrentRoomVisited());

		return roomToReturn;
	}
	else if (request == "Forward")
	{
		std::pair<std::pair<int, int>, bool> which = moveForward();
		int chosenDungeon = which.first.first;
		int chosenDungeonBackground = which.first.second;

		std::pair<RoomType, int> room = { intToRoom(chosenDungeon), chosenDungeonBackground };
		Response roomToReturn = std::make_pair( room, which.second );

		return roomToReturn;
	}
	else if (request == "Backward")
	{
		std::pair<int, int> which = moveBackward();
		int chosenDungeon = which.first;
		int chosenDungeonBackground = which.second;

		std::pair<RoomType, int> room = { intToRoom(chosenDungeon), chosenDungeonBackground };
		Response roomToReturn = std::make_pair( room, true );

		return roomToReturn;
	}
	else if (request == "CurrentDungeonIncrement")
	{
		return currentDungeonIncrement;
	}
	else if (request == "currentDungeonBG")
	{
		return currentDungeonRoomsList[currentDungeonIncrement].second;
	}
	else if (request == "IsFirstRoom?")
	{
		return firstRoom;
	}
	else if (request == "Visited?")
	{
		return visited[currentDungeonIncrement];
	}
	else if (request == "currentRoomType?")
	{
		return currentDungeonRoomsList[currentDungeonIncrement].first;
	}

	Response hi = "hello";
	return hi;
}

void RoomSelector::notify(const std::string& message)
{
	if (message == "setHardDifficulty")
	{
		difficulty = 2;
	}
	else if (message == "setEasyDifficulty")
	{
		difficulty = 1;
	}
	else if (message == "reset")
	{
		reset();
	}
	else if (message == "setIncrement")
	{
		increment = currentDungeonIncrement;
	}
	else if (message == "setCurrentDungeonIncrement")
	{
		currentDungeonIncrement = increment;
	}
	else if (message == "setVisited")
	{
		visited[currentDungeonIncrement] = true;
	}
}

void RoomSelector::Draw(sf::RenderWindow& window)
{
	// No drawing needed for this component
}

RoomSelector::RoomSelector(int numOfDungeonBGsInit, int numOfDungeonRoomsInit) : numOfDungeonBGs(numOfDungeonBGsInit), numOfDungeonRooms(numOfDungeonRoomsInit)
{
}

void RoomSelector::setDifficulty(int givenDifficulty)
{
	difficulty = givenDifficulty;
}
