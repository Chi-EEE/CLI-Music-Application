AudioLibrary audioLibrary = AudioLibrary();
audioLibrary.addAudio(Audio(std::string("Epic Music"), std::string("Hellos"), 1.9f, Artist("LOL")));
auto audio = audioLibrary.getSelectedAudio();
std::cout << audio.get()->getName();
//DoubleLinkedNode<Audio> audioNode = DoubleLinkedNode<Audio>
//	(
//		std::make_shared<Audio>(std::string("Name"), std::string("Hellos"), 1.9f, Artist("LOL")),
//		std::shared_ptr<DoubleLinkedNode<Audio>>(nullptr),
//		std::shared_ptr<DoubleLinkedNode<Audio>>(nullptr)
//		);
//std::shared_ptr<DoubleLinkedNode<Audio>> audio = std::make_shared<DoubleLinkedNode<Audio>>(audioNode);
/*std::shared_ptr<Audio> audio = std::make_shared<Audio>(std::string("Name"), std::string("Hellos"), 1.9f, Artist("LOL"));

songs.insert(audio);

std::shared_ptr<DoubleLinkedNode<Audio>> node = songs.getHead();
std::cout << node.get()->data.get()->getName();*/
//songs.insert(Audio{ std::string("Name"), Artist{}, 1.9f });
