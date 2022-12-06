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
	return this->selectedAudio.get()->data;
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

bool SelectableAudioList::removeSelectedAudio()
{
	if (this->selectedAudio == nullptr) {
		return false;
	}
	return this->audioList.removeData(this->selectedAudio->data);
}
