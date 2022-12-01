#include "LinkedList.h"

template<class T>
inline void LinkedList<T>::insert(T data)
{
	SingleLinkedNode<T> node = SingleLinkedNode<T>(data, this->tail);
	if (this->tail != nullptr) {
		this->tail->next = &node;
	}
	this->tail = &node;
}

template<class T>
inline T LinkedList<T>::remove(T data)
{
	if (size > 0) {
		size--;
		SingleLinkedNode<T> temp = this.head;
		this->head = temp.next;
		return temp;
	}
	return NULL;
}