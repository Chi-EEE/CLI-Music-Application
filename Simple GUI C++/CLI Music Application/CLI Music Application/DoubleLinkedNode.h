/// <summary>
/// Name: Chi Huu Huynh
/// Date: 06/12/2022
/// </summary>
#pragma once
template <class T>
class DoubleLinkedNode
{
public:
	DoubleLinkedNode(std::shared_ptr<T> data) {
		this->data = data;
	}
	std::shared_ptr <T> data;
	std::shared_ptr<DoubleLinkedNode<T>> prev = nullptr;
	std::shared_ptr<DoubleLinkedNode<T>> next = nullptr;
private:

};
