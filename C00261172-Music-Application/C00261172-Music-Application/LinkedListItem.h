#pragma once
template<typename T>
class LinkedListItem
{
	constructor(T data, LinkedListItem<T>* next) {
		this->data = data;
		this->next = next;
	}
private:

public:
	T data;
	LinkedListItem<T>* next;
};
