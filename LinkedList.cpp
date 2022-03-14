#include "LinkedList.h"


template <typename T>
void LinkedList<T>::addElement(T data) {

	LinkedListComponent<T>* current = firstElement;

	while (current->next != NULL) {
		current = current->next;
	}

	current->next = new LinkedListComponent<T>;
	LinkedListComponent<T>* previousElement = current;

	current = current->next;

	current->previous = previousElement;
	current->next = NULL;
	current->data = data;

}

template <typename T>
T* LinkedList<T>::getElementAt(int index) {

	LinkedListComponent<T>* current = firstElement;

	for (int i = 0; i <= index; i++) {

		if (current != NULL) {
			current = current->next;
		}
		else {
			return NULL;
		}
	}
	return &current->data;
}

template <typename T>
void LinkedList<T>::sort(std::function<int(T*)> sortValue) { //Bubble-Sort Algorhitmus
	LinkedListComponent<T>* current = firstElement;
	LinkedListComponent<T>* following;
	
	bool wasChange = true;

	while (wasChange) {

		current = firstElement;

		while(current->next != NULL){

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