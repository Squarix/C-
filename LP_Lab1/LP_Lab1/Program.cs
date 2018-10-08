using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LP_Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            bool    boolPrimit    = true;
            byte    bytePrimit    = 255;  // Хранит число в 1 байт
            sbyte   sbytePrimit   = -100; // byte со знаком
            short   shortPrimit   = 32767;
            ushort  ushortPrimit  = 65535;
            int     intPrimit     = 1000;
            uint    uintPrimit    = 13123;
            long    longPrimit    = 123132;
            ulong   ulongPrimit   = 1323;
            float   floatPrimit   = 123.456F;
            double  doublePrimit  = 123.456789;
            decimal decimalPrim   = 3235456; //  хранит десятичное дробное число. Если употребляется без десятичной запятой, 
                                             //имеет значение от 0 до +/–79 228 162 514 264 337 593 543 950 335; если с запятой, то от 0 до +/–7,9228162514264337593543950335
                                             //с 28 разрядами после запятой и занимает 16 байт. Представлен системным типом System.Decimal
            char   charPrimit   = 'a';
            string stringPrimit = "aaaa"; // unicode 2byte
            object a = 22;
            object b = 3.14;
            object c = "hello code";
            // может хранить значение любого типа данных и занимает 4 байта на 32-разрядной платформе и 8 байт на 64-разрядной платформе. 
            //Представлен системным типом System.Object, который является базовым для всех других типов и классов .NET.

            // 5 неявных преобразований
            shortPrimit  = sbytePrimit;
            intPrimit    = shortPrimit;
            longPrimit   = intPrimit;
            doublePrimit = floatPrimit;
            decimalPrim  = intPrimit;

            // 2 явных
            shortPrimit = (short)intPrimit;
            intPrimit   = Convert.ToInt32(longPrimit);

            // неявно типизированная переменная
            var nT  = 'h';
            var nT2 = "hi";
            var nT3 = 22;

            //nullable

            int? nullInt = null;
            if (!nullInt.HasValue) {
                nullInt = 225;
                Console.WriteLine($"nullInt: {nullInt}\n");
            }

            string string1 = "stringN1";
            string string2 = "stringN2";
            
            if(Equals(string1, string2)) {
                Console.WriteLine("Строки равны");
            } else {
                Console.WriteLine("Строки не равны");    
            }

            if (string1 == string2) {
                Console.WriteLine("Строки равны");
            } else {
                Console.WriteLine("Строки не равны");
            }

            string1 = String.Concat(string1, " hellowe");
            string2 = String.Copy(string1);
            string2 = string2.Substring(2, 3);

            string StringWWords = "Hellowe dsa dsa dsa dsds";
            string[] StringWArrWords = StringWWords.Split(' ');

            string1 = string1.Insert(4, "  |  Hellowe | ");
            string1 = string1.Remove(2, 4);

            string  str1 = "";
            string  str2 = null;

            StringBuilder stringBuilder = new StringBuilder("hellouwe");
            stringBuilder.Append(" end of string");
            stringBuilder.Insert(0, "begining of string ");
            stringBuilder.Insert(10, "somewhere");

            // punkt 3 

            int[,] ArrInt = new int[,] { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            int rows = ArrInt.GetUpperBound(0) + 1;
            int columns = ArrInt.Length / rows;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    Console.Write(ArrInt[i, j] + " ");
                }
                Console.WriteLine();
            }

            int[] ArrInt2 = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1 };
            Console.WriteLine("Изменение массива: введите позицию (0-10) и значение элемента ");
            int position = Convert.ToInt16(Console.ReadLine());
            int value    = Convert.ToInt16(Console.ReadLine());
            ArrInt2[position] = value;

            double[][] Arrauy = new double[3][];
            Arrauy[0] = new double[2];
            Arrauy[1] = new double[3];
            Arrauy[2] = new double[4];

            Console.WriteLine("Ввод double массива");
            
            for( int i = 0; i<3; i++) {
                for(int z = 0; z < 2 + i; z++) {
                    Arrauy[i][z] = Convert.ToDouble(Console.ReadLine());
                }
            }

            var varStr = "Неявнотипизированная переменная для хранения строки";
            var varArr = new int[] { 24, 12, 1999 };//для хранения массива
            //output type
            Console.WriteLine("str type -  " + varStr.GetType());//system.string
            Console.WriteLine("arr type -  " + varArr.GetType());//system.int32

            foreach(int Values in varArr)
            {
                Console.WriteLine(Values);
            }

            (int, string, char, string, ulong) kortezh = (1, "stroka", 's', "opyat stroka", 2555);
            var kortezh3 = (1, "stroka", 's', "opyat stroka", 2555);
            Console.WriteLine(kortezh);

            (int integer, string stinge, char chiar, string strings, ulong ushorti)kortezh2 = (1, "stroka", 's', "opyat stroka", 2555);

            Console.WriteLine($"{kortezh2.integer}  {kortezh2.Item2}  {kortezh2.ushorti}");
            int[] myarray222 = { 3, 4, 5, 2, 4, 2, 4 };
            Console.WriteLine("my answer is " + NewFunction(myarray222));

            Console.ReadKey();

        }
        static int NewFunction(int[] arr)
        {
            int result = 0;
            foreach (int i in arr)
            {
                if (i == 1)
                    result++;
            }

            bool ans(int count)//local function
            {
                return count > 1;
            }

            if (ans(result))
                result = 1999;
            return result;
        }
    }
}
