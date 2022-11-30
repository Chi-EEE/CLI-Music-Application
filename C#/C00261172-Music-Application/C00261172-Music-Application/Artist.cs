using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application
{
    internal class Artist
    {
        public Artist(string name) {
            this.name = name;
        }
        public static bool operator ==(Artist artistLeft, Artist artistRight)
        {
            return artistLeft.name == artistRight.name;
        }
        public static bool operator !=(Artist artistLeft, Artist artistRight)
        {
            return artistLeft.name != artistRight.name;
        }
        public string name { get; set; }
    }
}
