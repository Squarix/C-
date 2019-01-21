using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Reflection;
using System.Threading;

namespace LP_Lab15
{
    class Program
    {
        static void Main(string[] args)
        {
            var allProc = Process.GetProcesses();
            foreach (Process process in allProc)
            {
                Console.WriteLine("-----------------");
                Console.WriteLine("Proc ID: " + process.Id);
                Console.WriteLine("Name: " + process.ProcessName);
                Console.WriteLine("Priority: " + process.BasePriority);
                Console.WriteLine("Threads amount: " + process.Threads.Count);
            }

            AppDomain currentDomain = AppDomain.CurrentDomain;
            Console.WriteLine("current domain name: " + currentDomain.FriendlyName);
            Console.WriteLine("base dir" + currentDomain.BaseDirectory);
            

            AppDomain secondDomain = AppDomain.CreateDomain("second domain");
            secondDomain.Load("Second Domain");
            AppDomain.Unload(secondDomain);

            Thread thread1 = new Thread(new ThreadStart(TestClass.PrintHW));
            Thread thread2 = new Thread(new ThreadStart(TestClass.PrintBW));
                
            thread2.Start();
            thread1.Start();

            while (thread2.IsAlive)
            {
                Console.WriteLine("thread2 is alive");
                Thread.Sleep(300);
            }
            while (thread1.IsAlive)
            {
                Console.WriteLine("thread1 is alive");
                Thread.Sleep(300);
            }
            Console.ReadKey();
        }
    }

    public class TestClass
    {
        public static void PrintHW()
        {
            int i = 30;
            while (i != 0)
            {
                Console.WriteLine("Hello world");
                i--;
                Thread.Sleep(200);
            }
        }

        public static void PrintBW()
        {
            int i = 30;
            while (i != 0)
            {
                Console.WriteLine("Bye World");
                i--;
                Thread.Sleep(200);
            }
        }
    }

}
