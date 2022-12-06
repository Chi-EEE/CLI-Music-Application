#include "AudioList.h"

std::shared_ptr<Audio> AudioList::getAudioByName(std::string audioName)
{
	if (getAudioCount() > 0) {
		auto temp = audioList.getHead();
		do
		{
			if (audioName == temp->data->getName()) {
				return temp->data;
			}
			temp = temp->next;
		} while (temp != nullptr && temp != audioList.getTail());
	}
	return nullptr;
}

bool AudioList::removeAudio(std::shared_ptr<Audio> audio)
{
	return audioList.removeData(audio);
}

//std::shared_ptr<Audio> AudioList::getSelectedAudio()
//{
//	if (this->selectedAudio == nullptr) {
//		this->selectedAudio = this->audioList.getHead();
//		DoubleLinkedNode<Audio>* audioNode = this->selectedAudio.get();
//		if (audioNode == nullptr) {
//			return nullptr;
//		}
//		std::shared_ptr<Audio> audio = audioNode->data;
//		return audio;
//	}
//	return this->selectedAudio.get()->data;
//}
//
//std::shared_ptr<Audio> AudioList::getNextSelectedAudio()
//{
//	this->selectedAudio = this->selectedAudio.get()->next;
//	DoubleLinkedNode<Audio>* audioNode = this->selectedAudio.get();
//	if (audioNode == nullptr) {
//		return nullptr;
//	}
//	std::shared_ptr<Audio> audio = audioNode->data;
//	return audio;
//}
//
//bool AudioList::removeSelectedAudio()
//{
//	if (this->selectedAudio == nullptr) {
//		return false;
//	}
//	return this->audioList.removeData(this->selectedAudio->data);
//}
