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
            bool yes = false;
            while (true)
            {
                if (Changed)
                {
                    Changed = false;
                    BuildScreen();
                    Console.WriteLine(question);
                    Console.Write("[");
                    if (yes)
                    {
                        Console.Write("N");
                        Console.Write(" | ");
                        Console.ForegroundColor = ConsoleColor.Cyan;
                        Console.Write("Y");
                        ResetConsoleColor();
                    }
                    else
                    {
                        Console.ForegroundColor = ConsoleColor.Cyan;
                        Console.Write("N");
                        ResetConsoleColor();
                        Console.Write(" | ");
                        Console.Write("Y");
                    }
                    Console.Write("]");
                }
                ConsoleKeyInfo cki = Console.ReadKey();
                switch (cki.Key)
                {
                    case ConsoleKey.LeftArrow:
                        if (yes)
                        {
                            Changed = true;
                            yes = false;
                        }
                        break;
                    case ConsoleKey.RightArrow:
                        if (!yes)
                        {
                            Changed = true;
                            yes = true;
                        }
                        break;
                    case ConsoleKey.Enter:
                        return yes;
                    default:
                        Console.Write("\b \b");
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
            Console.Write(LINE);
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
            Console.Write(LINE);
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
                    default:
                        Console.Write("\b \b");
                        break;
                }
            }
        }
        static void Main(string[] args)
        {
            Run();
        }
        private static readonly AudioLibrary AudioLibrary = new();
        private static bool Changed = true;
        private const string LINE = "=======================================================================================================================\n";
    }
}