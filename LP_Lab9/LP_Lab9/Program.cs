using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LP_Lab9
{
    class Program
    {
        static void Main(string[] args)
        {
            User user   = new User();
            Admin admin = new Admin();
            Lamer lamer = new Lamer();
            user.Go += new intMod(user.Zip);
            admin.Go += new intMod(admin.Move);
            user.Run(11); // action + func + covar contr var
            admin.Run(100);
            Console.ReadKey();
        }
    }

    public delegate void intMod(int x);

    public abstract class Union
    {
        int position = 0;
        int size     = 0;
        public void Move(int length)
        {
            this.position += length;
        }

        public void Zip(int coef)
        {
            this.size /= coef;
        }

        public event intMod Go;
        public void Run(int data)
        {
            Console.WriteLine("Running");
            Go?.Invoke(data);
        }
    }

    public class User:Union
    {
        
    }

    public class Admin:Union
    {

    }

    public class Lamer:Union
    {

    }
}
