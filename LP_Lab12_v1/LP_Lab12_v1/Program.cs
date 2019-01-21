using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;
using System.IO;

namespace LP_Lab12_v1
{
    class Program
    {
        static void Main(string[] args)
        {
            Reflection.LogContains("LP_Lab12_v1.Reflection");
            Reflection.CallMethod("LP_Lab12_v1.TestingMethod", "Methode");
            Console.ReadKey();
        }
    }

    public class TestingMethod
    {
        public void Methode(int param)
        {
            Console.WriteLine("Hellou " + param);
        }
    }
    
    public class Reflection
    {
        public static void LogContains(string obj)
        {
            string logPath = @"E:\CSharpless\log.txt";
            using (StreamWriter sw = new StreamWriter(logPath, false, System.Text.Encoding.Default))
            {
                Type t = Type.GetType(obj);
                sw.WriteLine("Full name = " + t.FullName);
                sw.WriteLine("Base type is = " + t.BaseType);
                sw.WriteLine("Is sealed = " + t.IsSealed);
                sw.WriteLine("Is class = " + t.IsClass);
                foreach (Type iType in t.GetInterfaces())
                {
                    sw.WriteLine(iType.Name);
                }
                foreach (FieldInfo fi in t.GetFields())
                {
                    sw.WriteLine("Field = " + fi.Name);
                }
                MethodInfo[] mi = t.GetMethods();
                foreach (MethodInfo m in mi)
                {
                    sw.WriteLine("Public method -> " + m.Name);
                }
            }
        }

        public static void LogPublicMethods(string obj)
        {
            Type t = Type.GetType(obj);
            var bf = BindingFlags.Public;
            MethodInfo[] fi = t.GetMethods(bf);
            foreach (MethodInfo mi in fi)
            {
                Console.WriteLine("Public method -> " + mi.Name);
            }
        }

        public static void LogFieldsAndMethods(string obj)
        {
            Type t = Type.GetType(obj);
            foreach (FieldInfo fi in t.GetFields())
            {
                Console.WriteLine("Field = " + fi.Name);
            }
            foreach (MethodInfo fi in t.GetMethods())
            {
                Console.WriteLine("Field = " + fi.Name);
            }
        }

        public static void LogInterfaces(string obj)
        {
            Type t = Type.GetType(obj);
            foreach (Type iType in t.GetInterfaces())
            {
                Console.WriteLine(iType.Name);
            }
        }

        public static void LogMethodsWithParams(string obj, string type)
        {
            Type t = Type.GetType(obj);
            foreach (MethodInfo fi in t.GetMethods())
            {
                foreach(ParameterInfo pi in fi.GetParameters())
                {
                    if (pi.GetType() == Type.GetType(type))
                    {
                        Console.WriteLine("Method -> " + pi.Name);
                    }
                }
            }
        }

        public static void CallMethod(string obj, string method)
        {
            Assembly asm = Assembly.GetExecutingAssembly();
            string readPath = @"E:\CSharpless\in.txt";
            int param;
            using (StreamReader sr = new StreamReader(readPath, System.Text.Encoding.Default))
            {
                param = int.Parse(sr.ReadToEnd());
            }
            Console.WriteLine(param);
            Type t  = asm.GetType(obj);
            Console.WriteLine(t.Name);
            object newObj = Activator.CreateInstance(t);
            Console.WriteLine(newObj.GetType());
            MethodInfo newMethod = t.GetMethod(method);
     
            object result = newMethod.Invoke(newObj, new object[] { param });
        }
    }
}
