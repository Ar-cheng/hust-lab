#ifndef CLAUSE_H_
#define CLAUSE_H_

#include"cnf_parser.h"
#include"main.h"

Status stack_push(stack_i *, int , First_Node *, literal_Node *);
First_Node * stack_pop(stack_i *);//出栈
Status stack_free(stack_i *);//栈释放

First_Node * creatClause(int *,int );//创建子句/1
Status addClause(First_Node *, cnf_set *);//增加子句/1
First_Node * removeClause(cnf_set *, First_Node *);//删除子句，返回其地址/1
Status deleteClause(cnf_set *, First_Node *);//销毁子句/1

Status addliteral(First_Node *, int);//在某一子句中增加变元/1
//Status backliteral(First_Node *, literal_Node *);//恢复变元
literal_Node * removeliteral(First_Node * , int);//在某一子句中删除变元
Status deleteLiteral(First_Node *, int);//销毁一个子句中的变元

BOOL isUnitClause(First_Node * );//判断是否为单子句/1
Status evaluateClause(First_Node * , int);//子句判真/1
BOOL isHaveEmptyClause(cnf_set *);//是否有空子句/1
BOOL isHaveClause(cnf_set * );//子句集是否为空/1

Status Clause_simply(cnf_set * , int, stack_i *);//单子句化简
First_Node * locateUnitClause(cnf_set *);//定位单子句

Status stack_print(stack_i *);//打印栈
Status Destroy_Set(cnf_set *);//销毁集合

#endif // CLAUSE_H_INCLUDED
