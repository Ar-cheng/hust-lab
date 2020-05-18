//D:/learn/c++/c++_experiment/U201714480_4
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

class STACK
{
    int *const elems; //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;          //栈实际已有元素个数，栈空时pos=0;
public:
    STACK() : elems(nullptr), max(0), pos(0){}; //默认构造函数
    STACK(int m);                               //初始化栈：最多存m个元素
    STACK(const STACK &s);                      //用栈s拷贝初始化栈
    STACK(STACK &&s);                           //移动构造
    virtual int size() const;                   //返回栈的最大元素个数max
    virtual operator int() const;               //返回栈的实际元素个数pos
    virtual int operator[](int x) const;        //取下标x处的栈元素，第1个元素x=0
    virtual STACK &operator<<(int e);           //将e入栈,并返回栈
    virtual STACK &operator>>(int &e);          //出栈到e,并返回栈
    virtual STACK &operator=(const STACK &s);   //赋s给栈,并返回被赋值栈
    virtual STACK &operator=(STACK &&s);        //移动赋值
    virtual void print() const;                 //打印栈
    virtual ~STACK();                           //销毁栈
};

// STACK(int m); //初始化栈：最多存m个元素
STACK::STACK(int m) : elems(new int[m]), max(m), pos(0)
{
}
// STACK(const STACK &s); //用栈s拷贝初始化栈
STACK::STACK(const STACK &s) : elems(new int[s.max]), max(s.max), pos(s.pos)
{
    for (int i = 0; i < this->pos; i++)
    {
        this->elems[i] = s.elems[i];
    }
}
// STACK(STACK &&s); //移动构造
STACK::STACK(STACK &&s) : elems(s.elems), max(s.max), pos(s.pos)
{
    int **p = (int **)&(s.elems);
    *p = nullptr;
}
// virtual int size() const; //返回栈的最大元素个数max
int STACK::size() const
{
    return this->max;
}
// virtual operator int() const; //返回栈的实际元素个数pos
STACK::operator int() const
{
    return this->pos;
}
// virtual int operator[](int x) const; //取下标x处的栈元素，第1个元素x=0
int STACK::operator[](int x) const
{
    return this->elems[x];
}
// virtual STACK &operator<<(int e); //将e入栈,并返回栈
STACK &STACK::operator<<(int e)
{
    if (this->pos == this->max)
        cout << "push failed!" << endl;
    else
    {
        this->elems[pos] = e;
        this->pos++;
    }
    return *this;
}
// virtual STACK &operator>>(int &e); //出栈到e,并返回栈
STACK &STACK::operator>>(int &e)
{
    if (this->pos == 0)
        cout << "pop failed!" << endl;
    else
    {
        this->pos--;
        e = this->elems[pos];
    }
    return *this;
}
// virtual STACK &operator=(const STACK &s); //赋s给栈,并返回被赋值栈
STACK &STACK::operator=(const STACK &s)
{
    if (s.max != this->max)
    {
        if (this->elems)
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

STACK &STACK::operator=(STACK &&s)
{
    this->pos = s.pos;
    int **p = (int **)(&(this->elems));
    int **q = (int **)(&(s.elems));
    int *r = (int *)(&(this->max));
    *p = s.elems;
    *q = nullptr;
    *r = s.max;
    return *this;
}

//virtual void print() const; //打印栈
void STACK::print() const
{
    for (int i = 0; i < this->pos; i++)
        printf("%d  ", this->elems[i]);
}

//virtual ~STACK(); //销毁栈
STACK::~STACK()
{
    delete[] this->elems;
    this->pos = 0;
    int **p = (int **)(&(this->elems));
    int **q = (int **)(&(this->max));
    *p = nullptr;
    *q = 0;
}

class QUEUE : public STACK
{
    STACK s;

public:
    QUEUE(int m);                             //每个栈最多m个元素，要求实现的队列最多能入2m个元素
    QUEUE(const QUEUE &q);                    //用队列q拷贝初始化队列
    QUEUE(QUEUE &&q);                         //移动构造
    virtual operator int() const;             //返回队列的实际元素个数
    virtual int full() const;                 //返回队列是否已满，满返回1，否则0
    virtual int operator[](int x) const;      //取下标为x的元素，第1个元素下标为0
    virtual QUEUE &operator<<(int e);         //将e入队列,并返回队列
    virtual QUEUE &operator>>(int &e);        //出队列到e,并返回队列
    virtual QUEUE &operator=(const QUEUE &q); //赋q给队列,并返回被赋值队列
    virtual QUEUE &operator=(QUEUE &&q);      //移动赋值
    virtual void print() const;               //打印队列
    virtual ~QUEUE();                         //销毁队列
    void debug()
    {
        cout << "s1.size: " << STACK::size() << "   s1.pos: " << STACK::operator int() << "   ---";
        STACK::print();
        cout << endl;
        cout << "s2.size: " << s.size() << "   s2.pos: " << int(s) << "   ---";
        s.print();
        cout << endl;
    }
};
// QUEUE(int m);                             //每个栈最多m个元素，要求实现的队列最多能入2m个元素
QUEUE::QUEUE(int m) : STACK(m), s(STACK(m))
{
    //s = STACK(m);
}

// QUEUE(const QUEUE &q);                    //用队列q拷贝初始化队列
QUEUE::QUEUE(const QUEUE &q) : STACK(q), s(q.s)
{
}
// QUEUE(QUEUE &&q);                         //移动构造
QUEUE::QUEUE(QUEUE &&q) : STACK(move(q)), s(move(q.s))
{
    //s = move(q.s);
}
// virtual operator int() const;             //返回队列的实际元素个数
QUEUE::operator int() const
{
    return int(s) + STACK::operator int();
}
// virtual int full() const;                 //返回队列是否已满，满返回1，否则返回0
int QUEUE::full() const
{
    if (STACK::size() == STACK::operator int() && int(s) > 0)
        return 1;
    else
        return 0;
}
// virtual int operator[](int x) const;      //取下标为x的元素,第1个元素下标为0
int QUEUE::operator[](int x) const
{
    // cout << "s1.size: " << STACK::size() << "   s1.pos: " << STACK::operator int() << "   ---";
    // STACK::print();
    // cout << endl;
    // cout << "s2.size: " << s.size() << "   s2.pos: " << int(s) << "   ---";
    // s.print();
    // cout << endl;
    //cout<<"int s:   "<<int(s);
    if (x < int(s))
    {
        return s[int(s) - x - 1];
        // cout<<"s2....\n";
    }
    else if (x < int(s) + STACK::operator int())
    {
        return STACK::operator[](x - int(s));
        //  cout<<"s1...\n";
    }
    else
        return -1;
}
// virtual QUEUE &operator<<(int e);         //将e入队列,并返回队列
QUEUE &QUEUE::operator<<(int e)
{
    // debug();
    if (STACK::operator int() < STACK::size())
    {
        STACK::operator<<(e);
        return *this;
    }
    else if (int(s) == 0)
    {
        for (int i = 0; i < STACK::size(); i++)
        {
            int temp = 0;
            STACK::operator>>(temp);
            s << temp;
        }
        STACK::operator<<(e);
        return *this;
    }
    else
    {
        cout << "push faled!";
        return *this;
    }
}
// virtual QUEUE &operator>>(int &e);        //出队列到e,并返回队列
QUEUE &QUEUE::operator>>(int &e)
{
    //debug();
    if (int(s) > 0)
    {
        s >> e;
        return *this;
    }
    else if (STACK::operator int() > 0)
    {
        for (int i = 0, length = STACK::operator int(); i < length; i++)
        {
            //debug();
            int temp = 0;
            STACK::operator>>(temp);
            s << temp;
        }
        s >> e;
        return *this;
    }
    else
    {
        cout << "pop failed";
        return *this;
    }
}
// virtual QUEUE &operator=(const QUEUE &q); //赋q给队列,并返回被赋值的队列
QUEUE &QUEUE::operator=(const QUEUE &q)
{
    s = q.s;
    STACK::operator=(q);
    return *this;
}
// virtual QUEUE &operator=(QUEUE &&q);      //移动赋值
QUEUE &QUEUE::operator=(QUEUE &&q)
{
    s = move(q.s);
    STACK::operator=(q);
    return *this;
}
// virtual void print() const;               //打印队列
void QUEUE::print() const
{

    for (int i = int(s) - 1; i >= 0; i--)
        printf("%d  ", s[i]);
    for (int i = 0; i < STACK::operator int(); i++)
        printf("%d  ", STACK::operator[](i));
}
// virtual ~QUEUE();                         //销毁队列
QUEUE::~QUEUE()
{
}

void print_file(const QUEUE &s, ofstream &outfile)
{
    for (int i = 0; int(s) > 0 && i < int(s); i++)
        outfile << s[i] << "  ";
    // for (int i = int(s) - 1; i >= 0; i--)
    //     outfile << s[i] << "  ";
    // for (int i = 0; i < s.STACK::operator int(); i++)
    //     outfile << s.STACK::operator[](i) << "  ";
}

///在完成上述程序及测试无误后，请使用队列解决如下舞伴问题，此时main用非命令行的方式工作。假定在一次舞会上，男士排成一队，女士排成另一队。每次舞曲响起时，从男队和女队的队头各出一人，配成舞伴跳完此曲，跳完后各自进入自己队列的尾部。若男女两队的初始人数分别为M和F（M和F均为素数，且M != F），男队中排在位置m（m <= M）的男士，非常想和女队位置f（f <= F）的女士跳舞，问他在第几支曲舞曲才能和该女士跳舞 ? 请编程解决上述问题。
int main(){
    int count = 1;
    int M,F;
    int m,f;
    int first_m,first_f;

    cout << "pls input M && F:  ";
    cin >> M >> F;
    cout << "\npls input m && f:  ";
    cin >> m >> f;

    QUEUE s1(M);
    QUEUE s2(F);

    for (int i = 0; i < M ; i++){
        s1 << i;
    }
    for (int i = 0; i < F; i++)
    {
        s2 << i;
    }
    
    s1 >> first_m;
    s2 >> first_f;
    while ((first_m !=m)||( first_f!=f))
    {
        s1<<first_m;
        s2<<first_f;
        s1>>first_m;
        s2>>first_f;
        count++;
    }
    cout<<"\nthe count :  "<<count<<endl;
    getchar();
    getchar();
}