using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.Compression;

namespace LP_Lab13
{
    class Program
    {
        static void Main(string[] args)
        {
            using (StreamWriter sw = new StreamWriter(@"E:\Csharpless\LP_Lab13\log.txt"))
            {
                //var freeSpace = BVADiskInfo.FreeSpaceInfo();
                //foreach (string key in freeSpace.Keys)
                //{
                //    sw.WriteLine(key + ":" + freeSpace[key]);
                //}

                //var fileSystemInfo = BVADiskInfo.FileSystemInfo();
                //foreach (string key in fileSystemInfo.Keys)
                //{
                //    sw.WriteLine(key + ":" + freeSpace[key]);
                //}

                var pathinfo = BVAFileInfo.PathInfo(@"E:\Csharpless\LP_Lab13\log.txt");
                sw.WriteLine(pathinfo);

                sw.WriteLine(BVAFileInfo.FileParamsInfo(@"E:\Csharpless\LP_Lab13\log.txt"));
                sw.WriteLine(BVAFileInfo.DateAddInfo(@"E:\Csharpless\LP_Lab13\log.txt"));

                sw.WriteLine("File Amount");
                sw.WriteLine(BVADirInfo.FileAmount(@"E:\Csharpless\"));

                BVAFileManager.CreateDir(@"E:\Csharpless\BVAInspect");
                BVAFileManager.CreateDir(@"E:\Csharpless\BVAFiles");
                var dirInfo = new DirectoryInfo(@"E:\Csharpless\BVAInspect");
                foreach (FileInfo fi in dirInfo.GetFiles("*.txt"))
                { 
                    BVAFileManager.CopyFile(@"E:\Csharpless\BVAInspect\" + fi.Name,
                        @"E:\Csharpless\BVAFiles\" + fi.Name);
                }

                //ZipFile
            }
        }
    }
}

