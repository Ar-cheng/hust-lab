#pragma once
#define MAX_LITERAL 1000//最大变元数目
#define LINE 1024 //读取一行的最大字符数

#define ERROR -1//异常返回状态
#define OK 1//函数返回状态正常
#define TRUE 1
#define FALSE -1

typedef int InfoType;
typedef int Status;//函数的返回状态

#define MAX_CLAUSE_LENGTH 30
#define CLAUSE 1
#define LITERAL 2
#define SPLIT 3
#define UNSURE -2

typedef int BOOL;
typedef struct First_Node {//首结点的结构
	int num; //记录该子句中变元的个数
	struct literal_Node *next_literalNode;// 指向子句中下一变元结点
	struct First_Node *next_FirstNode;//指向下一子句的首节点
	struct First_Node *prev_FirstNode;//指向上一子句的首节点
}First_Node;

typedef struct literal_Node {//变元节点的结构
	InfoType literal_info; //变元信息
	struct literal_Node *next_literalnode;//指向子句中下一变元结点
}literal_Node;

typedef struct cnf_set { //总的结构体
	int literal_num;//变元个数
	int literal_num_init;//最初变元个数
	int clause_num;//子句个数
	First_Node * set;//子句的集合
	int literal_bool[MAX_LITERAL];//记录对应序号变元的真假,1为真，-1为假，0为未知
	//int literal_counter[MAX_LITERAL];//变元数目统计
}cnf_set;

typedef struct Clause {//子句结构
	//int isexist=0;//判断子句是否存在
	int literalnum;//变元数目
	int newclause[MAX_CLAUSE_LENGTH];//记录变元序号
	int clauseboolean[MAX_CLAUSE_LENGTH];//记录变元正负,1为正，-1为负
}Clause;

typedef struct stack_i {//栈结构
	int flag;//压栈分类标志
	literal_Node * N;
	First_Node * P;
	stack_i * next;
}stack_i;
