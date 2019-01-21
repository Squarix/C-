using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace КР2
{
    class Program
    {
        static void Main(string[] args)
        {   
            SuperHashSet<User> hashSet = new SuperHashSet<User>();
            hashSet.Add(new User("XYJ7uraH4iK"));
            hashSet.Add(new User("BaBKa_v_kEDaX")); 
            hashSet.Show();


            hashSet.CountEqual(new User("BaBKa_v_kEDaX"));

            Button b1 = new Button("Submit button");
            Button b2 = new Button("Delete button");
            User user = new User("FapToBuY");
            user.Click += b2.OnClick;
            user.Click += b1.OnClick;
            user.CommandClick();
            Console.ReadKey();
        }
    }

    class SuperHashSet<T> where T : class
    {
        private HashSet<T> hashSet = new HashSet<T>();

        public void Add(T obj)
        {
            hashSet.Add(obj);
        }

        public void Show()
        {
            foreach (var n in hashSet)
            {
                Console.WriteLine("----------");
                Console.WriteLine(n.ToString());
                Console.WriteLine("----------");
            }
        }

        public void CountEqual(T obj)
        {
            foreach (var n in hashSet.Where(n => n.Equals(obj)).Select(n => n))
            {
                Console.WriteLine(n.ToString());
            }
            int count = hashSet.Where(n => n.Equals(obj)).Select(n => n).Count();
            Console.WriteLine($"Obj amount: {count}");
        }

    }

    class User
    {
        private string name;
        public event EventHandler Click;
        public string Name { get; }
        public User(string name)
        {
            this.name = name;
        }

        public override string ToString()
        {
            return $"User: {this.name}";
        }

        public void CommandClick()
        {
            Console.WriteLine($"{this.name} pushed the button");
            Click?.Invoke(this, null);
        }

        public override bool Equals(object obj)
        {
            if (this.GetHashCode() == obj.GetHashCode())
            {
                return true;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return name.GetHashCode();
        }
    }

    class Button
    {
        private string nameOfButton;
        public Button(string nameOfButton)
        {
            this.nameOfButton = nameOfButton;
        }

        public void OnClick(object sender, EventArgs e)
        {

            Console.WriteLine("\n***************************************");
            Console.WriteLine("Notification:");
            Console.WriteLine($"Button {this.nameOfButton} was pushed.");
            Console.WriteLine("***************************************");

        }

    }
}
