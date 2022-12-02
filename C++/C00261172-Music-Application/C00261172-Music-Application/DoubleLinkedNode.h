#pragma once
template <class T>
class DoubleLinkedNode
{
public:
	DoubleLinkedNode(std::shared_ptr<DoubleLinkedNode<T>> data, std::shared_ptr<DoubleLinkedNode<T>> prev, std::shared_ptr<DoubleLinkedNode<T>> next) {
		this->data = data.get()->data;
		this->prev = prev;
		this->next = next;
	}
	std::shared_ptr <T> data;
	std::shared_ptr<DoubleLinkedNode<T>> prev;
	std::shared_ptr<DoubleLinkedNode<T>> next;
private:

};
