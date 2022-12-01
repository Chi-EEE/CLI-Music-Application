using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading.Channels;

namespace C00261172_Music_Application.Application
{
    internal class Program
    {
        static bool YesOrNo(string question)
        {
            Changed = true;
            while (true)
            {
                BuildScreen();
                Console.WriteLine(question);
                Console.WriteLine("[Y | N]");
                string input = Console.ReadLine();
                switch (input)
                {
                    case "Y":
                        return true;
                    case "N":
                        return false;
                    default:
                        break;
                }
            }
        }
        private static int EnterConsoleInt(string statement)
        {
            Changed = true;
            while (true)
            {
                BuildScreen();
                Console.WriteLine(statement);
                try
                {
                    string intString = Console.ReadLine()!;
                    return int.Parse(intString);
                }
                catch (Exception _)
                {
                    Console.Write("Please enter a valid number.");
                    Console.ReadKey();
                }
            }
        }
        private static string EnterConsoleString(string statement)
        {
            Changed = true;
            while (true)
            {
                BuildScreen();
                Console.WriteLine(statement);
                try
                {
                    string input = Console.ReadLine()!;
                    return input;
                }
                catch (Exception _)
                {
                    Console.Write("Please enter a valid text.");
                    Console.ReadKey();
                }
            }
        }
        private static void DisplayAudioDetails(Audio audio, int index)
        {
            Console.ForegroundColor = ConsoleColor.Blue;
            bool selected = audio == AudioLibrary.GetSelectedAudio();
            if (selected)
            {
                Console.Write("▼ ");
            }
            else
            {
                Console.Write("▶ ");
            }
            Console.WriteLine("[" + index + "] Audio Name: " + audio.Name);
            ResetConsoleColor();
            if (selected)
            {
                if (audio.Artist != null)
                {
                    Console.WriteLine("  Artist Name: " + audio.Artist.Name);
                }
                Console.WriteLine("  Duration: " + audio.Duration);
                Console.WriteLine("  Description: \n   -" + audio.Description);
            }
        }
        private static void BuildScreen()
        {
            Console.Clear();
            Console.WriteLine("My Audio Files: ");
            Console.WriteLine(new string('=', Console.WindowWidth));
            Audio firstSelectedAudio = AudioLibrary.GetSelectedAudio();
            Audio selectedAudio = firstSelectedAudio;
            int index = 1;
            do
            {
                if (selectedAudio == null)
                {
                    Console.WriteLine("  [No Audio found]");
                    break;
                }
                DisplayAudioDetails(selectedAudio, index);
                selectedAudio = AudioLibrary.getNextMusic();
            } while (firstSelectedAudio != selectedAudio);
            Console.WriteLine(new string('=', Console.WindowWidth));
        }
        private static void ResetConsoleColor()
        {
            Console.ForegroundColor = ConsoleColor.White;
        }
        private static Dictionary<string, Delegate> MenuOptions = new()
        {
            { "Add Audio", AddAudio },
            { "Remove Audio", RemoveAudio }
        };
        private static void BuildMenu(int selectedOption)
        {
            for (int i = 0; i < MenuOptions.Count; i++)
            {
                if (i == selectedOption)
                {
                    Console.ForegroundColor = ConsoleColor.Cyan;
                    Console.Write("-> ");
                    ResetConsoleColor();
                }
                Console.WriteLine("[" + i + "] " + MenuOptions.ElementAt(i).Key);
            }
        }
        private static void AddAudio()
        {
            bool addAudio = YesOrNo("Would you like to add a Audio file?");
            if (addAudio)
            {
                string name = EnterConsoleString("Please enter the Audio's Name:");

                string description = EnterConsoleString("Please enter the Audio's Description:");

                int duration = EnterConsoleInt("Please enter the Audio's Duration:");

                bool addArtist = YesOrNo("Do you want to add an Artist to this Audio?:");

                Artist? artist = null;
                if (addArtist)
                {
                    string artistName = EnterConsoleString("Please enter the Artist's Name:");
                    artist = new(artistName);
                }
                Audio newAudio = new(name, description, duration, artist);
                AudioLibrary.AddMusic(newAudio);
                BuildScreen();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("- Audio Created: " + newAudio.Name);
                ResetConsoleColor();
                Console.ReadKey();
                Changed = true;
            }
        }
        private static void RemoveAudio()
        {
            bool removeAudio = YesOrNo("Would you like to remove a Audio file?");
            if (removeAudio)
            {
            }
        }
        private static void Run()
        {
            int selectedOption = 0;
            while (true)
            {
                if (Changed)
                {
                    Changed = false;
                    BuildScreen();
                    BuildMenu(selectedOption);
                }
                else
                {
                    //Console.Write("\b \b");
                }
                ConsoleKeyInfo cki = Console.ReadKey();
                switch (cki.Key)
                {
                    case ConsoleKey.UpArrow:
                        if (selectedOption > 0)
                        {
                            Changed = true;
                            selectedOption--;
                        }
                        break;
                    case ConsoleKey.DownArrow:
                        if (selectedOption < MenuOptions.Count - 1)
                        {
                            Changed = true;
                            selectedOption++;
                        }
                        break;
                    case ConsoleKey.Enter:
                        MenuOptions.ElementAt(selectedOption).Value.DynamicInvoke();
                        break;
                }
            }
        }
        const int MF_BYCOMMAND = 0x00000000;
        const int SC_MINIMIZE = 0xF020;
        const int SC_MAXIMIZE = 0xF030;
        const int SC_SIZE = 0xF000;
        [DllImport("user32.dll")]
        public static extern int DeleteMenu(IntPtr hMenu, int nPosition, int wFlags);
        [DllImport("user32.dll")]
        private static extern IntPtr GetSystemMenu(IntPtr hWnd, bool bRevert);
        [DllImport("kernel32.dll", ExactSpelling = true)]
        private static extern IntPtr GetConsoleWindow();
        static void Main(string[] args)
        {
            DeleteMenu(GetSystemMenu(GetConsoleWindow(), false), SC_MINIMIZE, MF_BYCOMMAND);
            DeleteMenu(GetSystemMenu(GetConsoleWindow(), false), SC_MAXIMIZE, MF_BYCOMMAND);
            DeleteMenu(GetSystemMenu(GetConsoleWindow(), false), SC_SIZE, MF_BYCOMMAND);
            Run();
        }
        private static readonly AudioLibrary AudioLibrary = new();
        private static bool Changed = true;
    }
}