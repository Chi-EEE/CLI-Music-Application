#include "MusicLibrary.h"
#include <random>

CircularLinkedList<Song> MusicLibrary::getShuffledSongList()
{
    /*CircularLinkedList<Song> shuffledList(this->songs);
    std::random_device rd;
    std::mt19937 generator(rd());*/
    //std::shuffle(shuffledList.begin(), shuffledList.end(), generator);
    return CircularLinkedList<Song>();
}
