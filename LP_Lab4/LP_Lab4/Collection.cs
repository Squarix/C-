using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LP_Lab4
{
    public interface CollectionInt<T> where T:class
    {
        void Add(T obj);
        void Delete(T obj);
        void Lookup();
    }

    public class Database<T> : CollectionInt<T> where T:class
    {
        public string name;
        public string encode;
        private int counter = 0;
        List<T> list = new List<T>();
        public void Add(T obj)
        {
            list.Add(obj);
            counter++;
        }
        public void Delete(T obj)
        {
            list.Remove(list[counter]); 
        }
        public void Lookup()
        {
            foreach (T obj in list)
            {
                Console.WriteLine($"Имя объекта - {obj}");
            }
        }
    }
    public class DBSupport
    {
        
    }

    public class Table:DBSupport
    {
        string name;
        public Table(object name)
        {
            if (name.GetType() != typeof(string))
            {
                throw new Exception("Ошибка типов. Таблица принимает только string");
            }

            this.name = name.ToString();
        }

        public override string ToString()
        {
            return this.name.ToString();
        }

    }

    public class Schema:DBSupport
    {
        int name;
        public Schema(object name)
        {
            if (typeof(int) != name.GetType())
                throw new Exception("Ошибка типов. Схема принимает только int"); 
            this.name = (int)name;
        }
        public override string ToString()
        {
            return this.name.ToString();
        }
    }

    class Collection
    {
    }
}
