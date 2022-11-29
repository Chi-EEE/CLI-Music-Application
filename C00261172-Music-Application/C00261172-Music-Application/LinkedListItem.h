#pragma once
template <class T>
class LinkedListItem
{
public:
	LinkedListItem(T data, LinkedListItem<T>* next) {
		this->data = data;
		this->next = next;
	}
	T data;
	LinkedListItem<T>* next;
private:

};
