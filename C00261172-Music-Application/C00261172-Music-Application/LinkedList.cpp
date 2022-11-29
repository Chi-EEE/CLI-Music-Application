#include "LinkedList.h"
template<typename T>
inline void LinkedList<T>::insert(T data)
{
	LinkedListItem<T> node = LinkedListItem<T>(data, this->tail);
	this->tail->next = node;
	this->tail = node;
}
template<typename T>
inline void LinkedList<T>::remove(T data)
{
	LinkedListItem<T> temp = this.head;
	this->head = temp.next;
	return temp;
}