#pragma once
#include "SingleLinkedNode.h"
template <class T>
class LinkedList
{
public:
	LinkedList() {

	}
	void insert(T data);
	void remove(T data);
	SingleLinkedNode<T> getHead() { return this->head; }
	SingleLinkedNode<T> getTail() { return this->tail; }
private:
	SingleLinkedNode<T>* head = nullptr;
	SingleLinkedNode<T>* tail = nullptr;
};