#pragma once

#include <functional>


/*!
 * @brief Template struct LinkedListComponent can store data of any type T and pointers to a previous and following
 * element as to be used by the LinkedList class.
 *
 * @tparam T type of the stored data
 */
template <typename T>
struct LinkedListComponent
{
    /*!
     * @brief Data that is stored in this component of the LinkedList
     */
	T data;

	/*!
	 * @brief Pointer to the next element in the LinkedList
	 */
	LinkedListComponent* next = nullptr;

    /*!
     * @brief Pointer to the previous element in the LinkedList
     */
	LinkedListComponent* previous = nullptr;
};


/*!
 * @brief Template class LinkedList can handle, create and sort double linked lists with Elements of any type T.
 *
 * @tparam T type of the stored data
 */
template <typename T>
class LinkedList
{

private:

    /*! 
     * @brief Pointer to first component of the double linked list. nullptr if linked list is empty
     */
	LinkedListComponent<T>* m_FirstElement = nullptr;
	
	
public:

    /*!
     * @brief Destructor deletes every LinkedListComponent in the linked list.
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
     * @brief Adds data of the specified type T to the end of the linked list in a new LinkedListComponent.
     *
     * @param element element that will be added (by copy) to the linked list
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
     * @brief Iterates through the linked list and executes the given given lambda-function for each element in the
     * linked list.
     *
     * @param function lambda-function that will be executed with every element of the linked list
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
     * @brief Finds the first element for which a given lambda-function returns true. Returns pointer to the stored data
     * of the element.
     *
     * @param filter lambda-function which compares data from a list-element with a search-value and returns true if
     * both are equal
     * @return pointer to the data of the first element for which filter returned true
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
     * @brief Sorts the linked list using Bubble Sort. The sort key for a given element of type T will be determined by
     * the provided lambda-function.
     *
     * @param getSortValue lambda-function which return the sort key for a given element of type T
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
     * @brief [index] returns a pointer to the data T stored in the linked list at position index. A negative index is
     * allowed. Here, the linked list will be searched trough from the end.
     *
     * @param index index of the element to return starting at 0, negative index will lead to a count from the end of
     * the list (Python-like behaviour)
     * @return pointer to the data at the specified index in the linked list. nullptr if index is out-of-bounds
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
            for (int i = -1; i > index; --i) // counting to index in opposite direction
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
