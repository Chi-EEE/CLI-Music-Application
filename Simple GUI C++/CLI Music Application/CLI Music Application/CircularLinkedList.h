#pragma once
#include <memory>
#include "DoubleLinkedNode.h"
template <class T>
class CircularLinkedList
{
public:
	void insert(std::shared_ptr<T> data);
	bool removeData(std::shared_ptr<T> data);
	std::shared_ptr<DoubleLinkedNode<T>> getHead() { return this->head; }
	std::shared_ptr<DoubleLinkedNode<T>> getTail() { return this->tail; }

	int getCount() { return this->count; }
private:
	std::shared_ptr<DoubleLinkedNode<T>> head = nullptr;
	std::shared_ptr<DoubleLinkedNode<T>> tail = nullptr;
	int count = 0;
};

template<class T>
inline void CircularLinkedList<T>::insert(std::shared_ptr<T> data)
{
	if (count == 0)
	{
		std::shared_ptr<DoubleLinkedNode<T>>node(new DoubleLinkedNode<T>(data));
		this->tail = node;
		this->head = node;
	}
	else {
		std::shared_ptr<DoubleLinkedNode<T>>node(new DoubleLinkedNode<T>(data));
		this->head->next = node;
		this->tail->prev = node;
		node->next = this->tail;
		node->prev = this->head;
		this->head = node;
	}
	this->count++;
}

template<class T>
inline bool CircularLinkedList<T>::removeData(std::shared_ptr<T> data)
{
	if (this->count > 0) {
		std::shared_ptr<DoubleLinkedNode<T>> temp = this->head;
		do {
			if (temp.get()->data == data) {
				if (this->count == 1)
				{
					this->head = nullptr;
					this->tail = nullptr;
				}
				else
				{
					temp->next->prev = temp->next;
					temp->prev->next = temp->prev;
				}
				this->count--;
				return true;
			}
		} while (temp != nullptr && temp != this->tail);
	}
	return false;
}

