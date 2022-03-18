#pragma once

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

	LinkedListComponent<T>* m_FirstElement = nullptr;
	
	
public:

    ~LinkedList()
    {
        LinkedListComponent<T>* current = m_FirstElement;

        while (current != nullptr)
        {
            LinkedListComponent<T>* next = current->next;
            delete current;
            current = next;
        }
    }


    void AddElement(T element)
    {
        if (m_FirstElement == nullptr)
        {
            m_FirstElement = new LinkedListComponent<T>;
            m_FirstElement->data = element;
            return;
        }

        LinkedListComponent<T>* current = m_FirstElement;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = new LinkedListComponent<T>;
        current->next->data = element;
        current->next->previous = current;
    }


    void ForEach(std::function<void(T*)> function)
    {
        LinkedListComponent<T>* current = m_FirstElement;

        while (current != nullptr)
        {
            function(&current->data);
            current = current->next;
        }
    }


    T* Find(std::function<bool(T*)> filter)
    {
        LinkedListComponent<T>* current = m_FirstElement;

        while (current != nullptr)
        {
            if (filter(&current->data))
            {
                return &current->data;
            }
            current = current->next;
        }

        return nullptr;
    }


    void Sort(std::function<int(T*)> getSortValue)
    {
        LinkedListComponent<T>* current = nullptr;
        LinkedListComponent<T>* next = nullptr;

        bool changed = true;

        while (changed)
        {
            changed = false;
            current = m_FirstElement;
            while (current != nullptr && current->next != nullptr)
            {
                next = current->next;
                if (getSortValue(&current->data) > getSortValue(&next->data))
                {
                    T buffer = current->data;
                    current->data = next->data;
                    next->data = buffer;
                    changed = true;
                }

                current = current->next;
            }
        }
    }


    T* operator[] (int index) //overloading []-operator  to make code look cooler :)
    {
        //Function returns pointer at Element (type T) at index in the list
        //starts counting from position 0 (beginning) to position index (if index isn't beyond dimension of list)
        //starts counting from end of list if index is negative

        LinkedListComponent<T>* current = m_FirstElement;

        if (index >= 0)
        {
            for (int i = 0; i < index; ++i)
            {
                if (current != nullptr)
                {
                    current = current->next;
                }
                else
                {
                    // TODO: throw error
                    return nullptr;
                }
            }
        }
        else
        {
            if (current == nullptr)
            {
                return nullptr;
            }

            while (current->next != nullptr) //set current pointer to the last object of the list
            {
                current = current->next;
            }
            for (int i = -1; i > index; --i) //counting to index against in opposite direction
            {
                if (current != nullptr)
                {
                    current = current->previous;
                }
                else
                {
                    // TODO: throw error
                    return nullptr;
                }
            }
        }

        return &current->data;
    }
};
