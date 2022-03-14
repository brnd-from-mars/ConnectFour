#include "LinkedList.h"
#include <iostream>


template <typename T>
void LinkedList<T>::addElement(T data) {

//functions adds an Element of Type T at the end of a double-linked list

	LinkedListComponent<T>* current = firstElement;

	while (current->next != NULL) { //jumping through list to its end
		current = current->next;
	}

	current->next = new LinkedListComponent<T>;
	LinkedListComponent<T>* previousElement = current;

	current = current->next;

	current->previous = previousElement; //define properties of last (added) element
	current->next = NULL;
	current->data = data;

}

template <typename T>
T* LinkedList<T>::getElementAt(int index) { 

//Function returns pointer at Element (type T) at index in the list
//starts counting from position 0 (beginning) to position index (if index isn't beyond dimension of list)
//starts counting from end of list if index is negative 

	LinkedListComponent<T>* current = firstElement;

	if (index < 0) {

		while (current->next != NULL) { //set current pointer to the last object of the list
			current = current->next;
		}

		for (int i = 1; i <= -index; i++) { //counting to index against in opposite direction

			if (current != NULL) {
				current = current->previous;
			}
			else {
				std::cout << "ERROR: Index bigger than size of list" << std::endl;
				return NULL;
				
			}
		}
	}else {

		for (int i = 0; i <= index; i++) { //counting to index 

		if (current != NULL) {
			current = current->next;
		}
		else {
			std::cout << "ERROR: Index bigger than size of list" << std::endl;
			return NULL;
			
		}
	}
	}

	return &current->data;
}

template <typename T>
void LinkedList<T>::sort(std::function<int(T*)> sortValue) { 

//function sorts linked list with elements of type T with bubble-sort algorithm
//gets a lambda-function which tells, by wich value to sort

	LinkedListComponent<T>* current = firstElement;
	LinkedListComponent<T>* following;
	
	bool wasChange = true;

	while (wasChange) { 

		current = firstElement;

		while(current->next != NULL){ //iterating from begin to end of list as long as there were changes/swaps

			following = current->next;
			
		    if (sortValue(&current->data) > sortValue(&following->data)) { //if following Element is bigger than current

				T buffer_data = current->data;

				current->data = following->data; //Swap saved Data
				following->data = buffer_data;

				wasChange = true;

			}else {
				wasChange = false;
			}

			current = current->next;
		}

		current = firstElement;
	}

}



template class LinkedList<GameData>;
template class LinkedList<PlayerData>;