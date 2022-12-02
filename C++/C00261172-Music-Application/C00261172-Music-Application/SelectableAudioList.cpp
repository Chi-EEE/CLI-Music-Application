#include "SelectableAudioList.h"

std::shared_ptr<Audio> SelectableAudioList::getSelectedAudio()
{
    if (this->selectedAudio == nullptr) {
        this->selectedAudio = this->audioList.getHead();
        return this->selectedAudio.get()->data;
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
    return this->selectedAudio.get()->data;
}

std::shared_ptr<Audio> SelectableAudioList::removeSelectedAudio()
{
    return std::shared_ptr<Audio>();
}
