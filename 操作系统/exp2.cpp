#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

void P(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;       //操作标记：0或IPC_NOWAIT等
    semop(semid, &sem, 1); //1:表示执行命令的个数
    return;
}

void V(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}

int a = 0; //公共变量a

int semid; //信号量集标识符

pthread_t p1,p2;

void *subp1(void *arg)
{ //负责打印
    while(1){
        P(semid,1);
        cout << a <<endl;
        V(semid,0);
    }
}

void *subp2(void *arg)
{ //负责计算
    int j =1;
    while(j<=100){
        P(semid,0);
        a+= j;
        j++;
        V(semid,1);
    }
}

int main(){
    //创建信号灯
    semid = semget(ftok(".", 5), 2, 0666 | IPC_CREAT);
    /*****分别对每个信号量赋初值*****/
    union semun {
        int val;
    } arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) //是否可写,初值为1表示可写
        perror("semctl setval error1");
    arg.val = 0;
    if (semctl(semid, 1, SETVAL, arg) == -1) //是否可读，初值为0表示不可读
        perror("semctl setval error2");
    //创建子线程
    void *thread_result;
    int res = pthread_create(&p1,NULL,subp1,NULL);
    if(res!=0){
        perror("p1 error!");
        exit(1);
    }
    res = pthread_create(&p2, NULL, subp2, NULL);
    if (res != 0)
    {
        perror("p2 error!");
        exit(1);
    }
    pthread_join(p2, NULL);
    return 0;
}