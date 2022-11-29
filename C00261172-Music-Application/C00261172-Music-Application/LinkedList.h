#pragma once
#include "LinkedListItem.h"
template<typename T>
class LinkedList
{
	LinkedListItem<T>* head = nullptr;
	LinkedListItem<T>* tail = nullptr;

public:
	void insert(T data);
	void remove(T data);
};