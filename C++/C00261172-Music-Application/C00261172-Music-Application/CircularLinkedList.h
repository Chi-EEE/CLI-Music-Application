#pragma once
#include <memory>
#include <iterator>
#include <cstddef>
#include "DoubleLinkedNode.h"
template <class T>
class CircularLinkedList
{
public:
	CircularLinkedList() {

	}
	CircularLinkedList(CircularLinkedList<T>* circularLinkedList) {
		DoubleLinkedNode<T>* temp = circularLinkedList->getHead().get();
		while (temp != nullptr) {
			this->insert(temp->data);
			temp = temp->next.get();
		}
	}
	~CircularLinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
	}

	void insert(T data);
	T removeTail();
	T removeHead();
	std::shared_ptr<DoubleLinkedNode<T>> getHead() { return this->head; }
	std::shared_ptr<DoubleLinkedNode<T>> getTail() { return this->tail; }

	int getSize() { return this->size; }
private:
	std::shared_ptr<DoubleLinkedNode<T>> head = nullptr;
	std::shared_ptr<DoubleLinkedNode<T>> tail = nullptr;
	int size = 0;
};

template<class T>
inline void CircularLinkedList<T>::insert(T data)
{
	std::shared_ptr<DoubleLinkedNode<T>>node(new DoubleLinkedNode<T>(data, this->tail, this->head));
	if (this->tail != nullptr) {
		this->tail->next = node;
	}
	if (this->head == nullptr) {
		this->head = node;
	}
	this->tail = node;
	this->size++;
}

template<class T>
inline T CircularLinkedList<T>::removeTail()
{
	if (this->size <= 0) {
		DoubleLinkedNode<T>* previousTail = this->tail.get();
		if (previousTail != nullptr) {
			this->size--;
			if (previousTail->prev != nullptr) {
				previousTail->prev->next = previousTail->next;
			}
			if (previousTail->next != nullptr) {
				previousTail->next->prev = previousTail->prev;
			}
			this->tail = previousTail->prev;
			return previousTail->data;
		}
	}
	return NULL;
}

template<class T>
inline T CircularLinkedList<T>::removeHead()
{
	if (this->size <= 0) {
		DoubleLinkedNode<T>* previousHead = this->head.get();
		if (previousHead != nullptr) {
			this->size--;
			if (previousHead->prev != nullptr) {
				previousHead->prev->next = previousHead->next;
			}
			if (previousHead->next != nullptr) {
				previousHead->next->prev = previousHead->prev;
			}
			this->head = previousHead->next;
			return previousHead->data;
		}
	}
	return NULL;
}
