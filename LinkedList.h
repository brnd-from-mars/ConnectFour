#pragma once
#include <string>
#include "SessionModel.hpp"

struct GameData {
	std::string player1;
	std::string player2;
	int time;
	PlayerState winState;
	int moves;
};

struct PlayerData {
	std::string name;
	int totalGames;
	int wonGames;
};

struct LinkedListComponent {
	GameData data;
	LinkedListComponent* next = NULL;
	LinkedListComponent* previous = NULL;
};

enum class SortBy {
	time,
	moves,
	wonGames
};



class LinkedList
{
private:
	LinkedListComponent* firstElement = new LinkedListComponent; 
	
public:
	
	void sort(SortBy search);
	void addElement(GameData data);
	GameData* getElementAt(int index);
	
};

