//D:/learn/c++/c++_experiment/U201714480_1
#include<cstdio>
#include<cstdlib>
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

struct STACK
{
    int *elems;//申请内存用于存放栈的元素
    int max;//栈能存放的最大元素个数
    int pos;//栈实际已有元素个数 ，栈空时pos = 0
};

void initSTACK_NUM(STACK *const p,int m);//init with a num
void initSTACK(STACK *const p,const STACK &s);//init with a existed stack
int size(const STACK * const p);
int howMany(const STACK * const p);//ret pos
int getelem(const STACK *const p,int x);//get elem with index x
STACK *const push(STACK *const p ,int e);//push e,ret p
STACK *const pop(STACK *const p,int &e);//pop elem to e,ret p
STACK *const assign(STACK * const p, const STACK &s);//assign s to p,ret p
void print(const STACK * const p);//print p
void print_file(const STACK *const p,fstream outfile); //print to file

void destroySTACK(STACK * const p);//destroy p


void initSTACK_NUM(STACK *const p, int m){
    p->max = m;
    p->pos = 0;
    p->elems = (int *)malloc(sizeof(int)*m);
}

void initSTACK(STACK *const p, const STACK &s){
    p->max = s.max;
    p->pos = s.pos;
    p->elems = (int *)malloc(sizeof(int) * s.max);
    for(int j =0;j< s.max;j++){
        p->elems[j]=s.elems[j];
    }
}

int size(const STACK *const p){
    return p->max;
}

int howMany(const STACK *const p){
    return p->pos;
}

int getelem(const STACK *const p, int x){
    if(x<p->max&&x>=0)
        return p->elems[x];
    else
        return -1;
}

STACK *const push(STACK *const p, int e){
    if(p->pos < p->max){
        p->elems[p->pos] = e;
        p->pos++;
        return p;
    }
    else
        return nullptr;
}

STACK *const pop(STACK *const p, int &e){
    if(p->pos == 0)
        return nullptr;
    else{
        e = p->elems[p->pos-1];
        p->pos--;
        return p;
    }
}

STACK *const assign(STACK *const p, const STACK &s){
    for (int j = 0; j < s.max; j++)
    {
        p->elems[j] = s.elems[j];
    }
    p->pos = s.pos;
    return p;
    }

void print(const STACK *const p){
    for(int i =0;i< p->pos ;i++)
        printf("%d  ",p->elems[i]);
}

void print_file(const STACK *const p, ofstream &outfile){
    for (int i = 0; i < p->pos; i++)
        outfile << p->elems[i] << "  ";
}

void destroySTACK(STACK *const p){
   if(p->elems)
        free(p->elems);
    p->pos = 0;
    p->max = 0;
}

int main(const int argc,const char ** argv){
    string filename=argv[0];
    int temp=filename.find(".exe");
    if (temp != filename.npos )
    {
        string s =filename.substr(0,temp);
        filename = s;
    }
    filename += ".txt";
    ofstream outfile(filename);
    STACK s;
    STACK * p = &s;
    STACK * q;
    for(int i = 1 ;i< argc;i++){
        if(argv[i][0]=='-'){
            switch (argv[i][1])
            {
            case 'S':
                {
                    outfile << "S  " << atoi(argv[i+1])<<"  ";
                    initSTACK_NUM(p,atoi(argv[i+1]));
                    print_file(p,outfile);
                    break;
                }
            case 'I':
                {
                    outfile << "I  ";
                    STACK *temp;
                    for (int j = i + 1; j < argc&&argv[j][0] != '-'; j++, i++)
                    {
                        if (argv[j][0] != '-')
                             temp = push(p, atoi(argv[j]));
                    }
                    if(temp != nullptr)
                        print_file(p, outfile);
                    else 
                        {
                            outfile << 'E'<<"  ";
                            i =argc-1;
                        }
                    break;
                }
            case 'O':
                {
                    outfile << "O  ";
                    STACK *temp;
                    int e;
                    for(int j = 0;j < atoi(argv[i+1]);j++)
                        temp=pop(p,e);                        
                    i++;
                    if (temp != nullptr)
                        print_file(p, outfile);
                    else
                        {
                            outfile << 'E' << "  ";
                            i = argc - 1;
                        }
                    break;
                }
            case 'C':
                {
                    outfile << "C  ";
                    STACK s1;
                    q = &s1;
                    initSTACK(q,s);
                    p = q;
                    initSTACK(p,s);
                    print_file(p, outfile);
                    break;
                }
            case 'A':
                {
                    outfile << "A  ";
                    i++;
                    print_file(p, outfile);
                    break;
                }
            case 'N':
                {
                    outfile << "N  "<<howMany(p)<<"  ";
                    break;
                }
            case 'G':
            {
                outfile << "G  ";
                if (atoi(argv[i + 1]) < s.max && atoi(argv[i + 1]) >= 0)
                    outfile<< getelem(p, atoi(argv[i + 1])) << "  ";

                else
                {
                    outfile << 'E' << "  ";
                    i = argc - 1;
                }
                break;
            }
            }
        }
        
    }
    outfile.close();
    return 0;
}