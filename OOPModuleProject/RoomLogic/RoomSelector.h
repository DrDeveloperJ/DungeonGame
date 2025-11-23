#pragma once
#include <iostream>
#include <vector>
#include "../Component.h"

#include "RoomTypes.h"
#include <unordered_map>

class RoomSelector :
	public Component
{
protected:
	int difficulty = 1; // 1 = easy, 2 = hard
	int increment = -1; // explored up until
	int currentDungeonIncrement = -1; // current dungeon increment
	int maxDungeonRooms = 0;
	int numOfDungeonBGs;
	int numOfDungeonRooms; // Not including TreasureRoom
	int easyDifficultyMinRooms = 6;
	int easyDifficultyMaxRooms = 10;
	int hardDifficultyMinRooms = 9;
	int hardDifficultyMaxRooms = 15;
	bool firstRoom = true;
	std::vector<std::pair<int, int>> currentDungeonRoomsList;
	std::unordered_map<int, bool> visited;

public:
	virtual Response requestData(const std::string& request) override;
	virtual void notify(const std::string& message) override;
	virtual void Draw(sf::RenderWindow& window) override;

	RoomSelector(int numOfDungeonBGs, int numOfDungeonRooms);
	void setDifficulty(int givenDifficulty);
	std::pair<int, int> dungeonRoomSelector();
	RoomType intToRoom(int integer);
	bool checkIfFirstRoom();
	bool isCurrentRoomVisited();
	std::pair<int, int> moveBackward();
	std::pair<std::pair<int, int>, bool> moveForward();
	void reset();
	int getCurrentDungeonIncr();
};

