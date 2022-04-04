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

    /*! 
    *   @brief  Pointer at first Element of a linked list, which can contain
    *           objects of any type T;
    *           declared as nullpointer by default 
    */
	LinkedListComponent<T>* m_FirstElement = nullptr;
	
	
public:

    /*!
   *   @brief   destructor of LinkedList object;
   *            when called, iterates through list and deletes every element
   */
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

    /*!
    *   @brief  Function adds an element of a specified type T to the end of a linked list
    *
    *   @param  object to be added to the linked list
    */
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

    /*!
   *   @brief  
   *
   *   @return
   *   @param
   */
    void ForEach(std::function<void(T*)> function)
    {
        LinkedListComponent<T>* current = m_FirstElement;

        while (current != nullptr)
        {
            function(&current->data);
            current = current->next;
        }
    }

    /*!
    *   @brief  
    *   
    *   @return
    *   @param
    */
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

    /*!
    *   @brief  Function sorts a linked List with Elements of a specified Type T 
    *           by a passed lambda-function;
    *           Used sorting algorithm is bubblesort
    * 
    *   @param  Lambda-function which contains value to sort by
    */
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

    /*!
    *   @brief  Operator [] used for an object of type LinkedList to return 
    *           pointer at element at a specified index in this list
    * 
    *   @return pointer at element at specified index in linked list
    *   @param  index   index of the list-element to return;
    *                   first element of list at index 0;
    *                   negative indizes mean counting from end of the list towards first element
    */
    T* operator[] (int index)
    {
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

            while (current->next != nullptr) // set current pointer to the last object of the list
            {
                current = current->next;
            }
            for (int i = -1; i > index; --i) // counting to index against in opposite direction
            {
                if (current != nullptr)
                {
                    current = current->previous;
                }
                else
                {
                    return nullptr;
                }
            }
        }

        return &current->data;
    }
};
