using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LP_Lab4
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                Database<DBSupport> db = new Database<DBSupport>();
                Table table = new Table("users");
                Schema schema = new Schema(115);
                db.Add(table);
                db.Add(schema);
                db.Lookup();
                Console.ReadLine();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }
    }

    class OdnomerniyMassive
    {
        public int[] massive;
        int this[int firstElem, int secondElem]
        {
            get { return massive[0]; }
            set { }
        }

        public OdnomerniyMassive(params int[] param)
        {
            massive = new int[param.Length];
            for (int i = 0; i < param.Length; i++)
            {
                massive[i] = param[i];
            }
        }

        public OdnomerniyMassive()
        {
            Random rand = new Random();
            massive     = new int[10];
            for (int i = 0; i < 10; i++)
            {
                massive[i] = rand.Next(1,5);
            }
        }

        public void AddToMassive(params int[] param)
        {
            for (int i = 0; i < param.Length; i++)
            {
                massive[i] += param[i];
            }
        }

        public static OdnomerniyMassive operator *(OdnomerniyMassive MassiveClass, int[] massive2)
        {
            for (int i = 0; i < MassiveClass.massive.Length && i < massive2.Length; i++)
            {
                MassiveClass.massive[i] *= massive2[i];
            }
            return MassiveClass;
        }

        public static bool operator true(OdnomerniyMassive MassiveClass)
        {
            bool isTrue = true;
            for (int i = 0; i < MassiveClass.massive.Length; i++)
            {
                if (MassiveClass.massive[i] < 0)
                {
                    isTrue = false;
                }
            }
            return isTrue;
        }

        public static bool operator false(OdnomerniyMassive MassiveClass)
        {
            bool isTrue = false;
            for (int i = 0; i < MassiveClass.massive.Length; i++)
            {
                if (MassiveClass.massive[i] > 0)
                {
                    isTrue = true;
                }
            }
            return isTrue;
        }

        public static explicit operator int(OdnomerniyMassive MassiveClass)
        {
            return MassiveClass.massive.Length;
        }

        public static bool operator ==(OdnomerniyMassive MassiveClass, int value)
        {
            if(MassiveClass.massive[0] == value)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static bool operator !=(OdnomerniyMassive MassiveClass, int value)
        {
            if (MassiveClass.massive[0] != value)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static bool operator <(OdnomerniyMassive MassiveClass, int value)
        {
            if (MassiveClass.massive[0] < value)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static bool operator >(OdnomerniyMassive MassiveClass, int value)
        {
            if (MassiveClass.massive[0] > value)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public class Owner
        {
            int id;
            string name;
            string organisation;
            public Owner(int ownerID, string ownerName, string ownerOrg)
            {
                id           = ownerID;
                name         = ownerName;
                organisation = ownerOrg;
            }
        }

        public class Date
        {
            int day;
            int mounth;
            public Date(int dateDay, int dateMounth)
            {
                day    = dateDay;
                mounth = dateMounth;
            }
        }

        public Owner _owner
        {
            get; set;
        }

        public Date _date
        {
            get; set;
        }
    }
    static class MathObject
    {
        public static void MakeNull(ref OdnomerniyMassive obj1)
        {
            for( int i = 0; i < obj1.massive.Length; i++)
            {
                obj1.massive[i] = 0;
            }
        }
        public static int  FindMax(OdnomerniyMassive obj1)
        {
            int maxElem = obj1.massive[0];
            for (int i = 0; i < obj1.massive.Length; i++)
            {
                if (obj1.massive[i] > maxElem)
                {
                    maxElem = obj1.massive[i];
                }
            }
            return maxElem;
        }
        public static int FindMin(OdnomerniyMassive obj1)
        {
            int minElem = obj1.massive[0];
            for (int i = 0; i < obj1.massive.Length; i++)
            {
                if (obj1.massive[i] < minElem)
                {
                    minElem = obj1.massive[i];
                }
            }
            return minElem;
        }
    }
    static class Extension
    {
        public static int NewMethod(this OdnomerniyMassive obj)
        {
            return 1337;
        }
    }
}
