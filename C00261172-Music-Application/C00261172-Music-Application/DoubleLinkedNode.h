#pragma once
template <class T>
class DoubleLinkedNode
{
public:
	DoubleLinkedNode(T data, std::shared_ptr<DoubleLinkedNode<T>> prev, std::shared_ptr<DoubleLinkedNode<T>> next) {
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
	T data;
	std::shared_ptr<DoubleLinkedNode<T>> prev;
	std::shared_ptr<DoubleLinkedNode<T>> next;
private:

};
