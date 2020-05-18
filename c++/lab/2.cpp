//D:/learn/c++/c++_experiment/U201714480_2
#include<iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

class STACK{
    int  *const  elems;	//申请内存用于存放栈的元素
    const  int   max;	//栈能存放的最大元素个数
    int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
STACK():elems(nullptr),max(0),pos(0){};//默认构造函数
STACK(int m);		//初始化栈：最多存m个元素
STACK(const STACK&s); 			//用栈s拷贝初始化栈
STACK(STACK&&s);       			//移动构造
virtual int  size ( ) const;			//返回栈的最大元素个数max
virtual operator int ( ) const;			//返回栈的实际元素个数pos
virtual int operator[ ] (int x) const;	//取下标x处的栈元素，第1个元素x=0
virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值栈
virtual STACK& operator=(STACK&&s);  //移动赋值
virtual void print( ) const;			//打印栈
virtual ~STACK( );					//销毁栈
};

// STACK(int m); //初始化栈：最多存m个元素
STACK::STACK(int m) : elems(new int[m]), max(m), pos(0)
{
}
// STACK(const STACK &s); //用栈s拷贝初始化栈
STACK::STACK(const STACK &s) : elems(new int[s.max]), max(s.max), pos(s.pos)
{
    for(int i = 0 ;i<this->pos;i++){
        this->elems[i]=s.elems[i];
    }
}
// STACK(STACK &&s); //移动构造
STACK::STACK(STACK &&s) : elems(s.elems), max(s.max), pos(s.pos)
{
    int ** p = (int **)&(s.elems);
    *p = nullptr;
}
// virtual int size() const; //返回栈的最大元素个数max
int STACK::size() const{
    return this->max;
}
// virtual operator int() const; //返回栈的实际元素个数pos
STACK::operator int() const{
    return this->pos;
}
// virtual int operator[](int x) const; //取下标x处的栈元素，第1个元素x=0
int STACK::operator [](int x) const{
    return this->elems[x];
}
// virtual STACK &operator<<(int e); //将e入栈,并返回栈
STACK& STACK::operator <<(int e){
    if(this->pos==this->max)
    cout<<"push failed!"<<endl;
    else{
        this->elems[pos]=e;
        this->pos++;
    }
    return *this;
}
// virtual STACK &operator>>(int &e); //出栈到e,并返回栈
STACK& STACK::operator>>(int &e){
    if(this->pos==0)
        cout<<"pop failed!"<<endl;
    else{
        this->pos--;
        e = this->elems[pos];
    }
    return *this;
}

// virtual STACK &operator=(const STACK &s); //赋s给栈,并返回被赋值栈

STACK& STACK::operator=(const STACK&s){
    if (s.max != this->max)
        {
            if(this->elems)
                delete this->elems;
            int **p = (int **)&(this->elems);    
            *p = new int[s.max];
            int *q = (int *)&(this->max);
            *q = s.max;
        }
        this->pos = s.pos;
        for (int i = 0; i < this->pos; i++)
        {
            this->elems[i] = s.elems[i];
    }
    return *this;
}

//virtual STACK &operator=(STACK &&s); //移动赋值

STACK& STACK::operator=(STACK &&s){
    this->pos = s.pos;
    int **p = (int **)(&(this->elems));
    int **q = (int **)(&(s.elems));
    int *r = (int *)(&(this->max));
    *p = s.elems;
    * q = nullptr;
    * r = s.max;
    return *this;
}

//virtual void print() const; //打印栈
void STACK::print() const{
    for (int i = 0; i < this->pos; i++)
        printf("%d  ", this->elems[i]);
}

//virtual ~STACK(); //销毁栈
STACK::~STACK(){
    if(this->elems)
        delete [] this->elems;
    this->pos = 0;
    int ** p = (int **)(&(this->elems));
    int ** q = (int **)(&(this->max));
    *p = nullptr;
    *q = 0;
}

void print_file(const STACK &s, ofstream &outfile)
{
    for (int i = 0; i < int(s); i++)
        outfile << s[i] << "  ";
}


int main(const int argc, const char **argv)
{
    string filename = argv[0];
    int temp = filename.find(".exe");
    if (temp != filename.npos)
    {
        string s = filename.substr(0, temp);
        filename = s;
    }
    filename += ".txt";
    ofstream outfile(filename);

    STACK * s =nullptr;
    outfile << "S  " << atoi(argv[2]) << "  ";
    STACK s1(atoi(argv[2]));
    print_file(s1, outfile);
    
    s=&s1;

    for (int i = 3; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 'I':
            {
                bool isoverflow =false;
                outfile << "I  ";
                for (int j = i + 1; j < argc && argv[j][0] != '-'; j++, i++)
                {
                    if (argv[j][0] != '-')
                    {
                        if(int(*s)<(*s).size())
                            *s << atoi(argv[j]);
                        else
                            isoverflow = true;
                    }
                }
                if(isoverflow == true)
                {
                    outfile << 'E' << "  ";
                    i = argc - 1;
                    break;
                }
                print_file(*s, outfile);
                break;
            }
            case 'O':
            {
                bool isoverflow = false;
                outfile << "O  ";
                int e;
                for (int j = 0; j < atoi(argv[i + 1]); j++)
                {
                    if(int(*s)>0)
                        *s >> e;
                    else
                        isoverflow = true;
                }
                i++;
                if (isoverflow == true)
                {
                    outfile << 'E' << "  ";
                    i = argc - 1;
                    break;
                }
                print_file(*s, outfile);
                break;
            }
            case 'C':
            {
                outfile << "C  ";
                STACK s_temp(*s);
                s1 = move(s_temp);
                s = &s1;
                print_file(*s, outfile); 
                break;
            }
            case 'A':
            {
                outfile << "A  ";
                i++;
                STACK s_temp(atoi(argv[i+1]));
                s_temp = *s;
                s1 = move(s_temp);
                s = &s1;
                print_file(*s, outfile);
                break;
            }
            case 'N':
            {
                outfile << "N  " << int(*s) << "  ";
                break;
            }
            case 'G':
            {
                outfile << "G  ";
                if (atoi(argv[i + 1]) < int(*s) && atoi(argv[i + 1]) >= 0)
                    outfile << (*s)[atoi(argv[i + 1])] << "  ";
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