#include <stdio.h>
#include <time.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include <direct.h>

//#define DEBUG
#define STRATEGY1

char filename[256];

#define MAX_LITERAL 1000//最大变元数目
#define LINE 1024 //读取一行的最大字符数

#define ERROR -1//异常返回状态
#define OK 1//函数返回状态正常
#define TRUE 1
#define FALSE -1

#define MAX_CLAUSE_LENGTH 30
#define CLAUSE 1
#define LITERAL 2
#define SPLIT 3
#define UNSURE -2

#define LOC(i,j,x) ((i)*81+(j)*9+(x))

typedef int InfoType;
typedef int Status;//函数的返回状态
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
	//int literal_num_init;//最初变元个数
	int clause_num;//子句个数
	First_Node * set;//子句的集合
	int literal_bool[MAX_LITERAL];//记录对应序号变元的真假,1为真，-1为假，0为未知
}cnf_set;

//typedef struct Clause {//子句结构
//	//int isexist=0;//判断子句是否存在
//	int literalnum;//变元数目
//	int newclause[MAX_CLAUSE_LENGTH];//记录变元序号
//	int clauseboolean[MAX_CLAUSE_LENGTH];//记录变元正负,1为正，-1为负
//}Clause;

typedef struct Sudoku {
	int sdk[9][9];
	Sudoku *next;
}Sudoku;

typedef struct stack_i {//栈结构
	int flag;//压栈分类标志
	literal_Node * N;
	First_Node * P;
	stack_i * next;
}stack_i;

//cnf_parser.h
Status Create_Set(cnf_set *, int);//创建子句集

Status set_print(cnf_set *);//打印集合

Status set_print_check(cnf_set *);//检验结果

Status stack_push(stack_i *, int, First_Node *, literal_Node *);//入栈

First_Node * stack_pop(stack_i *);//出栈

//Status stack_free(stack_i *);//栈释放

First_Node * creatClause(int *, int);//创建子句/1

Status addClause(First_Node *, cnf_set *);//增加子句/1

First_Node * removeClause(cnf_set *, First_Node *);//删除子句，返回其地址/1

Status deleteClause(cnf_set *, First_Node *);//销毁子句/1

Status addliteral(First_Node *, int);//在某一子句中增加变元/1

literal_Node * removeliteral(First_Node *, int);//在某一子句中删除变元

Status deleteLiteral(First_Node *, int);//销毁一个子句中的变元

BOOL isUnitClause(First_Node *);//判断是否为单子句/1

Status evaluateClause(First_Node *, int);//子句判真/1

BOOL isHaveEmptyClause(cnf_set *);//是否有空子句/1

BOOL isHaveClause(cnf_set *);//子句集是否为空/1

Status Clause_simply(cnf_set *, int, stack_i *);//单子句化简

First_Node * locateUnitClause(cnf_set *);//定位单子句

Status stack_print(stack_i *);//打印栈

Status Destroy_Set(cnf_set * S);//销毁集合




//DPLL.h
Status literal_Assign(cnf_set *, int);//存储变元赋值

Status literal_back(cnf_set *, int *);//变元的赋值进行回溯；

Status change_back(cnf_set *, stack_i *); //子句集合还原

int literal_chose(cnf_set *);

int literal_chose_better(cnf_set *);//优化后的变元选择方案

Status counter_sort_strategy(cnf_set *);//依据变元出现的次数来挑选变元

Status counter_sort_strategy_betweentwo(cnf_set *);//在变元数小于2的子句中统计变元次数

int VSIDS_strategy(cnf_set *);//VSIDS 策略

Status DPLL_rec(cnf_set *);

Status DPLL_rec2(cnf_set *);//优化后的DPLL算法

Status booleanprint(cnf_set *);

Status result_check(cnf_set *);//验证输出结果


//Sudoku
Sudoku* createSudoku(int);//生成数独

Status SudokuToCNF(Sudoku *);//转化成CNF格式

Sudoku *CNFToSudoku(cnf_set *);//CNF转化成数独

BOOL sudoku_check(Sudoku *);//是否合乎规则

BOOL judge_x_y(Sudoku *, int, int);//填入数字是否正确

BOOL sudoku_rand(Sudoku *, int, int);//随机生成数独的递归函数

BOOL sudoku_solve(Sudoku *, int *);//求解数独

BOOL sudoku_dfs(Sudoku *, int, int, int *);//DFS求解数独

Status sudoku_print(Sudoku *);//打印数独


//diaplay
void CNFPage();

void sudokuPage();

Status path_generate(char *savepath, char *cnfpath);//找到当前的操作文件

Status CnfToRes_path(char *, char *);//生成res文件存储地址

Status RES_save(char *respath, BOOL DPLL, cnf_set *s, int time);//保存结果

Status CNF_save(cnf_set* s, char *cnf_path);//保存数据


//cnf_parser
Status literal_print(cnf_set *);//变元打印

Status Create_Set(cnf_set *S, int tag) {//创建集合的结构体
	//if (tag == 1) {//tag == 1 表示读取cnf文件进行求解
	FILE *fp;//目标文件指针
	//int is_eof;//判断是否读取到文件尾
	int is_first_line = 1;//判断是否读取的是第一行
	int m = 1;
	if (tag == 1) {
		printf("输入文件名称：");
		scanf("%s", filename);
	}
	else if (tag == 2) {
		strcpy(filename, "sudoku.cnf");
	}
	else if (tag == 3);
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("    	  文件打开失败!\n ");
		return ERROR;
	}
	printf("文件打开成功！\n");
	char buff[10];
	char ch;
	//char c[10];
	//fscanf(fp, "%s", c);
	//while (strcmp(c, "c") == 0)//过滤掉所有以c开头的注释内容
	//{
	//	fscanf(fp, "%s", c);
	//	if (strcmp(c, "p") == 0)
	//		break;//针对空注释的情况
	//	else
	//	{
	//		fscanf(fp, "%*[^\n]%*c");//跳行，将文件指针置于下一行的开头
	//		fscanf(fp, "%s", c);
	//	}
	//}
	while ((ch = fgetc(fp)) == 'c') {
		while ((ch = fgetc(fp)) != '\n');
	}
	//变元个数以及子句个数读取
	fscanf(fp, "%s", buff);//滤掉cnf
	fscanf(fp, "%s", buff);//以字符串格式读取变元个数
	S->literal_num = atoi(buff);//字符->数字
	//S->literal_num_init = S->literal_num;
	fscanf(fp, "%s", buff);//以字符串格式读取子句个数
	S->clause_num = atoi(buff);//字符->数字

#ifdef DEBUG
	printf("变元个数为%d  子句个数为%d\n", S->literal_num, S->clause_num);//......DEBUG......
#endif

//子句读取及构建
	int i = 0;// 记录子句中变元的个数
	First_Node *u, *v;//临时变量
	literal_Node *p, *q;//临时变量

	//第一个子句
	S->set = (First_Node *)malloc(sizeof(First_Node));
	S->set->next_FirstNode = NULL;
	S->set->prev_FirstNode = NULL;
	p = (literal_Node *)malloc(sizeof(literal_Node));//读取子句的第一个变元
	p->next_literalnode = NULL;
	S->set->next_literalNode = p;
	fscanf(fp, "%s", buff);
	p->literal_info = atoi(buff);//录入变元信息
	i = 1;

#ifdef DEBUG
	printf("%d  ", p->literal_info);//....DEBUG....
#endif

	while (TRUE) {//同一子句的后续变元
		fscanf(fp, "%s", buff);
		if (strcmp(buff, "0") == 0)
			break;//判断当前子句是否读取完成
		q = (literal_Node *)malloc(sizeof(literal_Node));
		q->next_literalnode = NULL;
		q->literal_info = atoi(buff);//录入变元信息
		i++;
		//链接
		p->next_literalnode = q;
		p = q;

#ifdef DEBUG
		printf("%d ", p->literal_info);//......DEBUG......
#endif

	}
	S->set->num = i;//记录子句中的变元个数
	//printf("子句变元个数为%d\n", S->set->num);//....DEBUG....

	//后续子句
	while (m < S->clause_num/*&&(is_eof = fscanf(fp, "%s", buff)) != -1*/) {//判断是否读到文件尾
		v = (First_Node *)malloc(sizeof(First_Node));
		v->next_FirstNode = NULL;
		p = (literal_Node *)malloc(sizeof(literal_Node));//读取子句的第一个变元
		p->next_literalnode = NULL;
		v->next_literalNode = p;
		fscanf(fp, "%s", buff);
		p->literal_info = atoi(buff);//录入变元信息
		i = 1;

#ifdef DEBUG
		printf("%d ", p->literal_info);//......DEBUG......
#endif

		while (TRUE) {//同一子句的后续变元
			fscanf(fp, "%s", buff);
			if (strcmp(buff, "0") == 0)
				break;//判断当前子句是否读取完成
			q = (literal_Node *)malloc(sizeof(literal_Node));
			q->next_literalnode = NULL;
			q->literal_info = atoi(buff);//录入变元信息
			i++;
			//变元结点链接
			p->next_literalnode = q;
			p = q;

#ifdef DEBUG	
			printf("%d ", p->literal_info);
#endif
		}
		v->num = i;

		//首节点链接
		if (is_first_line)//第一行与第二行
		{
			S->set->next_FirstNode = v;
			v->prev_FirstNode = S->set;
			u = v;
			is_first_line = 0;

#ifdef DEBUG
			printf("子句变元个数为%d\n", S->set->num);//....DEBUG....
#endif			
		}
		else {//后续行
#ifdef DEBUG
			printf("子句变元个数为%d\n", u->num);//....DEBUG....
#endif
			u->next_FirstNode = v;
			v->prev_FirstNode = u;
			u = v;
		}
		m++;
	}
	//}
	//else if (tag == 2) {//tag ==2 表示创建空集合后以数独结构进行转换。
	//	S->clause_num = 0;
	//	S->literal_num = 9 * 9 * 9;
	//	S->literal_num_init = 0;
	//	S->set = NULL;
	//}
	return TRUE;
}

Status set_print(cnf_set * S) {
	First_Node * p = S->set;
	for (; p != NULL; p = p->next_FirstNode)
	{
		printf("变元个数：%d\t", p->num);
		literal_Node * q = p->next_literalNode;
		for (; q != NULL; q = q->next_literalnode)
			printf("%d ", q->literal_info);
		printf("\n");
	}
	printf("\n");
	return OK;
}

Status set_print_check(cnf_set *S) {
	First_Node * p = S->set;
	for (; p != NULL; p = p->next_FirstNode)
	{
		printf("变元个数：%d\t", p->num);
		literal_Node * q = p->next_literalNode;
		for (; q != NULL; q = q->next_literalnode)
			printf("%d ", S->literal_bool[abs(q->literal_info)]*q->literal_info);
		printf("\n");
	}
	printf("\n");
	return OK;
}

Status literal_print(cnf_set *S) {
	int i;
	for (i = 1; i <= S->literal_num; i++) {
		if ((i - 1) % 10 == 0)
			printf("\n");
		if (S->literal_bool[i] > 0)
			printf("%d:TRUE ", i);
		else if (S->literal_bool[i] < 0)
			printf("%d:FALSE ", i);
		else
			printf("%d:UNSURE ", i);
	}
	return OK;
}

Status stack_push(stack_i *t, int flag, First_Node *P, literal_Node *N) {
	//t是不含数据的头节点指针
	if (t == NULL) {
		return FALSE;
	}
	stack_i *new_room = (stack_i*)malloc(sizeof(stack_i));
	if (!new_room)
	{
		printf("栈溢出！");
		exit(-1);
	}
	new_room->flag = flag;
	switch (flag)
	{
	case CLAUSE://整个子句
		new_room->P = P;//保存子句的地址
		new_room->N = NULL;
		break;
	case LITERAL://某个变元
		new_room->P = P;//保存所在子句地址
		new_room->N = N;//保存该变元
		break;
	case SPLIT://添加的单子句变元
		new_room->P = P;//保存所在子句地址
		new_room->N = NULL;//保存该变元
		break;
	default:
		break;
	}
	new_room->next = t->next;
	t->next = new_room;
	return OK;
}

First_Node * stack_pop(stack_i *t) {
	stack_i * p = t->next;
	t->next = p->next;
	First_Node * q = p->P;
	free(p);
	return q;
}

//Status stack_free(stack_i * t) {//栈释放
//	stack_i *p, *q;
//	p = t;
//	q = t->next;
//	while (p != NULL)
//	{
//		free(p);
//		p = q;
//		if (q != NULL)
//			q = q->next;
//	}
//	return OK;
//}

First_Node * creatClause(int *x, int num) {//创建子句
	int i = 0;
	First_Node * p = (First_Node *)malloc(sizeof(First_Node));
	literal_Node * u, *v;
	p->num = num;
	p->next_FirstNode = NULL;
	p->prev_FirstNode = NULL;
	u = (literal_Node *)malloc(sizeof(literal_Node));
	u->literal_info = x[i];
	u->next_literalnode = NULL;
	p->next_literalNode = u;
	for (i = 1; i < num; i++) {
		v = (literal_Node *)malloc(sizeof(literal_Node));
		v->literal_info = x[i];
		v->next_literalnode = NULL;
		u->next_literalnode = v;
		u = v;
	}
	return p;
}

Status addClause(First_Node * P, cnf_set * S) {//增加子句
	if (S->set) {
		S->set->prev_FirstNode = P;
	}
	P->next_FirstNode = S->set;
	P->prev_FirstNode = NULL;

	S->set = P;
	S->clause_num++;
	return OK;
}

Status addliteral(First_Node *P, int literal) {//在某一子句头部增加变元lilteral
	literal_Node *p = (literal_Node*)malloc(sizeof(literal_Node));
	p->literal_info = literal;
	p->next_literalnode = P->next_literalNode;
	P->next_literalNode = p;
	P->num++;
	return OK;
}

First_Node * removeClause(cnf_set * S, First_Node * N) {//删除子句,返回其地址
	First_Node *p = N->prev_FirstNode;
	if (N->next_FirstNode)
		N->next_FirstNode->prev_FirstNode = p;
	if (p)
		p->next_FirstNode = N->next_FirstNode;
	else//N为第一个子句
		S->set = N->next_FirstNode;
	S->clause_num--;
	return N;
}

Status deleteClause(cnf_set * S, First_Node * P) {//销毁子句/
	{
		literal_Node *N, *M;
		First_Node *p1 = P->prev_FirstNode;
		if (P->next_FirstNode) {
			P->next_FirstNode->prev_FirstNode = p1;
		}
		if (p1) {
			p1->next_FirstNode = P->next_FirstNode;
		}
		else {
			S->set = P->next_FirstNode;
		}
		for (N = P->next_literalNode; N; N = M) {
			M = N->next_literalnode;
			free(N);
		}
	}
	free(P);
	S->clause_num--;
	return OK;
}

literal_Node * removeliteral(First_Node * P, int literal) {//在某一子句中删除变元
	literal_Node *p, *q = NULL;
	for (p = P->next_literalNode; p; p = p->next_literalnode) {
		if (p->literal_info == literal) {
			P->num--;
			if (!q) {//针对第一个节点匹配成功的情况
				P->next_literalNode = p->next_literalnode;
			}
			else {
				q->next_literalnode = p->next_literalnode;
			}
			return p;
		}
		q = p;
	}
	return NULL;
}

Status deleteLiteral(First_Node * P, int literal) {//删除一个子句中的变元
	literal_Node *p, *q = NULL;
	for (p = P->next_literalNode; p; p = p->next_literalnode) {
		if (p->literal_info == literal) {
			P->num--;
			if (!q) {//针对第一个节点匹配成功的情况
				P->next_literalNode = p->next_literalnode;
			}
			else {
				q->next_literalnode = p->next_literalnode;
			}
			free(p);
			return OK;
		}
		q = p;
	}
	return ERROR;
}

BOOL isUnitClause(First_Node * p) {//判断是否为单子句
	return  (p->num == 1) ? TRUE : FALSE;
}

Status evaluateClause(First_Node * P, int literal)//子句判真
{
	literal_Node *p = P->next_literalNode;
	//int i = 0;
	for (; p; p = p->next_literalnode) {
		if (literal == p->literal_info) {
			return TRUE;//子句为真
		}
		else if (-literal == p->literal_info) {
			return UNSURE;//不确定
		}
	}
	return UNSURE;
}

BOOL isHaveEmptyClause(cnf_set *S) {//是否有空子句
	First_Node *p;
	for (p = S->set; p; p = p->next_FirstNode) {
		if (!(p->num)) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL isHaveClause(cnf_set * S) {//子句集是否为空
	return  (S->set) ? TRUE : FALSE;
}

Status Clause_simply(cnf_set * S, int literal, stack_i *head) {//单子句规则化简
	//set_print(S);
	literal_Node * N;
	First_Node * P = S->set;
	First_Node * q;
	while (P) {
		switch (evaluateClause(P, literal))
		{
		case TRUE:
			removeClause(S, P);
			stack_push(head, CLAUSE, P, NULL);//存子句
			P = P->next_FirstNode;
			break;
		case UNSURE://移除子句中选定变元的非
			N = removeliteral(P, -literal);
			if (N != NULL)
				stack_push(head, LITERAL, P, N);//存变元
			P = P->next_FirstNode;
			break;
		default:
			P = P->next_FirstNode;
			break;
		}
	}
	return OK;
}

First_Node * locateUnitClause(cnf_set * S) {//定位单子句
	First_Node * p;
	for (p = S->set; p; p = p->next_FirstNode) {
		if (isUnitClause(p) == TRUE) {
			return p;
		}
	}
	return NULL;
}

Status stack_print(stack_i * t) {
	stack_i * p;
	p = t->next;
	printf("栈为：\n");
	while (p) {
		switch (p->flag)
		{
		case CLAUSE:
			printf("CLAUSE:%d\n", p->P->next_literalNode->literal_info);
			break;
		case LITERAL:
			printf("LITERAL:%d.....%d\n", p->P->next_literalNode->literal_info, p->N->literal_info);
			break;
		case SPLIT:
			printf("SPLILT:%p\n", p->P);
			break;
		default:
			break;
		}
		p = p->next;
	}
	return OK;
}

Status Destroy_Set(cnf_set * S)
{
	if (!S) {
		return ERROR;
	}
	while (S->clause_num != 0)
		deleteClause(S, S->set);
	return OK;
}


//DPLL
Status literal_Assign(cnf_set * S, int literal)//存储变元赋值
{
	S->literal_bool[abs(literal)] = (literal > 0 ? 1 : -1);//记录到数组
	return OK;
}

Status literal_back(cnf_set *S, int * tag) {//变元的赋值回溯
	int i;
	for (i = 1; i <= S->literal_num; i++)
		if (tag[i] == UNSURE)//回溯
			S->literal_bool[i] = 0;
	return OK;
}

Status change_back(cnf_set *S, stack_i * t) {//子句还原
	stack_i * p = t->next;
	while (p) {
		switch (p->flag) {
		case CLAUSE:
			addClause(p->P, S);
			break;
		case LITERAL:
			addliteral(p->P, p->N->literal_info);
			break;
		case SPLIT:
			break;
		default:
			break;
			p = t->next;
		}
		t->next = t->next->next;
		free(p);
		p = t->next;
	}
	return OK;
}

Status DPLL_rec(cnf_set * S) {
	First_Node * p;
	stack_i t;
	int literal_v;
	//static int literal_back_tag[MAX_LITERAL];
	int *literal_back_tag = (int*)malloc(sizeof(int)*(S->literal_num + 1));//存储子句回溯信息
	if (literal_back_tag == NULL)exit(-1);
	int i;
	for (i = 0; i <= S->literal_num; i++)
		literal_back_tag[i] = 0;
	t.next = NULL;
#ifdef DEBUG1
	set_print(S);
}
#endif // DEBUG
while ((p = locateUnitClause(S)) != NULL) {
	literal_Assign(S, p->next_literalNode->literal_info);//保存变元,这里的变元得想办法赋值回去
	literal_back_tag[abs(p->next_literalNode->literal_info)] = UNSURE;
	//printf("\n子句集中单子句为:%d", p->next_literalNode->literal_info);
	Clause_simply(S, p->next_literalNode->literal_info, &t);//化简子句

	//printf("\n化简后为：\n");
	//set_print(S);
#ifdef DEBUG1
		//stack_print(&t);
		//booleanprint(S);
#endif // DEBUG
	if (isHaveClause(S) == FALSE) {//没有子句
		//set_print(S);
		change_back(S, &t);
		//set_print(S);
		return TRUE;
	}
	else if (isHaveEmptyClause(S) == TRUE) {//有空子句
		//stack_print(&t);
		//printf("回溯前:\n");
		//set_print(S);
		change_back(S, &t);
		//printf("回溯后的子句集合为：\n");
		//set_print(S);
		literal_back(S, literal_back_tag);//变元回溯
		return FALSE;
	}
}//While
//printf("\n");
//booleanprint(S);
literal_v = literal_chose(S);//选择变元
#ifdef DEBUG1
#endif // DEBUG1

	//printf("选取变元：%d\n", literal_v);

literal_Assign(S, literal_v);//保存变元
p = creatClause(&literal_v, 1);//创建子句
addClause(p, S);//添加子句
stack_push(&t, SPLIT, S->set, NULL);//把添加的子句压入栈，在回溯时需要销毁掉

//set_print(S);

//stack_print(&t);

#ifdef DEBUG1
	//printf("选择变元为：%d",literal_v);
	//printf("\n添加变元后为：\n");
	//set_print(S);
#endif // DEBUG

BOOL result = DPLL_rec(S);//递归
if (result == TRUE) {//如果是真
	deleteClause(S, stack_pop(&t));
	change_back(S, &t);
	//set_print(S);
	//printf("恢复后：\n");
	//set_print(S);
	return TRUE;
}

S->literal_bool[abs(literal_v)] = 0;
//booleanprint(S);

#ifdef DEBUG1
	//printf("\n栈：\n");
	//stack_print(&t);
#endif // DEBUG

literal_v = -literal_v;
//printf("\t选取新变元（反）：%d\n", literal_v);
literal_Assign(S, literal_v);//保存变元
p = creatClause(&literal_v, 1);
deleteClause(S, stack_pop(&t));
addClause(p, S);
//printf("旧的变元销毁后:\n");
//set_print(S);
stack_push(&t, SPLIT, S->set, NULL);
First_Node * temp = S->set;
//set_print(S);
result = DPLL_rec(S);//递归
change_back(S, &t);
//set_print(S);
deleteClause(S, temp);
//set_print(S);
//free(temp);
/*printf("回溯后的子句集：\n");
set_print(S);*/
if (result == FALSE) {
	literal_back(S, literal_back_tag);
	S->literal_bool[abs(literal_v)] = 0;
}
free(literal_back_tag);
return result;
}

Status DPLL_rec2(cnf_set * S) {//优化后的DPLL算法
	{
		First_Node * p;
		stack_i t;
		int literal_v;
		int *literal_back_tag = (int*)malloc(sizeof(int)*(S->literal_num + 1));//存储子句回溯信息
		if (literal_back_tag == NULL)exit(-1);
		int i;
		for (i = 0; i <= S->literal_num; i++)
			literal_back_tag[i] = 0;
		t.next = NULL;
		while ((p = locateUnitClause(S)) != NULL) {
			literal_Assign(S, p->next_literalNode->literal_info);//保存变元,这里的变元得想办法赋值回去
			literal_back_tag[abs(p->next_literalNode->literal_info)] = UNSURE;
			//printf("\n子句集中单子句为:%d", p->next_literalNode->literal_info);
			Clause_simply(S, p->next_literalNode->literal_info, &t);//化简子句
			if (isHaveClause(S) == FALSE) {//没有子句
				change_back(S, &t);
				return TRUE;
			}
			else if (isHaveEmptyClause(S) == TRUE) {//有空子句
				change_back(S, &t);
				literal_back(S, literal_back_tag);//变元回溯
				return FALSE;
			}
		}//While
		literal_v = literal_chose_better(S);//选择变元
		literal_Assign(S, literal_v);//保存变元
		p = creatClause(&literal_v, 1);//创建子句
		addClause(p, S);//添加子句
		stack_push(&t, SPLIT, S->set, NULL);//把添加的子句压入栈，在回溯时需要销毁掉
		BOOL result = DPLL_rec(S);//递归
		if (result == TRUE) {//如果是真
			deleteClause(S, stack_pop(&t));
			change_back(S, &t);
			return TRUE;
		}
		S->literal_bool[abs(literal_v)] = 0;
		literal_v = -literal_v;
		literal_Assign(S, literal_v);//保存变元
		p = creatClause(&literal_v, 1);
		deleteClause(S, stack_pop(&t));
		addClause(p, S);
		stack_push(&t, SPLIT, S->set, NULL);
		First_Node * temp = S->set;
		result = DPLL_rec(S);//递归
		change_back(S, &t);
		deleteClause(S, temp);
		if (result == FALSE) {
			literal_back(S, literal_back_tag);
			S->literal_bool[abs(literal_v)] = 0;
		}
		free(literal_back_tag);
		return result;
	}
}

Status booleanprint(cnf_set * S) {
	First_Node *p = S->set;
	int i;
	for (i = 1; i <= S->literal_num; i++)
		printf("%d:%d   ", i, S->literal_bool[i]);
	return OK;
}

Status counter_sort_strategy(cnf_set * S) {
	{
		int i;
		int max = 0;
		int index = 0;
		First_Node * Cp;
		literal_Node *Lp;
		int *visitedplus = (int*)malloc((S->literal_num + 1) * sizeof(int));
		if (visitedplus == NULL)exit(-1);
		int *visitedminus = (int*)malloc((S->literal_num + 1) * sizeof(int));
		if (visitedminus == NULL)exit(-1);
		for (i = 1; i <= S->literal_num; i++) {
			visitedplus[i] = visitedminus[i] = 0;
		}
		for (Cp = S->set; Cp; Cp = Cp->next_FirstNode) {
			for (Lp = Cp->next_literalNode; Lp; Lp = Lp->next_literalnode) {
				if (Lp->literal_info > 0) {
					visitedplus[Lp->literal_info]++;
				}
				else {
					visitedminus[0 - Lp->literal_info]++;
				}
			}
		}
		for (i = 1; i <= S->literal_num; i++)
			if (max < visitedplus[i] + visitedminus[i] && S->literal_bool[i] == 0) {
				max = visitedplus[i] + visitedminus[i];
				index = i;
			}

		index = (visitedplus[index] < visitedminus[index]) ? -index : index;
		free(visitedplus);
		free(visitedminus);
		return index;
	}
}

Status counter_sort_strategy_betweentwo(cnf_set * S) {
	int i;
	int flag = 0;//记录是否存在双变元子句，若不存在则返回0
	int max = 0;
	int index = 0;
	First_Node * Cp;
	literal_Node *Lp;
	for (Cp = S->set; Cp; Cp = Cp->next_FirstNode)
	{
		if (Cp->num == 2)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		return 0;
	int *visitedplus = (int*)malloc((S->literal_num + 1) * sizeof(int));
	if (visitedplus == NULL)exit(-1);
	int *visitedminus = (int*)malloc((S->literal_num + 1) * sizeof(int));
	if (visitedminus == NULL)exit(-1);
	for (i = 1; i <= S->literal_num; i++) {
		visitedplus[i] = visitedminus[i] = 0;
	}
	for (Cp = S->set; Cp&&Cp->num <= 2; Cp = Cp->next_FirstNode) {//改动地方
		for (Lp = Cp->next_literalNode; Lp; Lp = Lp->next_literalnode) {
			if (Lp->literal_info > 0) {
				visitedplus[Lp->literal_info]++;
			}
			else {
				visitedminus[0 - Lp->literal_info]++;
			}
		}
	}
	for (i = 1; i <= S->literal_num; i++)
		if (max < visitedplus[i] + visitedminus[i] && S->literal_bool[i] == 0) {
			max = visitedplus[i] + visitedminus[i];
			index = i;
		}

	index = (visitedplus[index] < visitedminus[index]) ? -index : index;
	free(visitedplus);
	free(visitedminus);
	return index;
}

int VSIDS_strategy(cnf_set *S)//VIDS 策略
{
	int i;
	static int count = 0;
	int max = 0;
	int index = 0;
	First_Node *Cp;
	literal_Node *Lp;
	int *visited_num = (int*)malloc((S->literal_num + 1) * sizeof(int));
	for (Cp = S->set; Cp; Cp = Cp->next_FirstNode) {
		for (Lp = Cp->next_literalNode; Lp; Lp = Lp->next_literalnode) {
			if (Lp->literal_info > 0) {
				visited_num[Lp->literal_info]++;
			}
			else {
				visited_num[-Lp->literal_info]++;
			}
		}
	}
	for (i = 1; i <= S->literal_num; i++) {
		if (max < visited_num[i] && S->literal_bool[i] == 0) {
			max = visited_num[i];
			index = i;
		}
	}
	count++;
	if (count > 10) {
		count = 0;
		for (i = 1; i <= S->literal_num; i++) {
			visited_num[i] /= 3;
		}
	}
	index = (count % 2) ? index : -index;
	return index;
}

int shortest_strategy(cnf_set *S) {//在最短的变元随便选一个
	if (!S) return 0;
	int index_num = 2;
	First_Node *p;
	while(TRUE)
	for (p = S->set; p; p->next_FirstNode)
		if (index_num = p->num)
		{
			return p->next_literalNode->literal_info;
		}
		else
			index_num++;
}

int literal_chose(cnf_set * S) {
	return counter_sort_strategy(S);
}

int literal_chose_better(cnf_set *S) {
#ifdef STRATEGY1
	int result = counter_sort_strategy_betweentwo(S);
	if (!result)
		return counter_sort_strategy(S);
	return result;
#endif // STRATEGY1
	
#ifdef STRATEGY2
	return VSIDS_strategy(S);
#endif // STRATEGY2

#ifdef STRATEGY3
	return shortest_strategy(S);
#endif // STRATEGY3
}

Status result_check(cnf_set *S) {//验证输出结果
	//set_print(S);
	int i, b;
	int flag;
	First_Node * Cp;
	literal_Node * Lp;
	printf("------------------------------------------------\n");
	printf("正在检查: \n");
	for (Cp = S->set, i = 1; Cp; Cp = Cp->next_FirstNode, i++) {
		printf("第%d个子句: ", i);
		for (Lp = Cp->next_literalNode, flag = 0; Lp; Lp = Lp->next_literalnode) {
			b = S->literal_bool[abs(Lp->literal_info)];
			if ((Lp->literal_info > 0 ? 1 : -1) == b) {
				printf("√");
				flag = 1;
				break;
			}
			else if (b == 0) {
				printf("%dNOTsure ", abs(Lp->literal_info));
			}
			else if ((Lp->literal_info > 0 ? 1 : -1) == -b) {
				continue;
			}
		}
		if (!flag) {
			printf("x");
		}
		printf("\n");
	}
	printf("\n");
	return OK;
}


//sudoku
Sudoku* createSudoku(int difficult)
{
	int i, j, t;
	int c, flag = 0;
	int x, y;
	srand(time(0));
	Sudoku *s = (Sudoku*)malloc(sizeof(Sudoku));
	Sudoku *ss = NULL;
	s->next = NULL;
	if (!s) {
		return NULL;
	}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			s->sdk[i][j] = 0;
		}
	}
	if (sudoku_rand(s, 0, 0) == TRUE) {//随机生成完整数独
		sudoku_print(s);
		for (c = 0; c < 3; c++) {//挖掉3个空
			x = rand() % 9;
			y = rand() % 9;
			s->sdk[x][y] = 0;
		}
		while (1) {
			sudoku_solve(s, &c);//求解该数独，得到解的个数c
			if (c > 1) {
				s->sdk[x][y] = t;
				flag++;
				if (flag >= difficult) {
					break;
				}
				for (ss = s->next; ss; ss = s->next) {
					s->next = ss->next;
					free(ss);
				}
			}
			else {
				do {
					x = rand() % 9;
					y = rand() % 9;
				} while (s->sdk[x][y] == 0);
				t = s->sdk[x][y];
				s->sdk[x][y] = 0;
			}
		}
		return s;
	}
	else {
		return NULL;
	}
}

BOOL sudoku_rand(Sudoku *s, int x, int y)
{
	int c = 0;
	s->sdk[x][y] = rand() % 9 + 1;
	do {
		do {
			c++;
			if (c > 9) {
				s->sdk[x][y] = 0;
				return FALSE;
			}
			s->sdk[x][y] = s->sdk[x][y] % 9 + 1;
		} while (judge_x_y(s, x, y) != TRUE);
		if (x == 8 && y == 8) {
			return TRUE;
		}
	} while (((y == 8) ? sudoku_rand(s, x + 1, 0) : sudoku_rand(s, x, y + 1)) != TRUE);
	return TRUE;
}

Status SudokuToCNF(Sudoku *s)
{
	int i, j, k, t;
	FILE  *fp;
	if ((fp = fopen("sudoku.cnf", "w")) == NULL)
	{
		printf("File open error\n ");
	}
	for (t = 0, i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (s->sdk[i][j]) t++;
		}
	}
	//将数独变为cnf公式保存在sudoku.cnf文件中
	fprintf(fp, "p cnf 729 %d\n", t + 10530);
	for (i = 0; i < 9; i++) {//保存已经存在的数
		for (j = 0; j < 9; j++) {
			if (k = s->sdk[i][j]) {
				fprintf(fp, "%d 0\n", 81 * i + 9 * j + k);
			}
		}
	}
	for (i = 1; i < 10; i++) {
		for (j = 1; j < 10; j++) {
			for (k = 1; k < 10; k++) {
				fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
			}
			fprintf(fp, "0\n");
		}
	}
	for (i = 1; i < 10; i++) {
		for (j = 1; j < 10; j++) {
			for (k = 1; k < 9; k++) {
				for (t = k + 1; t < 10; t++) {
					fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (i - 1) + 9 * (j - 1) + t);
				}
			}
		}
	}
	for (i = 1; i < 10; i++) {//对行处理，每一行一定存在1-9&&每一行不存在相同的数
		for (k = 1; k < 10; k++) {
			for (j = 1; j < 10; j++) {
				fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
			}
			fprintf(fp, "0\n");
		}
		for (k = 1; k < 10; k++) {
			for (j = 1; j < 9; j++) {
				for (t = j + 1; t < 10; t++) {
					fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (i - 1) + 9 * (t - 1) + k);
				}
			}
		}
	}
	for (j = 1; j < 10; j++) {//对列处理  方式同行
		for (k = 1; k < 10; k++) {
			for (i = 1; i < 10; i++) {
				fprintf(fp, "%d ", 81 * (i - 1) + 9 * (j - 1) + k);
			}
			fprintf(fp, "0\n");
		}
		for (k = 1; k < 10; k++) {
			for (i = 1; i < 9; i++) {
				for (t = i + 1; t < 10; t++) {
					fprintf(fp, "-%d ", 81 * (i - 1) + 9 * (j - 1) + k);
					fprintf(fp, "-%d 0\n", 81 * (t - 1) + 9 * (j - 1) + k);
				}
			}
		}
	}
	int m, n;
	for (m = 0; m < 3; m++) {
		for (n = 0; n < 3; n++) {
			for (k = 1; k < 10; k++) {
				for (i = 1; i < 4; i++) {
					for (j = 1; j < 4; j++) {
						fprintf(fp, "%d ", 81 * ((i - 1) + 3 * m) + 9 * ((j - 1) + 3 * n) + k);
					}
				}
				fprintf(fp, "0\n");
			}
			for (k = 1; k < 10; k++) {
				i = 1;
				j = 1;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j + 1) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j + 1) + k);
				j = 2;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 2) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j) + k);
				j = 3;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 1 - 2) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 1 - 1) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 3) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i + 1) + 9 * (3 * n + j - 2) + k);
				i = 2;
				j = 1;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j + 1) + k);
				j = 2;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j) + k);
				j = 3;
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 3) + k);
				fprintf(fp, "-%d ", 81 * (3 * m + i - 1) + 9 * (3 * n + j - 1) + k);
				fprintf(fp, "-%d 0\n", 81 * (3 * m + i) + 9 * (3 * n + j - 2) + k);
			}
		}
	}
	fclose(fp);
	return OK;
}

Sudoku *CNFToSudoku(cnf_set *S) {
	Sudoku *s = (Sudoku*)malloc(sizeof(Sudoku));
	s->next = NULL;
	int i, j, k;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			for (k = 1; k <= 9; k++) {
				if (S->literal_bool[LOC(i, j, k)] == TRUE) {
					s->sdk[i][j] = k;
				}
			}
		}
	}
	return s;
}

BOOL sudoku_check(Sudoku *s)
{
	int i, j, k, l;
	int flag = 0;
	int b[9];//记录出现次数
	/*横向检查*/
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			b[j] = 0;
		}
		for (j = 0; j < 9; j++) {
			if (!s->sdk[i][j]) {
				flag = 1;
			}
			else if (b[s->sdk[i][j] - 1] == 0) {
				b[s->sdk[i][j] - 1] = 1;//数字sdk[i][j]已出现
			}
			else {
				return FALSE;
			}
		}
	}
	/*纵向检查*/
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			b[j] = 0;
		}
		for (j = 0; j < 9; j++) {
			if (!s->sdk[j][i]) {
				flag = 1;
			}
			else if (b[s->sdk[j][i] - 1] == 0) {
				b[s->sdk[j][i] - 1] = 1;
			}
			else {
				return FALSE;
			}
		}
	}
	/*九格检查*/
	for (i = 0; i < 9; i += 3) {
		for (j = 0; j < 9; j += 3) {
			for (k = 0; k < 9; k++) {
				b[k] = 0;
			}
			for (k = i; k < i + 3; k++) {
				for (l = j; l < j + 3; l++) {
					if (s->sdk[k][l] == 0) {
						flag = 1;
					}
					else if (b[s->sdk[k][l] - 1] == 0) {
						b[s->sdk[k][l] - 1] = 1;
					}
					else {
						return FALSE;
					}
				}
			}
		}
	}
	return (flag) ? UNSURE : TRUE;
}

BOOL judge_x_y(Sudoku *s, int x, int y)
{
	int i, j;

	for (i = 0; i < 9; i++) {
		if (s->sdk[i][y] == s->sdk[x][y] && i != x) {
			return FALSE;
		}

	}
	for (i = 0; i < 9; i++) {
		if (s->sdk[x][i] == s->sdk[x][y] && i != y) {
			return FALSE;
		}

	}
	for (i = x / 3 * 3; i < x / 3 * 3 + 3; i++) {
		for (j = y / 3 * 3; j < y / 3 * 3 + 3; j++) {
			if (s->sdk[i][j] == s->sdk[x][y] && (i != x || j != y)) {
				return FALSE;
			}

		}
	}
	return TRUE;
}//1

BOOL sudoku_solve(Sudoku *s, int *solvecount)
{
	*solvecount = 0;
	sudoku_dfs(s, 0, 0, solvecount);
	return (solvecount > 0) ? TRUE : FALSE;
}

BOOL sudoku_dfs(Sudoku *s, int x, int y, int *solvecount)
{
	int i, j, k;
	Sudoku *ss;
	while (s->sdk[x][y] != 0 && x <= 8) {
		y++;
		if (y == 9) {
			x += 1;
			y = 0;
		}
	}
	if (x > 8) {
		ss = (Sudoku*)malloc(sizeof(Sudoku));
		for (j = 0; j < 9; j++) {
			for (k = 0; k < 9; k++) {
				ss->sdk[j][k] = s->sdk[j][k];
			}
		}
		ss->next = s->next;
		s->next = ss;
		(*solvecount)++;
		return TRUE;
	}
	for (i = 1; i <= 9; i++) {
		s->sdk[x][y] = i;
		switch (judge_x_y(s, x, y))
		{
		case FALSE:
			break;
		case TRUE:
			if (x == 8 && y == 8) {
				ss = (Sudoku*)malloc(sizeof(Sudoku));
				for (j = 0; j < 9; j++) {
					for (k = 0; k < 9; k++) {
						ss->sdk[j][k] = s->sdk[j][k];
					}
				}
				ss->next = s->next;
				s->next = ss;
				s->sdk[x][y] = 0;
				(*solvecount)++;
				return TRUE;
			}
			else {
				(y == 8) ? sudoku_dfs(s, x + 1, 0, solvecount) : sudoku_dfs(s, x, y + 1, solvecount);
			}
			break;
		default:
			break;
		}
	}
	s->sdk[x][y] = 0;
	return FALSE;
}

Status sudoku_print(Sudoku *s)
{
	int i, j;
	printf("数独为:\n");
	for (j = 0; j < 19; j++) {
		printf("-");
	}
	printf("\n");
	for (i = 0; i < 9; i++) {
		printf("|");
		for (j = 0; j < 9; j++) {
			printf("%d%c", s->sdk[i][j], ((j + 1) % 3 == 0) ? '|' : ' ');
		}
		printf("\n");
		if ((i + 1) % 3 == 0) {
			printf("|");
			for (j = 0; j < 17; j++) {
				printf("-");
			}
			printf("|\n");
		}
	}
	return OK;
}


//display
void CNFPage()
{
	char cnf_path[256];
	char res_path[256];
	int is_load = 0;//记录是否已载入cnf
	int is_solved = 0;//记录是否求解
	int is_repeated = 0;//记录是否进行过优化率计算
	cnf_set *S = NULL;//总的结构体
	BOOL result = FALSE;
	BOOL result2 = FALSE;
	int  i,t1 ,t2;
	double rate = 0;
	int op = 1;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("---------------基于SAT的CNF程序菜单-------------\n");
		printf("-----------------------CNF----------------------\n");
		if (is_load)
			printf("当前加载文件: %s\n", cnf_path);
		printf("1. 加载CNF文件\n");
		printf("2. 求解CNF(dpll_rec_1)\n");
		printf("3. 求解CNF(dpll_rec_2)\n");
		printf("4. 打印CNF\n");
		printf("5. 打印答案\n");
		printf("6. 检查答案\n");
		printf("0. 返回\n");
		printf("------------------------------------------------\n");
		printf("请选择你的操作[0~4]: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			if (S != NULL) {
				Destroy_Set(S);
				S = NULL;
			}

			S = (cnf_set*)malloc(sizeof(cnf_set));
			for (i = 0; i <= MAX_LITERAL; i++)
				S->literal_bool[i] = 0;
			//printf("debug!");
			if (Create_Set(S, 1) == TRUE)
			{
				printf("CNF Load Sucessfully!\n");
				_getcwd(cnf_path, 256);//获取工作路径
				path_generate(cnf_path, filename);
				is_load = 1;
				is_solved = 0;
			}
			else
			{
				S = NULL;
				is_load = 0;
			}
			is_repeated = 0;
			getchar();
			getchar();
			break;
		case 2:
			if (S == NULL)
			{
				printf("CNF未加载!\n");
				getchar();
				getchar();
				break;
			}
			if (is_solved)
			{
				printf("已求解，请勿重复操作!\n");
				getchar();
				getchar();
				break;
			}
			t1 = clock();
			result = DPLL_rec(S);
			t1 = clock() - t1;
			is_solved = 1;
			//duration = (double)(finish - start) / CLOCKS_PER_SEC;
			if (result == TRUE)
			{
				printf("Satisfied！");
				//literal_print(S);
				//printf("\n\nDPLL_rec takes %f seconds\n", duration);
				printf("\nDPLL_rec1 takes %d ms\n", t1);
				CnfToRes_path(cnf_path, res_path);//生成cnf文件存储地址
				if (RES_save(res_path, result, S, t1)) {
					printf("RES保存成功!\n");
				}
				else {
					printf("RES保存失败!\n");
				}
			}
			else if (result == FALSE)
			{
				printf("Not Satisfied!\n");
				printf("DPLL_rec takes %d ms\n", t1);
				CnfToRes_path(cnf_path, res_path);//生成cnf文件存储地址
				if (RES_save(res_path, result, S, t1)) {
					printf("RES保存成功!\n");
				}
				else {
					printf("RES保存失败!\n");
				}
			}
			else
				printf("求解失败!\n");
			getchar();
			getchar();
			break;
		case 3:
			if (is_repeated)
			{		
				printf("已完成计算，请勿重复操作！\n");
				getchar();
				getchar();
				break;
			}
			if (!is_solved)
			{
				printf("请优先使用dpll_rec_1完成计算！\n");
				getchar();
				getchar();
				break;
			}
			else
			{
				Destroy_Set(S);
				S = NULL;
			}
			S = (cnf_set*)malloc(sizeof(cnf_set));
			for (i = 0; i <= MAX_LITERAL; i++)
				S->literal_bool[i] = 0;
			if (Create_Set(S, 3) == TRUE);
			is_repeated = 1;
			t2 = clock();
			result2 = DPLL_rec2(S);
			t2 = clock() - t2;
			if (result2 == TRUE)
			{
				printf("Satisfied！\n");
				printf("DPLL_rec1 takes %d ms\n", t1);
				printf("DPLL_rec2 takes %d ms\n", t2);
				rate = (float)(t1 - t2)/ t1;
				printf("优化率为:%%%f\n", rate*100);
			}
			else if (result2 == FALSE)
			{
				printf("Not Satisfied!\n");
				printf("DPLL_rec1 takes %d ms\n", t1);
				printf("DPLL_rec2 takes %d ms\n", t2);
				rate = float(t1 - t2) / t1;
				printf("优化率为:%%%f\n", rate*100);
			}
			else
				printf("求解失败!\n");
			getchar();
			getchar();
			break;
		case 4:
			if (S == NULL)
			{
				printf("CNF文件未加载!\n");
				getchar();
				getchar();
				break;
			}
			set_print(S);
			printf("打印完成!\n");
			getchar();
			getchar();
			break;
		case 5:
			if (S == NULL)
			{
				printf("CNF文件未加载!\n");
				getchar();
				getchar();
				break;
			}
			if (!is_solved)
			{
				printf("未求解！\n");
				getchar();
				getchar();
				break;
			}
			if (result == TRUE)
			{
				printf("Satisfied！\n");
				literal_print(S);
			}
			else if (result == FALSE)
				printf("Not Satisfied!\n");
			else
				printf("求解失败!\n");
			getchar();
			getchar();
			break;
		case 6:
			if (S == NULL)
			{
				printf("CNF文件未加载!\n");
				getchar();
				getchar();
				break;
			}
			if (!is_solved)
			{
				printf("未求解！\n");
				getchar();
				getchar();
				break;
			}
			//result_check(S);
			set_print_check(S);
			getchar();
			getchar();
			break;
		case 0:
			break;
		}
	}
	if (S) {
		Destroy_Set(S);
		S = NULL;
		is_load = 0;
	}
}

void sudokuPage()
{
	int t, i, k;
	int is_exist = 0;
	int dpll;
	int op = 1;
	char path[256];
	cnf_set * S = NULL;
	S = (cnf_set*)malloc(sizeof(cnf_set));
	for (i = 0; i <= MAX_LITERAL; i++)
		S->literal_bool[i] = 0;
	Sudoku *s = (Sudoku *)malloc(sizeof(Sudoku));
	s->next = NULL;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("-------------基于SAT的CNF程序菜单---------------\n\n");
		printf("---------------------数独-----------------------\n");
		printf("1. 生成数独(重复操作可生成新数独)\n");
		printf("2. 生成数独求解\n");
		printf("0. 回退\n");
		printf("------------------------------------------------\n");
		printf("请选择你的操作[0~2]: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			if (!(s = createSudoku(20))) {
				printf("数独生成失败！\n");
			}
			else {
				printf("数独生成成功!\n");
				is_exist = 1;
				sudoku_print(s);
				printf("------------------------------------------------\n");
			}
			getchar();
			getchar();
			break;
		case 2: {
			printf("数独为:\n");
			sudoku_print(s);
			printf("\n正在求解...\n");
			t = clock();
			Status result = SudokuToCNF(s);
			if (result) {
				Create_Set(S, 2);
				dpll = DPLL_rec(S);
				if (dpll == TRUE) {
					t = clock() - t;
					printf("该CNF成功解出!\n");
					Sudoku *ss = NULL;
					ss = CNFToSudoku(S);
					sudoku_print(ss);
					free(ss);
					printf("The process takes %dms\n", t);
				}
				Destroy_Set(S);
				S = NULL;
			}
			getchar();
			getchar();
			break;
		}
		case 0:
			break;
		}
	}
}

void main()
{
	int op = 1;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("---------------基于SAT的CNF程序菜单-------------\n");
		printf("------------------------------------------------\n");
		printf("1. CNF文件\n");
		printf("2. 数独游戏\n");
		printf("0. 退出\n");
		printf("------------------------------------------------\n");
		printf("请选择你的操作[0~2]: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			CNFPage();
			getchar();
			getchar();
			break;
		case 2:
			sudokuPage();
			getchar();
			getchar();
			break;
		case 0:
			break;
		}
	}
	printf("欢迎下次使用本系统！\n");
	getchar();
	getchar();
	return;
}

Status CnfToRes_path(char *cnf_path, char *res_path) {//生成res文件存储地址
	int i = 0;
	while (cnf_path[i] != '\0')
	{
		res_path[i] = cnf_path[i];
		i++;
	}
	res_path[i] = '\0';
	i -= 3;
	res_path[i++] = 'r';
	res_path[i++] = 'e';
	res_path[i] = 's';
	return OK;
}

Status path_generate(char *res_path, char *filename) {

	char temp[2];
	temp[0] = '\\';
	temp[1] = '\0';
	strcat(res_path, temp);
	strcat(res_path, filename);
	return OK;
}

Status RES_save(char *res_path, BOOL DPLL, cnf_set *s, int time) {
	int i;
	FILE *fp = fopen(res_path, "w");
	if (!fp) {
		return ERROR;
	}
	if (DPLL == TRUE)
		fprintf(fp, "s 1\n");
	if (DPLL == FALSE)
		fprintf(fp, "s 0\n");
	fprintf(fp, "v");
	for (i = 1; i <= s->literal_num; i++) {
		fprintf(fp, " %d", s->literal_bool[i] * i);
	}
	fprintf(fp, "\nt %d", time);
	fclose(fp);
	return OK;

}

Status CNF_save(cnf_set* s, char *cnf_Path) {
	FILE *fP = fopen(cnf_Path, "w");
	First_Node * P;
	literal_Node *N;
	if (!fP) {
		return ERROR;
	}
	fprintf(fP, "p cnf %d %d\n", s->literal_num, s->clause_num);
	for (P = s->set; P; P = P->next_FirstNode) {
		for (N = P->next_literalNode; N; N = N->next_literalnode) {
			fprintf(fP, "%d ", N->literal_info);
		}
		fprintf(fP, "0\n");
	}
	fclose(fP);
	return OK;
}