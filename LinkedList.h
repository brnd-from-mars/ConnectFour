#pragma once
#include <string>
#include <functional>
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

template <typename T>
struct LinkedListComponent {
	T data;
	LinkedListComponent* next = NULL;
	LinkedListComponent* previous = NULL;
};

template <typename T>
class LinkedList
{
private:
	LinkedListComponent<T>* firstElement = new LinkedListComponent<T>;
	
	
public:

    T* operator[] (int i) //overloading []-operator  to make code look cooler :)
    {
        return getElementAt(i);
    }
	void sort(std::function<int(T*)> sortValue);
	void addElement(T data);
	T* getElementAt(int index);
	
};

