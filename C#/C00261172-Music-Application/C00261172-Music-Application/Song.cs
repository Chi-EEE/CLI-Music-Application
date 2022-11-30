using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application
{
    internal class Song
    {
        public Song(string name, Artist artist, string description, float duration) {
            this.name = name;
            this.artist = artist;
            this.description = description;
            this.duration= duration;
        }
        public static bool operator ==(Song songLeft, Song songRight)
        {
            return songLeft.name == songRight.name && songLeft.description == songRight.description;
        }
        public static bool operator !=(Song songLeft, Song songRight)
        {
            return songLeft.name != songRight.name || songLeft.description != songRight.description;
        }
        public string name { get; set; }
        public string description { get; set; }
        public Artist artist { get; set; }
        public float duration { get; }
    }
}
