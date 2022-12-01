using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application.Application
{
    internal class Artist
    {
        public Artist(string name) {
            this.Name = name;
        }
        public static bool operator ==(Artist artistLeft, Artist artistRight)
        {
            if (ReferenceEquals(artistLeft, artistRight)) return true;

            if (ReferenceEquals(artistLeft, null) || ReferenceEquals(artistRight, null)) return false;

            return artistLeft.Name == artistRight.Name;
        }
        public static bool operator !=(Artist artistLeft, Artist artistRight)
        {
            return !(artistLeft == artistRight);
        }
        public string Name { get; set; }
    }
}
