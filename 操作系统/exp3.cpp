#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#define SHM_SIZE 1024
#define SHM_COUNT 5

/***对信号量数组index编号的信号量做P操作***/
void P(int semid, int index)
{
    struct sembuf sem = {index, -1, 0};
    semop(semid, &sem, 1);
}

/***对信号量数组index编号的信号量做V操作***/
void V(int semid, int index)
{
    struct sembuf sem = {index, +1, 0};
    semop(semid, &sem, 1);
}

int main()
{
    string IN_FILENAME;
    string OUT_FILENAME;

    cout <<"pls input infile name:";
    cin >> IN_FILENAME;

    cout << "pls input outfile name:";
    cin >> OUT_FILENAME;

    int semid; //信号量集标识符
    semid = semget(ftok(".", 5), SHM_COUNT * 2, 0666 | IPC_CREAT);
    /*****分别对每个信号量赋初值*****/
    union semun {
        int val;
    } arg;
    arg.val = 1;
    for(int i = 0;i< SHM_COUNT ; i++)
    {
        if(semctl(semid, i, SETVAL, arg) == -1) //是否可写,初值为1表示可写
            perror("semctl setval error1");
    }
    arg.val = 0;

    for (int i = 0; i < SHM_COUNT; i++)
    {
        if(semctl(semid, i + 5 , SETVAL, arg) == -1) //是否可读，初值为0表示不可读
            perror("semctl setval error2");
    }
    //创建共享内存
    vector<int> shm_id;//存放共享内存标识
    
    for(int i =0 ;i<SHM_COUNT;i++)
        shm_id.push_back(shmget(IPC_PRIVATE, SHM_SIZE + sizeof(int), IPC_CREAT | 0666));
    cout<<"creat shm OK!"<<endl;
    //创建两个进程readbuf,writebuf
    //readbuf

    int pid1,pid2;
    while((pid1 = fork())==-1);//创建子进程write
    if(pid1 > 0 )//父进程
    {
        while((pid2 = fork())==-1);//创建子进程read
        if(pid2 == 0)//子进程read
        {
            int size;
            int index = 0;
            char * shared_memory;
            FILE *fp;
            if((fp = fopen(IN_FILENAME.c_str(),"rb+"))==nullptr)
            {
                cout << "打开infile文件失败！\n";
                return -1;
            }
            while(1){
                P(semid,index);//写缓存区
                shared_memory = (char *)shmat(shm_id[index], 0, 0);//获取内存权限
                size = fread(shared_memory+sizeof(int),sizeof(char),SHM_SIZE,fp);
                *((int*)shared_memory) = size;
                //cout << "read file:" << size << " index:" << index << endl;
                shmdt(shared_memory);//分离权限
                V(semid,index+SHM_COUNT);//可以读这个缓存区了
                index = (index + 1) % SHM_COUNT;
                if(size < SHM_SIZE-1)
                    break;
            }
            fclose(fp);
            cout <<"finish read"<<endl;
            return 0;
        }
        else if(pid2>0){//父进程
            wait(0);
            wait(0);
            for(int i =0 ;i<SHM_COUNT;i++){
                shmctl(shm_id[i], IPC_RMID, 0); //删除共享内存
            }
            cout<<"copy end!"<<endl;
            return 0;
        }
    }
    else if(pid1 == 0)//子进程writebuf
    {
        FILE *fp;
        int  index = 0;
        char *shared_memory;
        int size;
        bool exit_flag = false;
        if ((fp = fopen(OUT_FILENAME.c_str(), "wb+")) == NULL)
        {
            cout << "outfile打开失败！\n";
            return -1;
        }

        while (1)
        {
            P(semid, index + SHM_COUNT); //读缓存区     
            //getchar();  
            shared_memory = (char *)shmat(shm_id[index], 0, 0); //获取内存权限
            size = *((int *)shared_memory);
            //cout << "write file:" << size << " index:" << index << endl;
            fwrite(shared_memory+4, sizeof(char),size, fp);
            shmdt(shared_memory);
            V(semid, index); //可以写缓存区了
            index = (index + 1) % SHM_COUNT;
            if(size < SHM_SIZE-1)
                break;
        }
        fclose(fp);
        cout <<"finish write!"<<endl;
        return 0;
    }
}