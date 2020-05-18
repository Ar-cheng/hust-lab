#ifndef CLAUSE_H_
#define CLAUSE_H_

#include"cnf_parser.h"
#include"main.h"

Status stack_push(stack_i *, int , First_Node *, literal_Node *);
First_Node * stack_pop(stack_i *);//��ջ
Status stack_free(stack_i *);//ջ�ͷ�

First_Node * creatClause(int *,int );//�����Ӿ�/1
Status addClause(First_Node *, cnf_set *);//�����Ӿ�/1
First_Node * removeClause(cnf_set *, First_Node *);//ɾ���Ӿ䣬�������ַ/1
Status deleteClause(cnf_set *, First_Node *);//�����Ӿ�/1

Status addliteral(First_Node *, int);//��ĳһ�Ӿ������ӱ�Ԫ/1
//Status backliteral(First_Node *, literal_Node *);//�ָ���Ԫ
literal_Node * removeliteral(First_Node * , int);//��ĳһ�Ӿ���ɾ����Ԫ
Status deleteLiteral(First_Node *, int);//����һ���Ӿ��еı�Ԫ

BOOL isUnitClause(First_Node * );//�ж��Ƿ�Ϊ���Ӿ�/1
Status evaluateClause(First_Node * , int);//�Ӿ�����/1
BOOL isHaveEmptyClause(cnf_set *);//�Ƿ��п��Ӿ�/1
BOOL isHaveClause(cnf_set * );//�Ӿ伯�Ƿ�Ϊ��/1

Status Clause_simply(cnf_set * , int, stack_i *);//���Ӿ仯��
First_Node * locateUnitClause(cnf_set *);//��λ���Ӿ�

Status stack_print(stack_i *);//��ӡջ
Status Destroy_Set(cnf_set *);//���ټ���

#endif // CLAUSE_H_INCLUDED
