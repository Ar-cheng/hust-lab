#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <cstring>
#include <list>
#include <string>
#include <iomanip>
//--------------------------------------------------------------------------------
#define RESET "\033[0m"
#define RED "\033[31m"              /* Red */
#define BOLDRED "\033[1m\033[31m"   /* Bold Red */
#define GREEN "\033[32m"            /* Green */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BLUE "\033[34m"             /* Blue */
#define BOLDBLUE "\033[1m\033[34m"  /* Bold Blue */
//---------------------------------------------------------------------------------
// struct stat {
//     dev_t     st_dev;      文件的设备编号
//     ino_t     st_ino;      节点
//     mode_t    st_mode;     文件的类型和权限
//     nlink_t   st_nlink;    连到该文件的硬链接数目，刚建立的文件值为1
//     uid_t     st_uid;      用户ID
//     gid_t     st_gid;      组ID
//     dev_t     st_rdev;     设备类型）若此文件为设备文件，则为其设备编号
//     off_t     st_size;     文件字节数（文件大小）
//     blksize_t st_blksize;  块大小（文件I/O缓冲区的大小）
//     blkcnt_t  st_blocks;   块数
//     time_t    st_atime;    最后一次访问时间
//     time_t    st_mtime;    最后一次修改时间
//     time_t    st_ctime;    最后一次改变时间（指属性）
// };

void info_file(char *pathName)
{
    struct stat buf;
    struct tm *time;
    char filemode[11];
    char symlink[100];
    std::ios::fmtflags flag(std::cout.flags()); //save old format
    if (lstat(pathName, &buf) < 0)
    {
        perror("lstat error");
        return;
    }
    // 文件类型的宏变量（与宏函数功能类似）*/
    //            S_IFMT     0170000   bit mask for the file type bit fields
    //            S_IFSOCK   0140000   socket
    //            S_IFLNK    0120000   symbolic link
    //            S_IFREG    0100000   regular file
    //            S_IFBLK    0060000   block device
    //            S_IFDIR    0040000   directory
    //            S_IFCHR    0020000   character device
    //            S_IFIFO    0010000   FIFO
    //            S_ISUID    0004000   set UID bit
    //            S_ISGID    0002000   set-group-ID bit (see below)
    //            S_ISVTX    0001000   sticky bit (see below)
    switch (buf.st_mode & S_IFMT)
    {
    case S_IFREG: //regular
        filemode[0] = '-';
        break;
    case S_IFSOCK: //socket
        filemode[0] = 's';
        break;
    case S_IFLNK: //symbol link
        filemode[0] = 'l';
        break;
    case S_IFBLK: //block device 块设备信息
        filemode[0] = 'b';
        break;
    case S_IFDIR: //dir
        filemode[0] = 'd';
        break;
    case S_IFCHR: //character device 字符设备
        filemode[0] = 'c';
        break;
    case S_IFIFO: //fifo
        filemode[0] = 'p';
        break;
    default: //else
        perror("none type");
        break;
    }
    int i = 0;
    while (i < 9)
    {
        //文件权限宏变量*/
        //            S_IRWXU    00700     mask for file owner permissions
        //            S_IRUSR    00400     owner has read permission
        //            S_IWUSR    00200     owner has write permission
        //            S_IXUSR    00100     owner has execute permission
        //            S_IRWXG    00070     mask for group permissions
        //            S_IRGRP    00040     group has read permission
        //            S_IWGRP    00020     group has write permission
        //            S_IXGRP    00010     group has execute permission
        //            S_IRWXO    00007     mask for permissions for others (not in group)
        //            S_IROTH    00004     others have read permission
        //            S_IWOTH    00002     others have write permission
        //            S_IXOTH    00001     others have execute permission
        //std::cout <<"权限："<<buf.st_mode<<std::endl;
        if (buf.st_mode & (1 << i))
        {
            switch (i % 3)
            {
            case 0:
                filemode[9 - i] = 'x';
                break;
            case 1:
                filemode[9 - i] = 'w';
                break;
            case 2:
                filemode[9 - i] = 'r';
                break;
            }
        }
        else
        {
            filemode[9 - i] = '-';
        }
        i++;
    }

    // struct tm
    // {
    //     int tm_sec;                             /*Second [0,60].包含闰秒*/
    //     int tm_min;                             /*Minutes [0,59].*/
    //     int tm_hour;                            /*Hour [0,23].*/
    //     int tm_mday;                            /*Day of month [1,31].*/
    //     int tm_mon;                             /*Month of year [0,11].(January = 0)*/
    //     int tm_year;                            /*Year Since 1900.*/
    //     int tm_wday;                            /*Day of week [0,6] (Sunday = 0).*/
    //     int tm_yday;                            /*Day of year [0,365].包含闰年*/
    //     int tm_isdat; /*Daylight Savings flag*/ /*夏时制，夏时令（Daylight Saving Time：DST）*/
    // }
    //struct tm *localtime(const time_t *timer)

    time = localtime(&buf.st_mtime); //文件内容部分修改时间处理

    filemode[10] = '\0';
    std::cout << filemode << " ";
    std::cout << buf.st_nlink << " ";
    std::cout << std::left << std::setw(7) << std::setfill(' ') << getpwuid(buf.st_uid)->pw_name << " "; //获取用户
    std::cout << std::left << std::setw(7) << getgrgid(buf.st_gid)->gr_name;                             //获取用户组
    if (filemode[0] == 'b' || filemode[0] == 'c')                                                        //块设备信息或字符设备
        std::cout << (buf.st_rdev >> 8) << " " << (buf.st_rdev & 0xff);                                  //主设备号　次设备号
    else
        std::cout << std::right << std::setw(7) << std::right << buf.st_size << " "; //文件大小

    std::cout << time->tm_year + 1900 << "-" << time->tm_mon + 1 << "-" << time->tm_mday << " "; //时间

    std::cout << std::setw(2) << std::setfill('0') << time->tm_hour << ":" << std::setw(2) << time->tm_min << " "; //时间
    if (filemode[0] == 'l')                                                                                        //符号链接，蓝色输出
    {
        memset(symlink, '\0', sizeof(symlink));
        std::cout << BOLDBLUE << pathName << RESET << " -> ";
        if (readlink(pathName, symlink, sizeof(symlink)) > 0)
        {
            symlink[strlen(symlink)] = '\0';
            info_file(symlink);
        }
    }
    else if (filemode[0] == 'd') //目录，红色输出
    {
        std::cout << BOLDRED << pathName << '/' << RESET << std::endl;
    }
    else
    {
        if (filemode[3] == 'x') //可执行文件
        {
            std::cout << BOLDGREEN << pathName << RESET << std::endl;
        }
        else //其他类型
        {
            std::cout << pathName << std::endl;
        }
    }
}

void info_dir(char * filename,const char *dirName)
{
    std::list<dirent *> dirList;
    DIR *dir;
    struct dirent *direntp;
    struct stat buf;
    std::cout << dirName << ":" << std::endl;
    dir = opendir(filename);
    if (dir == NULL)
    {
        perror("error");
        return;
    }
    chdir(filename);
    while ((direntp = readdir(dir)) != NULL)
    {
        if (lstat(direntp->d_name, &buf) < 0)
        {
            perror("open folder error!");
        }
        if (S_ISDIR(buf.st_mode))
        {
            if (strcmp(direntp->d_name, "..") == 0 || strcmp(direntp->d_name, ".") == 0)
                continue;
            info_file(direntp->d_name);
            dirList.push_back(direntp);
        }
        else
            info_file(direntp->d_name);
    }
    std::cout << std::endl;
    for (std::list<dirent *>::iterator itor1 = dirList.begin(); itor1 != dirList.end(); itor1++)
    {
        std::string dirN = std::string(dirName) + "/" + (*itor1)->d_name; //构造子文件路径名
        info_dir((*itor1)->d_name, dirN.data());
        std::cout << std::endl;
    }
    chdir("..");
    closedir(dir);
}

int main(int argc, char *argv[])
{
    struct stat buf;
    for (int i = 1; i < argc; i++)
    {
        // S_ISLNK(st_mode)：是否是一个连接.S_ISREG(st_mode) ：是否是一个常规文件.S_ISDIR(st_mode) ：是否是一个目录
        // S_ISCHR(st_mode) ：是否是一个字符设备.S_ISBLK(st_mode) ：是否是一个块设备
        // S_ISFIFO(st_mode) ：是否 是一个FIFO文件.S_ISSOCK(st_mode) ：是否是一个SOCKET文件
        if (lstat(argv[i], &buf) < 0)
        {
            perror("lstat error");
            continue;
        }
        if (S_ISDIR(buf.st_mode)) //是一个目录
        {
            info_dir(argv[i], argv[i]);
        }
        else //不是目录，作为文件处理
        {
            info_file(argv[i]);
        }
    }
    return 0;
}