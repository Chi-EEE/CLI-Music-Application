#pragma once
template <class T>
class SingleLinkedNode
{
public:
	SingleLinkedNode(T data, SingleLinkedNode<T>* next) {
		this->data = data;
		this->next = next;
	}
	T data;
	SingleLinkedNode<T>* next;
private:

};
