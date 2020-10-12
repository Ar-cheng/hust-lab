char c;
int c; //同一作用域变量重复定义
int fibo(char x)
{
    return 1;
}

int main()
{
    int f;
    char f;  //同一作用域变量重复定义
    f();     //对非函数名采用函数调用形式访问
    fibo;    //对函数名采用非函数调用形式访问
    fibo(f); //函数调用时实参和形参不匹配
    f[2];    //对非数组变量采用非函数调用形式访问

    (f + 1)++;   //对非左值进行自增自减运算
    f = 1 + 2.1; //类型不匹配
    e = f;       //使用未定义的变量
    g();         //调用未定义的函数
    break;       //break不在循环中
    continue;    //continue语句不在循环中
    return 1.1;  //函数返回值类型与函数定义返回值类型不匹配
}

int nortn()
{
    int a; //函数没有返回语句
}
