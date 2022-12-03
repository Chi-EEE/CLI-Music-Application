#include "SelectableAudioList.h"

std::shared_ptr<Audio> SelectableAudioList::getSelectedAudio()
{
	if (this->selectedAudio == nullptr) {
		this->selectedAudio = this->audioList.getHead();
		DoubleLinkedNode<Audio>* audioNode = this->selectedAudio.get();
		if (audioNode == nullptr) {
			return nullptr;
		}
		std::shared_ptr<Audio> audio = audioNode->data;
		return audio;
	}
	return nullptr;
}

std::shared_ptr<Audio> SelectableAudioList::getNextSelectedAudio()
{
	if (this->selectedAudio == nullptr) {
		this->selectedAudio = this->audioList.getHead();
		return this->selectedAudio.get()->data;
	}
	this->selectedAudio = this->selectedAudio.get()->next;
	DoubleLinkedNode<Audio>* audioNode = this->selectedAudio.get();
	if (audioNode == nullptr) {
		return nullptr;
	}
	std::shared_ptr<Audio> audio = audioNode->data;
	return audio;
}

std::shared_ptr<Audio> SelectableAudioList::removeSelectedAudio()
{
	return std::shared_ptr<Audio>();
}
