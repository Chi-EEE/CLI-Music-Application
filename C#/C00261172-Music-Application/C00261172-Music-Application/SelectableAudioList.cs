using C00261172_Music_Application.Application;
using C00261172_Music_Application.DataStructure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application
{
    internal class SelectableAudioList
    {
        public Audio? GetSelectedAudio()
        {
            if (this.SelectedAudio == null)
            {
                this.SelectedAudio = this.audioList.Head;
            }
            return this.SelectedAudio?.Data;
        }
        public Audio? getNextMusic()
        {
            if (this.SelectedAudio == null)
            {
                this.SelectedAudio = this.audioList.Head;
                return this.SelectedAudio?.Data;
            }
            this.SelectedAudio = this.SelectedAudio.Next;
            return this.SelectedAudio.Data;
        }
        public bool RemoveSelectedMusic()
        {
            return audioList.RemoveData(GetSelectedAudio());
        }
        private DoubleLinkedNode<Audio>? SelectedAudio { get; set; }
        protected CircularLinkedList<Audio> audioList = new();
    }
}
