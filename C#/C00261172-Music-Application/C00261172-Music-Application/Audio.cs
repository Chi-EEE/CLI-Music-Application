using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application.Application
{
    internal class Audio
    {
        public Audio(string name, string description, int duration, Artist? artist) {
            this.Name = name;
            this.Description = description;
            this.Duration= duration;
            this.Artist = artist;
        }
        public static bool operator ==(Audio audioLeft, Audio audioRight)
        {
            if (ReferenceEquals(audioLeft, audioRight)) return true;

            if (ReferenceEquals(audioLeft, null) || ReferenceEquals(audioRight, null)) return false;

            return audioLeft.Name == audioRight.Name && audioLeft.Description == audioRight.Description;
        }
        public static bool operator !=(Audio audioLeft, Audio audioRight)
        {
            return !(audioLeft == audioRight);
        }
        public string Name { get; set; }
        public string Description { get; set; }
        public int Duration { get; }
        public Artist? Artist { get; set; }
    }
}
