using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Runtime.CompilerServices;

namespace LP_Lab10
{
    class Program
    {
        static void Main(string[] args)
        {
            Random rand = new Random();
            ArrayList ArrayList = new ArrayList();
            for (short i = 0; i < 5; i++)
                ArrayList.Add(rand.Next());
            ArrayList.Add("Строка (a.k.a string)");
            ArrayList.Add(new Student());
            ArrayList.RemoveAt(1);
            foreach (Object value in ArrayList)
                Console.WriteLine(value);
            Console.WriteLine(ArrayList.Count);
            Console.WriteLine(ArrayList.IndexOf("Строка (a.k.a string)"));

            Stack<char> stack = new Stack<char>();
            stack.Push('a');
            stack.Push('b');
            stack.Push('c');
            stack.Push('d');
            stack.Push('e');
            stack.Push('f');

            foreach (char value in stack)
                Console.WriteLine(value);

  //          (int ded, string ded1, bol ded2) ded3 = (1, "2", true);
            stack.Pop();
            stack.Pop();

            Console.WriteLine("New array");

            List<char> list = new List<char>();
            foreach (char value in stack) {
                list.Add(value);
                Console.WriteLine(value);
            }
            list.Insert(3, 'z');
            list.Capacity = 22;
            Console.WriteLine(list.Contains('d'));
            ObservableCollection<int> observable = new ObservableCollection<int> {1,2,3,4,5,6};
            observable.CollectionChanged += CollectionChanged;
            observable.Add(7);
            observable.Remove(4);


            Console.ReadKey();
        }

        private static void CollectionChanged(Object obj, NotifyCollectionChangedEventArgs e)
        {
            Console.WriteLine("Коллекция изменилась!");
        }
    }

    public class Student
    {

    }
}
