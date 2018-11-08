using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LP_Lab5
{
    public abstract class GetExceptions: Exception
    {
        protected short num;
        protected string message;
    }

    public class MyExceptions:GetExceptions
    {
       
        public MyExceptions()
        {
            num = 777;
            message = "Общая ошибка (не найден более конкретный обработчик)";
            this.PrintError();
        }

        private void PrintError()
        {
            Console.WriteLine($"Ошибка - {this.num}");
            Console.WriteLine($"Сообщение: {this.message}");
        }
    }

    public class VirusException: GetExceptions
    {
        public VirusException()
        {
            this.message = "Ошибка вируса!";
        }
        public void LoadData()
        {
            Console.WriteLine(this.message);
        }
    }

    public class ElectionVirus: GetExceptions
    {
        public ElectionVirus()
        {
            this.message = "USA only fabrcating election is allowed";
            this.num     = 1337;
        }

        public void GetInfo()
        {
            Console.WriteLine($"Message - {message}");
            Console.WriteLine($"Num - {num}");
        }
    }
}
