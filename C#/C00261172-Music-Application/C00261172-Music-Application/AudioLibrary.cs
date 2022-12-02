using C00261172_Music_Application.DataStructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application.Application
{
    internal class AudioLibrary: SelectableAudioList
    {
        public void AddMusic(Audio audio)
        {
            AudioList.Insert(audio);
        }
        public CircularLinkedList<Audio> getShuffledMusicList()
        {
            throw new NotImplementedException();
        }
    }
}
