#include "AudioList.h"

/// <summary>
/// Searches through the audioList and finds if the audioName matches the audio's name
/// Returns the matched audio
/// </summary>
/// <param name="audioName"></param>
/// <returns></returns>
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
		} while (temp != nullptr && temp != audioList.getHead());
	}
	return nullptr;
}

/// <summary>
/// Add audio to the audioList
/// </summary>
/// <param name="audio"></param>
/// <returns></returns>
bool AudioList::insertAudio(std::shared_ptr<Audio> audio)
{
	if (getAudioByName(audio->getName()) == nullptr) {
		this->audioList.insert(audio);
		return true;
	}
	return false;
}

/// <summary>
/// Removes the audio from the audioList
/// </summary>
/// <param name="audio"></param>
/// <returns></returns>
bool AudioList::removeAudio(std::shared_ptr<Audio> audio)
{
	return audioList.removeData(audio);
}

/// <summary>
/// Goes through the audioList and plays the next audio
/// It asks the user whether to continue after the audio has completed playing
/// </summary>
void AudioList::playAllAudio()
{
	if (getAudioCount() > 0) {
		bool continuePlaying = false;
		auto temp = this->audioList.getHead();
		do
		{
			temp->data->play();
			temp = temp->next;
			while (true) {
				std::cout << "Do you want to continue playing audio from this list?";
				std::cin >> continuePlaying;
				if (!std::cin.fail()) {
					break;
				}
				std::cout << "\nError: 0 or 1";
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
		} while (continuePlaying);
	}
}

/// <summary>
/// Removes the audio which matches the audioName
/// </summary>
/// <param name="audioName"></param>
/// <returns></returns>
bool AudioList::removeAudioByName(std::string audioName)
{
	auto audio = getAudioByName(audioName);
	if (audio) {
		return audioList.removeData(audio);
	}
	return false;
}

/// <summary>
/// Returns a string with a list of the audio names
/// </summary>
/// <returns></returns>
std::string AudioList::getAllAudio()
{
	std::string result = "";
	if (getAudioCount() > 0)
	{
		auto temp = this->audioList.getHead();
		do {
			result += "||" + temp->data->getName();
			temp = temp->next;
		} while (temp != nullptr && temp != this->audioList.getHead());
		result += "||";
	}
	result += "\n\n";
	return result;
}