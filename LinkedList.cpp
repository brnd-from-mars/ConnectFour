#include "LinkedList.h"


void LinkedList::addElement(GameData data) {
	
	LinkedListComponent* current = firstElement;

	while (current->next != NULL) {
		current = current->next;
	}

	current->next = new LinkedListComponent;
	LinkedListComponent* previousElement = current;

	current = current->next;

	current->previous = previousElement;
	current->next = NULL;
	current->data = data;

}

GameData* LinkedList::getElementAt(int index) {

	LinkedListComponent* current = firstElement;

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

void LinkedList::sort(SortBy search) { //Bubble-Sort Algorhitmus
	LinkedListComponent* current = firstElement;
	LinkedListComponent* following;
	
	bool wasChange = true;

	while (wasChange) {

		current = firstElement;

		while(current->next != NULL){

			following = current->next;
			
		
			if (current->data.time > following->data.time) { //if following Element is bigger than current

				GameData buffer_data = current->data; 

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
