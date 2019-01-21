using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Xml.Serialization;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization.Formatters.Soap;
using System.Runtime.Serialization.Json;
using System.Xml.XPath;
using System.Xml;

namespace LP_Lab5
{
    class Program
    {
        static void Main(string[] args)
        {
            Word word = new Word();
            BinaryFormatter formatter = new BinaryFormatter();
            using (FileStream fs = new FileStream("word.dat", FileMode.OpenOrCreate))
            {
                formatter.Serialize(fs, word);
            }

            using (FileStream fs = new FileStream("word.dat", FileMode.OpenOrCreate))
            {
                Word newWord = (Word)formatter.Deserialize(fs);
                Console.WriteLine(newWord.Name);
            }

            SoapFormatter soapFormatter = new SoapFormatter();
            using (FileStream fs = new FileStream("word.soap", FileMode.OpenOrCreate))
            {
                soapFormatter.Serialize(fs, word);
            }

            XmlSerializer serializer = new XmlSerializer(typeof(Word));
            using (FileStream fs = new FileStream("points.xml", FileMode.OpenOrCreate))
            {
                serializer.Serialize(fs, word);
            }

            NetworkInfo ni = new NetworkInfo("ok", "You won't belive", "Article content");
            NetworkInfo n1 = new NetworkInfo("ok", "You won't belive", "Second Article content");
            DataContractJsonSerializer jsonSerializer = new DataContractJsonSerializer(typeof(NetworkInfo));
            using (FileStream fs = new FileStream("info.json", FileMode.Create))
            {
                jsonSerializer.WriteObject(fs, ni);
            }

            NetworkInfo[] netArray = new NetworkInfo[] { ni, n1 };
            DataContractJsonSerializer jsonArraySerializer = new DataContractJsonSerializer(typeof(NetworkInfo[]));
            using (FileStream fs = new FileStream("array.json", FileMode.Create))
            {
                jsonArraySerializer.WriteObject(fs, netArray);
            }

            using (FileStream fs = new FileStream("info.json", FileMode.OpenOrCreate))
            {
                NetworkInfo netInfo = (NetworkInfo)jsonSerializer.ReadObject(fs);
//                string jsonString = ;            
                Console.WriteLine(netInfo.status);
            }

            XmlDocument xDoc = new XmlDocument();
            xDoc.Load("points.xml");
            XmlElement xRoot = xDoc.DocumentElement;

            XmlNodeList nodeList = xRoot.SelectNodes("*");
            foreach (XmlNode node in nodeList)
                Console.WriteLine(node.OuterXml);
            Console.WriteLine("-----------");
            XmlNodeList nodeList2 = xRoot.SelectNodes("name");
            foreach (XmlNode node in nodeList2)
                Console.WriteLine(node.OuterXml);

            Console.Read();

        }

        partial class PartialClass
        {
            int partialField2;
        }

        [DataContract]
        public class NetworkInfo
        {
            [DataMember]
            public string status { get; set; }
            [DataMember]
            public Article article { get; set; }

            public NetworkInfo(string status, string header, string text)
            {
                this.status  = status;
                this.article = new Article(header, text);
            }
        }

        [DataContractAttribute]
        public class Article
        {
            [DataMember]
            public string header;
            [DataMember]
            public string text;
            public Article(string header, string text)
            {
                this.header = header;
                this.text   = text;
            }
        }
    }
}
