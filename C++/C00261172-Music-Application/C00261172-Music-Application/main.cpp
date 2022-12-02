#include <iostream>
#include <string>
#include <memory>
#include "CircularLinkedList.h"
#include "Audio.h"
int main() {
	CircularLinkedList<Audio> songs;
	DoubleLinkedNode<Audio> audioNode = DoubleLinkedNode<Audio>
		(
			std::make_shared<DoubleLinkedNode<Audio>>(Audio(std::string("Name"), std::string("Hellos"), 1.9f, Artist())),
			std::shared_ptr<DoubleLinkedNode<Audio>>(nullptr),
			std::shared_ptr<DoubleLinkedNode<Audio>>(nullptr)
			);
	std::shared_ptr<DoubleLinkedNode<Audio>> audio = std::make_shared<DoubleLinkedNode<Audio>>(audioNode);
	songs.insert(audio);
	//songs.insert(Audio{ std::string("Name"), Artist{}, 1.9f });
	return 0;
}