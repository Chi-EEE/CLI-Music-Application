#include <random>
#include "MusicLibrary.h"
#include "RandomNumberGenerator.h"
CircularLinkedList<Song> MusicLibrary::getShuffledSongList()
{
    int linkedListSize1 = this->songs.getSize();
    if (linkedListSize1 <= 1) {
        return this->songs;
    }
    int linkedListSize2 = linkedListSize1 / 2;
    CircularLinkedList<Song> l1, l2;
    DoubleLinkedNode<Song> tempSong1 = *(this->songs.getHead().get());
    DoubleLinkedNode<Song> tempSong2 = *(this->songs.getTail().get());
    do {
        l1.insert(tempSong1.data);
        l2.insert(tempSong2.data);
        tempSong1 = tempSong1->next();
        tempSong2 = *(tempSong2->next());
    } while (tempSong1 != tempSong2);
    /*for (int i = this->songs.getSize() - 1; i >= 1; i--) {
        RandomNumberGenerator::getInstance().getNumberFromRange(i, this->songs.getSize());
    }*/
    return CircularLinkedList<Song>();
}
