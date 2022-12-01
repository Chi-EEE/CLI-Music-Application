using C00261172_Music_Application.DataStructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application.Application
{
    internal class Playlist: SelectableAudioList
    {
        public Playlist(string name) { 
            this.Name = name;
        }
        void AddMusic(Audio audio)
        {
            audioList.Insert(audio);
        }
        public string Name { get; set; }
    }
}
