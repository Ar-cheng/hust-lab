#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<iostream>
#include<string>

using namespace std;

pid_t p1,p2;//进程p1 p2
int _pipe[2];//无名管道

void my_func(int sig){
    if(sig == SIGINT)
    {
        kill(p1,SIGUSR1);//发信号给p1
        kill(p2,SIGUSR2);//发信号到p2
       cout<<"\nKILL!"<<endl;
    }
}

//SIGUSR1 自定义信号 默认处理：进程终止
//SIGUSR2 自定义信号 默认处理：进程终止
void handle_p1(int sig){
    if(sig==SIGUSR1){//
        close(_pipe[1]);
         cout<<"Child Process 1 is Killed by Parent!"<<endl;
    }
    exit(0) ;
}
void handle_p2(int sig){
    if(sig==SIGUSR2){
        close(_pipe[0]);
        cout<<"Child Process 2 is Killed by Parent!"<<endl;
    }
    exit(0) ;
}
int main(void){
    int count=1;//计数器初值
    char buf[100] = {0};

    if(pipe(_pipe)<0) //创建管道
        cout<<"pipe error!"<<endl;
    
    if(signal(SIGINT,my_func)==SIG_ERR)
        cout<<"can't catch SIGINT\n";

    p1=fork();//创建子进程p1
   
    if(p1>0){//p1>0在父进程中
        p2=fork();//创建子进程p2

        if(p2>0){//p2>0在父进程中
            wait(0);//等待一个子进程退出
            wait(0);//等待另一个子进程退出
            close(_pipe[0]);//关闭读管道
            close(_pipe[1]);//关闭写管道
            cout<<"Parent Process is Killed!"<<endl;
        }
        else{//p2 = 0 在子进程p2中
            signal(SIGINT,(__sighandler_t)1);//屏蔽ctrl+c信号
            signal(SIGUSR2,handle_p2);
            close(_pipe[1]);//关闭写管道
            while(1){
                if(read(_pipe[0],buf,99)>0){
                    cout<<buf<<endl;
                }
            }
        }
    }
    else{//p1=0在子进程p1中
        signal(SIGINT,(__sighandler_t)1);//屏蔽ctrl+c信号
        signal(SIGUSR1,handle_p1);
        close(_pipe[0]);//关闭读管道
        while(1){
            sprintf(buf,"I send you %d times",count);
            write(_pipe[1],buf,sizeof(buf));
            sleep(1);
            count++;
        } 
    }
}