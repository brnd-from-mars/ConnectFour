#pragma once

#include <string>
#include <functional>


template <typename T>
struct LinkedListComponent
{
	T data;
	LinkedListComponent* next = nullptr;
	LinkedListComponent* previous = nullptr;
};


template <typename T>
class LinkedList
{

private:

	LinkedListComponent<T>* firstElement = new LinkedListComponent<T>;
	
	
public:

    T* operator[] (int index) //overloading []-operator  to make code look cooler :)
    {
        //Function returns pointer at Element (type T) at index in the list
        //starts counting from position 0 (beginning) to position index (if index isn't beyond dimension of list)
        //starts counting from end of list if index is negative

        LinkedListComponent<T>* current = firstElement;

        if (index < 0) {
            while (current->next != nullptr) { //set current pointer to the last object of the list
                current = current->next;
            }
            for (int i = 1; i <= -index; i++) { //counting to index against in opposite direction
                if (current != nullptr) {
                    current = current->previous;
                }
                else {
                    // TODO: throw error
                    return nullptr;
                }
            }
        } else {
            for (int i = 0; i <= index; i++) { //counting to index
                if (current != nullptr) {
                    current = current->next;
                }
                else {
                    // TODO: throw error
                    return nullptr;
                }
            }
        }

        return &current->data;
    }


	void sort(std::function<int(T*)> sortValue)
    {
        //function sorts linked list with elements of type T with bubble-sort algorithm
        //gets a lambda-function which tells, by which value to sort

        LinkedListComponent<T>* current = firstElement;
        LinkedListComponent<T>* following;

        bool wasChange = true;

        while (wasChange) {

            current = firstElement;

            while(current->next != nullptr){ //iterating from begin to end of list as long as there were changes/swaps

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


	void addElement(T data)
    {
        //functions adds an Element of Type T at the end of a double-linked list
        LinkedListComponent<T>* current = firstElement;

        while (current->next != nullptr) { //jumping through list to its end
            current = current->next;
        }

        current->next = new LinkedListComponent<T>;
        LinkedListComponent<T>* previousElement = current;

        current = current->next;

        current->previous = previousElement; //define properties of last (added) element
        current->next = nullptr;
        current->data = data;
    }
};

