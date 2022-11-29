#pragma once
#include "LinkedListItem.h"
template <class T>
class LinkedList
{
public:
	LinkedList() {

	}
	void insert(T data);
	void remove(T data);
	LinkedListItem<T> getHead() { return this->head; }
	LinkedListItem<T> getTail() { return this->tail; }
private:
	LinkedListItem<T>* head = nullptr;
	LinkedListItem<T>* tail = nullptr;
};

template<class T>
inline void LinkedList<T>::insert(T data)
{
	LinkedListItem<T> node = LinkedListItem<T>(data, this->tail);
	if (this->tail != nullptr) {
		this->tail->next = &node;
	}
	this->tail = &node;
}

template<class T>
inline void LinkedList<T>::remove(T data)
{
	LinkedListItem<T> temp = this.head;
	this->head = temp.next;
	return temp;
}
