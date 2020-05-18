#include <stdio.h>
#include <time.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include <direct.h>

//#define DEBUG
#define STRATEGY1

char filename[256];

#define MAX_LITERAL 1000//����Ԫ��Ŀ
#define LINE 1024 //��ȡһ�е�����ַ���

#define ERROR -1//�쳣����״̬
#define OK 1//��������״̬����
#define TRUE 1
#define FALSE -1

#define MAX_CLAUSE_LENGTH 30
#define CLAUSE 1
#define LITERAL 2
#define SPLIT 3
#define UNSURE -2

#define LOC(i,j,x) ((i)*81+(j)*9+(x))

typedef int InfoType;
typedef int Status;//�����ķ���״̬
typedef int BOOL;


typedef struct First_Node {//�׽��Ľṹ
	int num; //��¼���Ӿ��б�Ԫ�ĸ���
	struct literal_Node *next_literalNode;// ָ���Ӿ�����һ��Ԫ���
	struct First_Node *next_FirstNode;//ָ����һ�Ӿ���׽ڵ�
	struct First_Node *prev_FirstNode;//ָ����һ�Ӿ���׽ڵ�
}First_Node;

typedef struct literal_Node {//��Ԫ�ڵ�Ľṹ
	InfoType literal_info; //��Ԫ��Ϣ
	struct literal_Node *next_literalnode;//ָ���Ӿ�����һ��Ԫ���
}literal_Node;

typedef struct cnf_set { //�ܵĽṹ��
	int literal_num;//��Ԫ����
	//int literal_num_init;//�����Ԫ����
	int clause_num;//�Ӿ����
	First_Node * set;//�Ӿ�ļ���
	int literal_bool[MAX_LITERAL];//��¼��Ӧ��ű�Ԫ�����,1Ϊ�棬-1Ϊ�٣�0Ϊδ֪
}cnf_set;

//typedef struct Clause {//�Ӿ�ṹ
//	//int isexist=0;//�ж��Ӿ��Ƿ����
//	int literalnum;//��Ԫ��Ŀ
//	int newclause[MAX_CLAUSE_LENGTH];//��¼��Ԫ���
//	int clauseboolean[MAX_CLAUSE_LENGTH];//��¼��Ԫ����,1Ϊ����-1Ϊ��
//}Clause;

typedef struct Sudoku {
	int sdk[9][9];
	Sudoku *next;
}Sudoku;

typedef struct stack_i {//ջ�ṹ
	int flag;//ѹջ�����־
	literal_Node * N;
	First_Node * P;
	stack_i * next;
}stack_i;

//cnf_parser.h
Status Create_Set(cnf_set *, int);//�����Ӿ伯

Status set_print(cnf_set *);//��ӡ����

Status set_print_check(cnf_set *);//������

Status stack_push(stack_i *, int, First_Node *, literal_Node *);//��ջ

First_Node * stack_pop(stack_i *);//��ջ

//Status stack_free(stack_i *);//ջ�ͷ�

First_Node * creatClause(int *, int);//�����Ӿ�/1

Status addClause(First_Node *, cnf_set *);//�����Ӿ�/1

First_Node * removeClause(cnf_set *, First_Node *);//ɾ���Ӿ䣬�������ַ/1

Status deleteClause(cnf_set *, First_Node *);//�����Ӿ�/1

Status addliteral(First_Node *, int);//��ĳһ�Ӿ������ӱ�Ԫ/1

literal_Node * removeliteral(First_Node *, int);//��ĳһ�Ӿ���ɾ����Ԫ

Status deleteLiteral(First_Node *, int);//����һ���Ӿ��еı�Ԫ

BOOL isUnitClause(First_Node *);//�ж��Ƿ�Ϊ���Ӿ�/1

Status evaluateClause(First_Node *, int);//�Ӿ�����/1

BOOL isHaveEmptyClause(cnf_set *);//�Ƿ��п��Ӿ�/1

BOOL isHaveClause(cnf_set *);//�Ӿ伯�Ƿ�Ϊ��/1

Status Clause_simply(cnf_set *, int, stack_i *);//���Ӿ仯��

First_Node * locateUnitClause(cnf_set *);//��λ���Ӿ�

Status stack_print(stack_i *);//��ӡջ

Status Destroy_Set(cnf_set * S);//���ټ���




//DPLL.h
Status literal_Assign(cnf_set *, int);//�洢��Ԫ��ֵ

Status literal_back(cnf_set *, int *);//��Ԫ�ĸ�ֵ���л��ݣ�

Status change_back(cnf_set *, stack_i *); //�Ӿ伯�ϻ�ԭ

int literal_chose(cnf_set *);

int literal_chose_better(cnf_set *);//�Ż���ı�Ԫѡ�񷽰�

Status counter_sort_strategy(cnf_set *);//���ݱ�Ԫ���ֵĴ�������ѡ��Ԫ

Status counter_sort_strategy_betweentwo(cnf_set *);//�ڱ�Ԫ��С��2���Ӿ���ͳ�Ʊ�Ԫ����

int VSIDS_strategy(cnf_set *);//VSIDS ����

Status DPLL_rec(cnf_set *);

Status DPLL_rec2(cnf_set *);//�Ż����DPLL�㷨

Status booleanprint(cnf_set *);

Status result_check(cnf_set *);//��֤������


//Sudoku
Sudoku* createSudoku(int);//��������

Status SudokuToCNF(Sudoku *);//ת����CNF��ʽ

Sudoku *CNFToSudoku(cnf_set *);//CNFת��������

BOOL sudoku_check(Sudoku *);//�Ƿ�Ϻ�����

BOOL judge_x_y(Sudoku *, int, int);//���������Ƿ���ȷ

BOOL sudoku_rand(Sudoku *, int, int);//������������ĵݹ麯��

BOOL sudoku_solve(Sudoku *, int *);//�������

BOOL sudoku_dfs(Sudoku *, int, int, int *);//DFS�������

Status sudoku_print(Sudoku *);//��ӡ����


//diaplay
void CNFPage();

void sudokuPage();

Status path_generate(char *savepath, char *cnfpath);//�ҵ���ǰ�Ĳ����ļ�

Status CnfToRes_path(char *, char *);//����res�ļ��洢��ַ

Status RES_save(char *respath, BOOL DPLL, cnf_set *s, int time);//������

Status CNF_save(cnf_set* s, char *cnf_path);//��������


//cnf_parser
Status literal_print(cnf_set *);//��Ԫ��ӡ

Status Create_Set(cnf_set *S, int tag) {//�������ϵĽṹ��
	//if (tag == 1) {//tag == 1 ��ʾ��ȡcnf�ļ��������
	FILE *fp;//Ŀ���ļ�ָ��
	//int is_eof;//�ж��Ƿ��ȡ���ļ�β
	int is_first_line = 1;//�ж��Ƿ��ȡ���ǵ�һ��
	int m = 1;
	if (tag == 1) {
		printf("�����ļ����ƣ�");
		scanf("%s", filename);
	}
	else if (tag == 2) {
		strcpy(filename, "sudoku.cnf");
	}
	else if (tag == 3);
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("    	  �ļ���ʧ��!\n ");
		return ERROR;
	}
	printf("�ļ��򿪳ɹ���\n");
	char buff[10];
	char ch;
	//char c[10];
	//fscanf(fp, "%s", c);
	//while (strcmp(c, "c") == 0)//���˵�������c��ͷ��ע������
	//{
	//	fscanf(fp, "%s", c);
	//	if (strcmp(c, "p") == 0)
	//		break;//��Կ�ע�͵����
	//	else
	//	{
	//		fscanf(fp, "%*[^\n]%*c");//���У����ļ�ָ��������һ�еĿ�ͷ
	//		fscanf(fp, "%s", c);
	//	}
	//}
	while ((ch = fgetc(fp)) == 'c') {
		while ((ch = fgetc(fp)) != '\n');
	}
	//��Ԫ�����Լ��Ӿ������ȡ
	fscanf(fp, "%s", buff);//�˵�cnf
	fscanf(fp, "%s", buff);//���ַ�����ʽ��ȡ��Ԫ����
	S->literal_num = atoi(buff);//�ַ�->����
	//S->literal_num_init = S->literal_num;
	fscanf(fp, "%s", buff);//���ַ�����ʽ��ȡ�Ӿ����
	S->clause_num = atoi(buff);//�ַ�->����

#ifdef DEBUG
	printf("��Ԫ����Ϊ%d  �Ӿ����Ϊ%d\n", S->literal_num, S->clause_num);//......DEBUG......
#endif

//�Ӿ��ȡ������
	int i = 0;// ��¼�Ӿ��б�Ԫ�ĸ���
	First_Node *u, *v;//��ʱ����
	literal_Node *p, *q;//��ʱ����

	//��һ���Ӿ�
	S->set = (First_Node *)malloc(sizeof(First_Node));
	S->set->next_FirstNode = NULL;
	S->set->prev_FirstNode = NULL;
	p = (literal_Node *)malloc(sizeof(literal_Node));//��ȡ�Ӿ�ĵ�һ����Ԫ
	p->next_literalnode = NULL;
	S->set->next_literalNode = p;
	fscanf(fp, "%s", buff);
	p->literal_info = atoi(buff);//¼���Ԫ��Ϣ
	i = 1;

#ifdef DEBUG
	printf("%d  ", p->literal_info);//....DEBUG....
#endif

	while (TRUE) {//ͬһ�Ӿ�ĺ�����Ԫ
		fscanf(fp, "%s", buff);
		if (strcmp(buff, "0") == 0)
			break;//�жϵ�ǰ�Ӿ��Ƿ��ȡ���
		q = (literal_Node *)malloc(sizeof(literal_Node));
		q->next_literalnode = NULL;
		q->literal_info = atoi(buff);//¼���Ԫ��Ϣ
		i++;
		//����
		p->next_literalnode = q;
		p = q;

#ifdef DEBUG
		printf("%d ", p->literal_info);//......DEBUG......
#endif

	}
	S->set->num = i;//��¼�Ӿ��еı�Ԫ����
	//printf("�Ӿ��Ԫ����Ϊ%d\n", S->set->num);//....DEBUG....

	//�����Ӿ�
	while (m < S->clause_num/*&&(is_eof = fscanf(fp, "%s", buff)) != -1*/) {//�ж��Ƿ�����ļ�β
		v = (First_Node *)malloc(sizeof(First_Node));
		v->next_FirstNode = NULL;
		p = (literal_Node *)malloc(sizeof(literal_Node));//��ȡ�Ӿ�ĵ�һ����Ԫ
		p->next_literalnode = NULL;
		v->next_literalNode = p;
		fscanf(fp, "%s", buff);
		p->literal_info = atoi(buff);//¼���Ԫ��Ϣ
		i = 1;

#ifdef DEBUG
		printf("%d ", p->literal_info);//......DEBUG......
#endif

		while (TRUE) {//ͬһ�Ӿ�ĺ�����Ԫ
			fscanf(fp, "%s", buff);
			if (strcmp(buff, "0") == 0)
				break;//�жϵ�ǰ�Ӿ��Ƿ��ȡ���
			q = (literal_Node *)malloc(sizeof(literal_Node));
			q->next_literalnode = NULL;
			q->literal_info = atoi(buff);//¼���Ԫ��Ϣ
			i++;
			//��Ԫ�������
			p->next_literalnode = q;
			p = q;

#ifdef DEBUG	
			printf("%d ", p->literal_info);
#endif
		}
		v->num = i;

		//�׽ڵ�����
		if (is_first_line)//��һ����ڶ���
		{
			S->set->next_FirstNode = v;
			v->prev_FirstNode = S->set;
			u = v;
			is_first_line = 0;

#ifdef DEBUG
			printf("�Ӿ��Ԫ����Ϊ%d\n", S->set->num);//....DEBUG....
#endif			
		}
		else {//������
#ifdef DEBUG
			printf("�Ӿ��Ԫ����Ϊ%d\n", u->num);//....DEBUG....
#endif
			u->next_FirstNode = v;
			v->prev_FirstNode = u;
			u = v;
		}
		m++;
	}
	//}
	//else if (tag == 2) {//tag ==2 ��ʾ�����ռ��Ϻ��������ṹ����ת����
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
		printf("��Ԫ������%d\t", p->num);
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
		printf("��Ԫ������%d\t", p->num);
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
	//t�ǲ������ݵ�ͷ�ڵ�ָ��
	if (t == NULL) {
		return FALSE;
	}
	stack_i *new_room = (stack_i*)malloc(sizeof(stack_i));
	if (!new_room)
	{
		printf("ջ�����");
		exit(-1);
	}
	new_room->flag = flag;
	switch (flag)
	{
	case CLAUSE://�����Ӿ�
		new_room->P = P;//�����Ӿ�ĵ�ַ
		new_room->N = NULL;
		break;
	case LITERAL://ĳ����Ԫ
		new_room->P = P;//���������Ӿ��ַ
		new_room->N = N;//����ñ�Ԫ
		break;
	case SPLIT://��ӵĵ��Ӿ��Ԫ
		new_room->P = P;//���������Ӿ��ַ
		new_room->N = NULL;//����ñ�Ԫ
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

//Status stack_free(stack_i * t) {//ջ�ͷ�
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

First_Node * creatClause(int *x, int num) {//�����Ӿ�
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

Status addClause(First_Node * P, cnf_set * S) {//�����Ӿ�
	if (S->set) {
		S->set->prev_FirstNode = P;
	}
	P->next_FirstNode = S->set;
	P->prev_FirstNode = NULL;

	S->set = P;
	S->clause_num++;
	return OK;
}

Status addliteral(First_Node *P, int literal) {//��ĳһ�Ӿ�ͷ�����ӱ�Ԫlilteral
	literal_Node *p = (literal_Node*)malloc(sizeof(literal_Node));
	p->literal_info = literal;
	p->next_literalnode = P->next_literalNode;
	P->next_literalNode = p;
	P->num++;
	return OK;
}

First_Node * removeClause(cnf_set * S, First_Node * N) {//ɾ���Ӿ�,�������ַ
	First_Node *p = N->prev_FirstNode;
	if (N->next_FirstNode)
		N->next_FirstNode->prev_FirstNode = p;
	if (p)
		p->next_FirstNode = N->next_FirstNode;
	else//NΪ��һ���Ӿ�
		S->set = N->next_FirstNode;
	S->clause_num--;
	return N;
}

Status deleteClause(cnf_set * S, First_Node * P) {//�����Ӿ�/
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

literal_Node * removeliteral(First_Node * P, int literal) {//��ĳһ�Ӿ���ɾ����Ԫ
	literal_Node *p, *q = NULL;
	for (p = P->next_literalNode; p; p = p->next_literalnode) {
		if (p->literal_info == literal) {
			P->num--;
			if (!q) {//��Ե�һ���ڵ�ƥ��ɹ������
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

Status deleteLiteral(First_Node * P, int literal) {//ɾ��һ���Ӿ��еı�Ԫ
	literal_Node *p, *q = NULL;
	for (p = P->next_literalNode; p; p = p->next_literalnode) {
		if (p->literal_info == literal) {
			P->num--;
			if (!q) {//��Ե�һ���ڵ�ƥ��ɹ������
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

BOOL isUnitClause(First_Node * p) {//�ж��Ƿ�Ϊ���Ӿ�
	return  (p->num == 1) ? TRUE : FALSE;
}

Status evaluateClause(First_Node * P, int literal)//�Ӿ�����
{
	literal_Node *p = P->next_literalNode;
	//int i = 0;
	for (; p; p = p->next_literalnode) {
		if (literal == p->literal_info) {
			return TRUE;//�Ӿ�Ϊ��
		}
		else if (-literal == p->literal_info) {
			return UNSURE;//��ȷ��
		}
	}
	return UNSURE;
}

BOOL isHaveEmptyClause(cnf_set *S) {//�Ƿ��п��Ӿ�
	First_Node *p;
	for (p = S->set; p; p = p->next_FirstNode) {
		if (!(p->num)) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL isHaveClause(cnf_set * S) {//�Ӿ伯�Ƿ�Ϊ��
	return  (S->set) ? TRUE : FALSE;
}

Status Clause_simply(cnf_set * S, int literal, stack_i *head) {//���Ӿ���򻯼�
	//set_print(S);
	literal_Node * N;
	First_Node * P = S->set;
	First_Node * q;
	while (P) {
		switch (evaluateClause(P, literal))
		{
		case TRUE:
			removeClause(S, P);
			stack_push(head, CLAUSE, P, NULL);//���Ӿ�
			P = P->next_FirstNode;
			break;
		case UNSURE://�Ƴ��Ӿ���ѡ����Ԫ�ķ�
			N = removeliteral(P, -literal);
			if (N != NULL)
				stack_push(head, LITERAL, P, N);//���Ԫ
			P = P->next_FirstNode;
			break;
		default:
			P = P->next_FirstNode;
			break;
		}
	}
	return OK;
}

First_Node * locateUnitClause(cnf_set * S) {//��λ���Ӿ�
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
	printf("ջΪ��\n");
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
Status literal_Assign(cnf_set * S, int literal)//�洢��Ԫ��ֵ
{
	S->literal_bool[abs(literal)] = (literal > 0 ? 1 : -1);//��¼������
	return OK;
}

Status literal_back(cnf_set *S, int * tag) {//��Ԫ�ĸ�ֵ����
	int i;
	for (i = 1; i <= S->literal_num; i++)
		if (tag[i] == UNSURE)//����
			S->literal_bool[i] = 0;
	return OK;
}

Status change_back(cnf_set *S, stack_i * t) {//�Ӿ仹ԭ
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
	int *literal_back_tag = (int*)malloc(sizeof(int)*(S->literal_num + 1));//�洢�Ӿ������Ϣ
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
	literal_Assign(S, p->next_literalNode->literal_info);//�����Ԫ,����ı�Ԫ����취��ֵ��ȥ
	literal_back_tag[abs(p->next_literalNode->literal_info)] = UNSURE;
	//printf("\n�Ӿ伯�е��Ӿ�Ϊ:%d", p->next_literalNode->literal_info);
	Clause_simply(S, p->next_literalNode->literal_info, &t);//�����Ӿ�

	//printf("\n�����Ϊ��\n");
	//set_print(S);
#ifdef DEBUG1
		//stack_print(&t);
		//booleanprint(S);
#endif // DEBUG
	if (isHaveClause(S) == FALSE) {//û���Ӿ�
		//set_print(S);
		change_back(S, &t);
		//set_print(S);
		return TRUE;
	}
	else if (isHaveEmptyClause(S) == TRUE) {//�п��Ӿ�
		//stack_print(&t);
		//printf("����ǰ:\n");
		//set_print(S);
		change_back(S, &t);
		//printf("���ݺ���Ӿ伯��Ϊ��\n");
		//set_print(S);
		literal_back(S, literal_back_tag);//��Ԫ����
		return FALSE;
	}
}//While
//printf("\n");
//booleanprint(S);
literal_v = literal_chose(S);//ѡ���Ԫ
#ifdef DEBUG1
#endif // DEBUG1

	//printf("ѡȡ��Ԫ��%d\n", literal_v);

literal_Assign(S, literal_v);//�����Ԫ
p = creatClause(&literal_v, 1);//�����Ӿ�
addClause(p, S);//����Ӿ�
stack_push(&t, SPLIT, S->set, NULL);//����ӵ��Ӿ�ѹ��ջ���ڻ���ʱ��Ҫ���ٵ�

//set_print(S);

//stack_print(&t);

#ifdef DEBUG1
	//printf("ѡ���ԪΪ��%d",literal_v);
	//printf("\n��ӱ�Ԫ��Ϊ��\n");
	//set_print(S);
#endif // DEBUG

BOOL result = DPLL_rec(S);//�ݹ�
if (result == TRUE) {//�������
	deleteClause(S, stack_pop(&t));
	change_back(S, &t);
	//set_print(S);
	//printf("�ָ���\n");
	//set_print(S);
	return TRUE;
}

S->literal_bool[abs(literal_v)] = 0;
//booleanprint(S);

#ifdef DEBUG1
	//printf("\nջ��\n");
	//stack_print(&t);
#endif // DEBUG

literal_v = -literal_v;
//printf("\tѡȡ�±�Ԫ��������%d\n", literal_v);
literal_Assign(S, literal_v);//�����Ԫ
p = creatClause(&literal_v, 1);
deleteClause(S, stack_pop(&t));
addClause(p, S);
//printf("�ɵı�Ԫ���ٺ�:\n");
//set_print(S);
stack_push(&t, SPLIT, S->set, NULL);
First_Node * temp = S->set;
//set_print(S);
result = DPLL_rec(S);//�ݹ�
change_back(S, &t);
//set_print(S);
deleteClause(S, temp);
//set_print(S);
//free(temp);
/*printf("���ݺ���Ӿ伯��\n");
set_print(S);*/
if (result == FALSE) {
	literal_back(S, literal_back_tag);
	S->literal_bool[abs(literal_v)] = 0;
}
free(literal_back_tag);
return result;
}

Status DPLL_rec2(cnf_set * S) {//�Ż����DPLL�㷨
	{
		First_Node * p;
		stack_i t;
		int literal_v;
		int *literal_back_tag = (int*)malloc(sizeof(int)*(S->literal_num + 1));//�洢�Ӿ������Ϣ
		if (literal_back_tag == NULL)exit(-1);
		int i;
		for (i = 0; i <= S->literal_num; i++)
			literal_back_tag[i] = 0;
		t.next = NULL;
		while ((p = locateUnitClause(S)) != NULL) {
			literal_Assign(S, p->next_literalNode->literal_info);//�����Ԫ,����ı�Ԫ����취��ֵ��ȥ
			literal_back_tag[abs(p->next_literalNode->literal_info)] = UNSURE;
			//printf("\n�Ӿ伯�е��Ӿ�Ϊ:%d", p->next_literalNode->literal_info);
			Clause_simply(S, p->next_literalNode->literal_info, &t);//�����Ӿ�
			if (isHaveClause(S) == FALSE) {//û���Ӿ�
				change_back(S, &t);
				return TRUE;
			}
			else if (isHaveEmptyClause(S) == TRUE) {//�п��Ӿ�
				change_back(S, &t);
				literal_back(S, literal_back_tag);//��Ԫ����
				return FALSE;
			}
		}//While
		literal_v = literal_chose_better(S);//ѡ���Ԫ
		literal_Assign(S, literal_v);//�����Ԫ
		p = creatClause(&literal_v, 1);//�����Ӿ�
		addClause(p, S);//����Ӿ�
		stack_push(&t, SPLIT, S->set, NULL);//����ӵ��Ӿ�ѹ��ջ���ڻ���ʱ��Ҫ���ٵ�
		BOOL result = DPLL_rec(S);//�ݹ�
		if (result == TRUE) {//�������
			deleteClause(S, stack_pop(&t));
			change_back(S, &t);
			return TRUE;
		}
		S->literal_bool[abs(literal_v)] = 0;
		literal_v = -literal_v;
		literal_Assign(S, literal_v);//�����Ԫ
		p = creatClause(&literal_v, 1);
		deleteClause(S, stack_pop(&t));
		addClause(p, S);
		stack_push(&t, SPLIT, S->set, NULL);
		First_Node * temp = S->set;
		result = DPLL_rec(S);//�ݹ�
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
	int flag = 0;//��¼�Ƿ����˫��Ԫ�Ӿ䣬���������򷵻�0
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
	for (Cp = S->set; Cp&&Cp->num <= 2; Cp = Cp->next_FirstNode) {//�Ķ��ط�
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

int VSIDS_strategy(cnf_set *S)//VIDS ����
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

int shortest_strategy(cnf_set *S) {//����̵ı�Ԫ���ѡһ��
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

Status result_check(cnf_set *S) {//��֤������
	//set_print(S);
	int i, b;
	int flag;
	First_Node * Cp;
	literal_Node * Lp;
	printf("------------------------------------------------\n");
	printf("���ڼ��: \n");
	for (Cp = S->set, i = 1; Cp; Cp = Cp->next_FirstNode, i++) {
		printf("��%d���Ӿ�: ", i);
		for (Lp = Cp->next_literalNode, flag = 0; Lp; Lp = Lp->next_literalnode) {
			b = S->literal_bool[abs(Lp->literal_info)];
			if ((Lp->literal_info > 0 ? 1 : -1) == b) {
				printf("��");
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
	if (sudoku_rand(s, 0, 0) == TRUE) {//���������������
		sudoku_print(s);
		for (c = 0; c < 3; c++) {//�ڵ�3����
			x = rand() % 9;
			y = rand() % 9;
			s->sdk[x][y] = 0;
		}
		while (1) {
			sudoku_solve(s, &c);//�����������õ���ĸ���c
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
	//��������Ϊcnf��ʽ������sudoku.cnf�ļ���
	fprintf(fp, "p cnf 729 %d\n", t + 10530);
	for (i = 0; i < 9; i++) {//�����Ѿ����ڵ���
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
	for (i = 1; i < 10; i++) {//���д���ÿһ��һ������1-9&&ÿһ�в�������ͬ����
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
	for (j = 1; j < 10; j++) {//���д���  ��ʽͬ��
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
	int b[9];//��¼���ִ���
	/*������*/
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			b[j] = 0;
		}
		for (j = 0; j < 9; j++) {
			if (!s->sdk[i][j]) {
				flag = 1;
			}
			else if (b[s->sdk[i][j] - 1] == 0) {
				b[s->sdk[i][j] - 1] = 1;//����sdk[i][j]�ѳ���
			}
			else {
				return FALSE;
			}
		}
	}
	/*������*/
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
	/*�Ÿ���*/
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
	printf("����Ϊ:\n");
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
	int is_load = 0;//��¼�Ƿ�������cnf
	int is_solved = 0;//��¼�Ƿ����
	int is_repeated = 0;//��¼�Ƿ���й��Ż��ʼ���
	cnf_set *S = NULL;//�ܵĽṹ��
	BOOL result = FALSE;
	BOOL result2 = FALSE;
	int  i,t1 ,t2;
	double rate = 0;
	int op = 1;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("---------------����SAT��CNF����˵�-------------\n");
		printf("-----------------------CNF----------------------\n");
		if (is_load)
			printf("��ǰ�����ļ�: %s\n", cnf_path);
		printf("1. ����CNF�ļ�\n");
		printf("2. ���CNF(dpll_rec_1)\n");
		printf("3. ���CNF(dpll_rec_2)\n");
		printf("4. ��ӡCNF\n");
		printf("5. ��ӡ��\n");
		printf("6. ����\n");
		printf("0. ����\n");
		printf("------------------------------------------------\n");
		printf("��ѡ����Ĳ���[0~4]: ");
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
				_getcwd(cnf_path, 256);//��ȡ����·��
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
				printf("CNFδ����!\n");
				getchar();
				getchar();
				break;
			}
			if (is_solved)
			{
				printf("����⣬�����ظ�����!\n");
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
				printf("Satisfied��");
				//literal_print(S);
				//printf("\n\nDPLL_rec takes %f seconds\n", duration);
				printf("\nDPLL_rec1 takes %d ms\n", t1);
				CnfToRes_path(cnf_path, res_path);//����cnf�ļ��洢��ַ
				if (RES_save(res_path, result, S, t1)) {
					printf("RES����ɹ�!\n");
				}
				else {
					printf("RES����ʧ��!\n");
				}
			}
			else if (result == FALSE)
			{
				printf("Not Satisfied!\n");
				printf("DPLL_rec takes %d ms\n", t1);
				CnfToRes_path(cnf_path, res_path);//����cnf�ļ��洢��ַ
				if (RES_save(res_path, result, S, t1)) {
					printf("RES����ɹ�!\n");
				}
				else {
					printf("RES����ʧ��!\n");
				}
			}
			else
				printf("���ʧ��!\n");
			getchar();
			getchar();
			break;
		case 3:
			if (is_repeated)
			{		
				printf("����ɼ��㣬�����ظ�������\n");
				getchar();
				getchar();
				break;
			}
			if (!is_solved)
			{
				printf("������ʹ��dpll_rec_1��ɼ��㣡\n");
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
				printf("Satisfied��\n");
				printf("DPLL_rec1 takes %d ms\n", t1);
				printf("DPLL_rec2 takes %d ms\n", t2);
				rate = (float)(t1 - t2)/ t1;
				printf("�Ż���Ϊ:%%%f\n", rate*100);
			}
			else if (result2 == FALSE)
			{
				printf("Not Satisfied!\n");
				printf("DPLL_rec1 takes %d ms\n", t1);
				printf("DPLL_rec2 takes %d ms\n", t2);
				rate = float(t1 - t2) / t1;
				printf("�Ż���Ϊ:%%%f\n", rate*100);
			}
			else
				printf("���ʧ��!\n");
			getchar();
			getchar();
			break;
		case 4:
			if (S == NULL)
			{
				printf("CNF�ļ�δ����!\n");
				getchar();
				getchar();
				break;
			}
			set_print(S);
			printf("��ӡ���!\n");
			getchar();
			getchar();
			break;
		case 5:
			if (S == NULL)
			{
				printf("CNF�ļ�δ����!\n");
				getchar();
				getchar();
				break;
			}
			if (!is_solved)
			{
				printf("δ��⣡\n");
				getchar();
				getchar();
				break;
			}
			if (result == TRUE)
			{
				printf("Satisfied��\n");
				literal_print(S);
			}
			else if (result == FALSE)
				printf("Not Satisfied!\n");
			else
				printf("���ʧ��!\n");
			getchar();
			getchar();
			break;
		case 6:
			if (S == NULL)
			{
				printf("CNF�ļ�δ����!\n");
				getchar();
				getchar();
				break;
			}
			if (!is_solved)
			{
				printf("δ��⣡\n");
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
		printf("-------------����SAT��CNF����˵�---------------\n\n");
		printf("---------------------����-----------------------\n");
		printf("1. ��������(�ظ�����������������)\n");
		printf("2. �����������\n");
		printf("0. ����\n");
		printf("------------------------------------------------\n");
		printf("��ѡ����Ĳ���[0~2]: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			if (!(s = createSudoku(20))) {
				printf("��������ʧ�ܣ�\n");
			}
			else {
				printf("�������ɳɹ�!\n");
				is_exist = 1;
				sudoku_print(s);
				printf("------------------------------------------------\n");
			}
			getchar();
			getchar();
			break;
		case 2: {
			printf("����Ϊ:\n");
			sudoku_print(s);
			printf("\n�������...\n");
			t = clock();
			Status result = SudokuToCNF(s);
			if (result) {
				Create_Set(S, 2);
				dpll = DPLL_rec(S);
				if (dpll == TRUE) {
					t = clock() - t;
					printf("��CNF�ɹ����!\n");
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
		printf("---------------����SAT��CNF����˵�-------------\n");
		printf("------------------------------------------------\n");
		printf("1. CNF�ļ�\n");
		printf("2. ������Ϸ\n");
		printf("0. �˳�\n");
		printf("------------------------------------------------\n");
		printf("��ѡ����Ĳ���[0~2]: ");
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
	printf("��ӭ�´�ʹ�ñ�ϵͳ��\n");
	getchar();
	getchar();
	return;
}

Status CnfToRes_path(char *cnf_path, char *res_path) {//����res�ļ��洢��ַ
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