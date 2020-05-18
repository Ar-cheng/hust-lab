#pragma once
#define MAX_LITERAL 1000//����Ԫ��Ŀ
#define LINE 1024 //��ȡһ�е�����ַ���

#define ERROR -1//�쳣����״̬
#define OK 1//��������״̬����
#define TRUE 1
#define FALSE -1

typedef int InfoType;
typedef int Status;//�����ķ���״̬

#define MAX_CLAUSE_LENGTH 30
#define CLAUSE 1
#define LITERAL 2
#define SPLIT 3
#define UNSURE -2

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
	int literal_num_init;//�����Ԫ����
	int clause_num;//�Ӿ����
	First_Node * set;//�Ӿ�ļ���
	int literal_bool[MAX_LITERAL];//��¼��Ӧ��ű�Ԫ�����,1Ϊ�棬-1Ϊ�٣�0Ϊδ֪
	//int literal_counter[MAX_LITERAL];//��Ԫ��Ŀͳ��
}cnf_set;

typedef struct Clause {//�Ӿ�ṹ
	//int isexist=0;//�ж��Ӿ��Ƿ����
	int literalnum;//��Ԫ��Ŀ
	int newclause[MAX_CLAUSE_LENGTH];//��¼��Ԫ���
	int clauseboolean[MAX_CLAUSE_LENGTH];//��¼��Ԫ����,1Ϊ����-1Ϊ��
}Clause;

typedef struct stack_i {//ջ�ṹ
	int flag;//ѹջ�����־
	literal_Node * N;
	First_Node * P;
	stack_i * next;
}stack_i;
