using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LP_Lab5
{
    class Program
    {
        static void Main(string[] args)
        {
            Soft word = new Word();
            word.LoadProcess();

            Virus virus = new Virus();
            virus.FabricateElection("USA");
            virus.HackPentagon();

            Bomber bomber = new Bomber();
            bomber.LoadProcess();

            Printer printer = new Printer();
            printer.iAmPrinting(bomber);
            printer.iAmPrinting(word);

            if (word is Soft)
            {
                Console.WriteLine($"{word} is Soft");
            }

            if (word is Word)
            {
                Console.WriteLine($"{word} is Word");
            }

            if (word as Soft != null)
            {
                Console.WriteLine($"{word} as Soft");
            }

            if (word as Bomber != null)
            {
                Console.WriteLine($"{word} as Bomber");
            }

            Soft[] softArray = new Soft[] {new Word(), new Bomber(), new Virus() };
            Computer_Controller controller = new Computer_Controller(softArray);
            controller.PrintSoft();

            Console.ReadLine();
        }

        partial class PartialClass
        {
            int partialField2;
        }
    }
}
