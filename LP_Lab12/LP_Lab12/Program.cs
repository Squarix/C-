using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace LP_Lab12
{
    public class Program
    {
        public static void Main()
        {
            Console.WriteLine("aa");
            AAA.Recursiya();
            Console.ReadKey();
        }
    }
      
    public class AAA
    {
        public static void Recursiya()
        {
            Program.Main();
        }
    }
}
