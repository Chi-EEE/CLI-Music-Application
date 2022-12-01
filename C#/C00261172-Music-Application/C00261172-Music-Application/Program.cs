using System.Diagnostics;

namespace C00261172_Music_Application.Application
{
    internal class Program
    {
        static bool YesOrNo(string question)
        {
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
            bool selected = audio == audioLibrary.GetSelectedAudio();
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
                Console.WriteLine("  Description: \n -" + audio.Description);
            }
        }
        private static void BuildScreen()
        {
            Console.Clear();
            Console.WriteLine("My Audio Files: ");
            Console.WriteLine(new string('=', Console.WindowWidth));
            Audio firstSelectedAudio = audioLibrary.GetSelectedAudio();
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
                selectedAudio = audioLibrary.getNextMusic();
            } while (firstSelectedAudio != selectedAudio);
            Console.WriteLine(new string('=', Console.WindowWidth));
        }
        private static void ResetConsoleColor()
        {
            Console.ForegroundColor = ConsoleColor.White;
        }
        private static Dictionary<string, Delegate> menuOptions = new()
        {
            { "Add Audio", AddAudio }
        };
        private static void BuildMenu(int selectedOption)
        {
            for (int i = 0; i < menuOptions.Count; i++)
            {
                if (i == selectedOption)
                {
                    Console.ForegroundColor = ConsoleColor.Cyan;
                    Console.Write("->");
                    ResetConsoleColor();
                }
                Console.WriteLine("[" + i + "] " + menuOptions.ElementAt(i).Key);
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
                Audio newAudio = new Audio(name, description, duration, artist);
                audioLibrary.AddMusic(newAudio);
                BuildScreen();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine("- Audio Created: " + newAudio.Name);
                ResetConsoleColor();
                Console.ReadKey();
            }
        }
        private static void Run()
        {
            int selectedOption = 0;
            while (true)
            {
                BuildScreen();
                ConsoleKeyInfo cki = Console.ReadKey();
                switch (cki.Key)
                {
                    case ConsoleKey.DownArrow:
                        selectedOption -= 1 % menuOptions.Count;
                        break;
                    case ConsoleKey.UpArrow:
                        selectedOption += 1 % menuOptions.Count;
                        break;
                }
                BuildMenu(selectedOption);
            }
        }
        static void Main(string[] args)
        {
            Run();
        }
        private static AudioLibrary audioLibrary = new();
    }
}