using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LP_Lab11
{
    public class Vector : IEnumerable<Vector> , IComparable<Vector>
    {
        public int value;
        public Vector(int value)
        {
            this.value = value;
        }

        public int CompareTo(Vector other)
        {
            if (this.value > other.value)
                return 1;
            else if (this.value == other.value)
                return -1;
            else
                return 0;
        }

        public IEnumerator<Vector> GetEnumerator()
        {
            return this.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return this.GetEnumerator();
        }
  

    }
    class Program
    {

        static void Main(string[] args)
        {
            string[] stringArray = new string[12] { "January", "February", "March",
                                                    "April", "May", "June",
                                                    "July", "August", "September",
                                                    "October", "November", "December" };
            IEnumerable<string> result1 = stringArray.Where(n=> n.Length < 6)
                                                     .Select(n => n);
            
            IEnumerable<string> result2 = stringArray.OrderBy(n=>n);
            IEnumerable<string> result3 = stringArray.Where(n => n.IndexOf('u') != 0 && n.Length > 4);
            foreach (string value in result2)
                Console.WriteLine(value);
            foreach (string value in result1)
                Console.WriteLine(value);
            foreach (string value in result3)
                Console.WriteLine(value);

            List<Vector> VecList = new List<Vector>();
            for (int i = 0; i < 11; i++)
                VecList.Add(new Vector(i));

            IEnumerable<Vector> res4 =  VecList
                .Where(n => n.value > 3)
                .OrderBy(n => n.value)
                .Skip(1)
                .Take(3)
                .Select(n=> n);

            foreach (Vector name in res4)
                Console.WriteLine(name.value);
            int[] key = new int[11] { 1,2,3,4,5,6,7,8,9,10,11 };
            var hash = stringArray
                .Join(
                    key,
                    w => w.Length,
                    q => q,
                    (w, q) => new
                    {
                        id     = w,
                        vector = q, 
                    }
                );

            Console.WriteLine(VecList
                .Where(n=>n.value > 0)
                .Count());

            IEnumerable<Vector> res5 = VecList
                .Where( n => n == VecList.Max())
                .Select(n => n);
            foreach (Vector name in res5)
                Console.WriteLine(name.value);

            IEnumerable<Vector> res6 = VecList
                .FirstOrDefault(n => n.value < 0);
           

            IEnumerable<Vector> res7 = VecList
                .OrderBy(n=> n.value)
                .Select(n=>n);
            foreach (Vector name in res7)
                Console.WriteLine(name.value);

            Console.ReadKey();
        }
    }
}
