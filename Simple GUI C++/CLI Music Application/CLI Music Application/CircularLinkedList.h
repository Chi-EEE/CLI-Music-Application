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
		node->next = node;
		node->prev = node;
	}
	else {
		std::shared_ptr<DoubleLinkedNode<T>>node(new DoubleLinkedNode<T>(data));
		this->head->prev = node;
		this->tail->next = node;
		node->next = this->head;
		node->prev = this->tail;
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
					if (temp == this->tail) {
						this->tail = temp->prev;
					}
					else if (temp == this->head) {
						this->head = temp->next;
					}
					temp->next->prev = temp->prev;
					temp->prev->next = temp->next;
				}
				this->count--;
				return true;
			}
			temp = temp->next;
		} while (temp != nullptr && temp != this->head);
	}
	return false;
}

