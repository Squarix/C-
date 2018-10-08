using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using VectorNS;

namespace LP_Lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            Vector Vec = new Vector(2, "Hellowe, readonly");
            Vector Vec2 = new Vector(0, "Hellowe, readonly");
            Vector[] VecArray = new Vector[2];

            Nikitosik first = new ThreeChetiri();
            Nikitosik second = new TwoChetiri();
            VecArray[0] = Vec;
            VecArray[1] = Vec2;
            foreach (Vector value in VecArray)
            {
                if (value.data[0] == 0)
                {
                    Console.WriteLine($"{value}");
                }
            }
            Console.WriteLine($" readonly: {Vec.getString}  ");
            Vec[1] = 55;
            Console.ReadLine();
            int count = 10;
            count = StaticMath.Calculate(count);
        }
    }
}

namespace VectorNS
{
    class Vector
    {
        private int   accessKey;
        private int   status;
        private int   amount;
        public  int[] data = new int[5];

        readonly string readOnly;
        const int constValue  = 12;
            
        public Vector()
        {
            data[0]  = 0;
            data[1]  = 2;
            readOnly = "Hellowe, this string is ReadOnly";
        }

        private Vector(string value)
        {
            readOnly  = value;
            data[0]   = 0;
            accessKey = 1133;
        }
        static Vector()
        { Console.WriteLine("Egagai !00"); }
        public Vector PrivateConstruct(string value)
        {
            Vector VectorClass = new Vector(value);
            return VectorClass;
        }

        public Vector(int value, string strValue):this(strValue)
        {
            data[0] = value;
        }

        public void OutRef(out int hellowe, ref int goodbye)
        {
            hellowe = 18;
            goodbye += 4;
        }

        public int this[int index]
        {
            get
            {
                return data[index];
            }
            set
            {
                Console.WriteLine("Enter access key (1133): ");
                int key = int.Parse(Console.ReadLine());
                if (key == this.accessKey)
                {
                    Console.WriteLine("Success!");
                    data[index] = value;
                }
            }
        }
        
        public string getString
        {
            get
            {
                return readOnly;
            }
            set { }
        }

    }
        
    static class StaticMath
    {
        public static int Calculate(int first)
        {
            first++;
            return first;
        }
    }

    interface Nikitosik
    {
        void Stasyan(int alesha);
    }


    class ThreeChetiri : Nikitosik
    {
        public void Stasyan(int alesha)
        {
            bool flag = (alesha>0) ? true : false;
        }
    }

    class TwoChetiri: Nikitosik
    {
        public void Stasyan(int kek)
        {
            bool flag = (kek > 100) ? true : false;
        }
    }

    public partial class Employee
    {
        public void DoWork()
        {
        }
    }

    public partial class Employee
    {
        public void GoToLunch()
        {
        }
    }

    class Equals
    {
        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        public override string ToString()
        {
            return base.ToString();
        }
    }
}  