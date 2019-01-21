using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace LP_Lab5
{
    struct Error
    {
        enum ProcessCode
        {
            code = 0x2225, 
        };
        private int code;
        private int description;
        public Error(int code)
        {
            this.code = code;
            this.description = (int)ProcessCode.code;
        }

    }

    partial class PartialClass
    {
        int partialField1;
    }
    [XmlRoot("Soft")]
    [Serializable]
    public abstract class Soft
    {
        [XmlElement]
        public string name;
        [XmlAttribute("platform")]
        public int bitness;
        [XmlIgnore]
        public string platform;
        virtual public bool LoadProcess()
        {
            Console.WriteLine("Загружаем процесс в память");
            return true;
        }
        public override string ToString()
        {
            Console.WriteLine($"Название объекта - {this.name}");
            string newStr = "";
            return newStr;
        }

        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }
    }
    [Serializable]    
    public abstract class TextProccessor : Soft
    {
        public TextProccessor()
        {
            this.bitness = 64;
            this.name = "Ворд";      
        }
        public override string ToString()
        {
            Console.WriteLine($"Название объекта - {this.name}, тип - TP:Soft");
            string newStr = "";
            return newStr;
        }
    }

    [Serializable]

    public class Word : TextProccessor
    {
        
        public Word ()
        {
            this.name = "Word";
            this.platform = "Windows 10";
        }
        override public bool LoadProcess()
        {
            Console.WriteLine("Загружаем Ворд");
            Console.WriteLine("3агружаем обнову в 989 килогигабайт");
            Console.WriteLine("Самое время сообщить о лицензии");
            Console.WriteLine("Немножко повисим");
            Console.WriteLine("Вылетаем");
            Console.WriteLine("");
            return true;
        }
    }

    interface VirusMethods
    {
        bool HackPentagon();
        bool FabricateElection(string country);
    }

    class Virus:Soft , VirusMethods
    {
        public bool HackPentagon()
        {
            Console.WriteLine("Пентагон успешно взломан!");
            Console.WriteLine("");
            return true;
        }

        public bool FabricateElection(string country)
        {
            if (country != "USA")
                throw new ElectionVirus();
            Console.WriteLine($"Выборы в {country} успешно подтусованны");
            Console.WriteLine("");
            return true;
        }
    }

    class Bomber : Soft
    {
        public Bomber()
        {
            name = "Сапер";
        }
        override public bool LoadProcess()
        {
            Console.WriteLine("");
            Console.WriteLine("Загружаем Сапёр");
            Console.WriteLine("Подгружаем спрайты");
            Console.WriteLine("Загружаем в память");
            Console.WriteLine("Разрешаем начать игру");
            Console.WriteLine("");
            return true;
        }
        public override string ToString()
        {
            Console.WriteLine("");
            Console.WriteLine($"Название объекта - {this.name}, тип - Bomber");
            string newStr = "";
            return newStr;
        }
    }

    sealed class Developer : Soft
    {

    }

    class Printer
    {
        public void iAmPrinting(Soft someobj)
        {
            Console.WriteLine(someobj.ToString());
        }
    }

    public class Computer :IEnumerable
    {
        public List<Soft> softList;

        public Computer(Soft[] obj)
        {
            softList = new List<Soft>();
            int i = 0;
            foreach (Soft soft in obj)
            {
                softList.Add(soft);
            }
        }


        IEnumerator IEnumerable.GetEnumerator()
        {
            return softList.GetEnumerator();
        }
    }

    public class Computer_Controller : IEnumerable<Soft>
    {
        private Computer computer;
        public Computer_Controller(Soft[] soft)
        {
            computer = new Computer(soft);
        }
        public void Add(Soft soft)
        {
            computer.softList.Add(soft);
        }

        public void PrintSoft()
        {
            foreach (Soft soft in computer.softList)
                Console.WriteLine(soft.Name);
        }

        public void RemoveAt(int index)
        {
            if (computer.softList.Count <= index)
                throw new IndexOutOfRangeException("Error!");
            else
                computer.softList.RemoveAt(index);
        }

        public IEnumerator<Soft> GetEnumerator()
        {
            return computer.softList.GetEnumerator();
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return computer.softList.GetEnumerator();
        }

        public Soft this[int index]
        {
            get
            {
                return computer.softList[index];
            }
            set
            {
                computer.softList[index] = value;
            }
        }

        public Soft SoftList
        {
            get
            {
                return computer.softList[0];
            }
            set
            {
                computer.softList[0] = value;
            }
        }

        public List<Soft> softGetList 
        {
            get { return this.computer.softList;  }
            set { }
        }

        public void WriteSoft(int index)
        {
            Console.WriteLine(computer.softList[index]);
        }

    }
}
