using C00261172_Music_Application.DataStructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application.Application
{
    internal class Playlist
    {
        public Playlist(string name) { 
            this.Name = name;
        }
        void insert(Song song)
        {
            Songs.insert(song);
        }
        void removeSelectedSong()
        {

        }
        Song? getSelectedSong()
        {
            if (this.SelectedSong == null)
            {
                this.SelectedSong = this.Songs.head;
            }
            return this.SelectedSong?.Data;
        }
        Song? getNextSong()
        {
            if (this.SelectedSong == null)
            {
                this.SelectedSong = this.Songs.head;
                return this.SelectedSong?.Data;
            }
            this.SelectedSong = this.SelectedSong.Next;
            return this.SelectedSong.Data;
        }
        public string Name { get; set; }
        private DoubleLinkedNode<Song>? SelectedSong { get; set; }
        CircularLinkedList<Song> Songs = new();
    }
}
