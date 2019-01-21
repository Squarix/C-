using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace LP_Lab13
{
    public class BVADiskInfo
    {
        public static Dictionary<string, long> FreeSpaceInfo()
        {
            Dictionary<string, long> disksInfo = new Dictionary<string, long>();
            var allDriver = DriveInfo.GetDrives();
            foreach (var d in allDriver)
               disksInfo.Add (d.Name, d.AvailableFreeSpace);
            return disksInfo;
        }

        public static Dictionary<string, string> FileSystemInfo()
        {
            Dictionary<string, string> allDrives = new Dictionary<string, string>();
            var allDriver = DriveInfo.GetDrives();
            foreach (var d in allDriver)
                allDrives.Add(d.Name, d.DriveFormat);
            return allDrives;
        }

    }

    public class BVAFileInfo
    {
        public static string PathInfo(string path)
        {
            if (File.Exists(path))
            {
                var fileInfo = new FileInfo(path);
                return fileInfo.DirectoryName;
            }

            return "File not found";
        }

        public static string FileParamsInfo(string path)
        {
            if (File.Exists(path))
            {
                var fileInfo = new FileInfo(path);
                string summaryInfo = fileInfo.DirectoryName + "  LENGTH:" +
                    fileInfo.Length + "  EXTENSION:" +
                    fileInfo.Extension + "  FULLNAME:" +
                    fileInfo.FullName + " NAME: " +
                    fileInfo.Name;
                return summaryInfo;
            }

            return "File not found";
        }

        public static string DateAddInfo(string path)
        {
            if (File.Exists(path))
            {
                var fileInfo = new FileInfo(path);
                return fileInfo.CreationTime.ToString();
            }

            return "File not found";
        }
    }

    public class BVADirInfo
    {
        public static bool isExist(string path)
        {
            return Directory.Exists(path);
        }

        public static int FileAmount(string path)
        {
            int fileAmount = -1;
            if (isExist(path))
            { 
                fileAmount = Directory.GetFiles(path).Count();   
            }
            return fileAmount;
        }
        
        public static string DateAddInfo(string path)
        {
            if (isExist(path))
            {
                DirectoryInfo dirInfo = new DirectoryInfo(path);
                return dirInfo.CreationTime.ToString();
            }
            return "Directory not found";
        }

        public static string[] SubDirAmount(string path)
        {
            if (isExist(path))
            {
               return Directory.GetDirectories(path);
            }
            string[] error = new string[] { "Directory not found" };
            return error;
        }

        public static string ParentDirInfo(string path)
        {
            if (isExist(path))
            {
                return Directory.GetParent(path).Name;
            }
            return "Directory not found";
        }
    }

    public class BVAFileManager
    {
        public static void CreateDir(string path)
        {
            Directory.CreateDirectory(path);
        }

        public static void RemoveDir(string path)
        {
            Directory.Delete(path);
        }

        public static void CopyFile(string path, string name)
        {
            File.Copy(path, name);
        }

        public static void RenameFile(string path, string name)
        {
            File.Copy(path, name);
            File.Delete(path);
        }
    }
}
