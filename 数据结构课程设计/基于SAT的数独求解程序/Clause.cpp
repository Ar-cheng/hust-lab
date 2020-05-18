#include"Clause.h"

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

Status stack_free(stack_i * t) {//栈释放
	stack_i *p, *q;
	p = t;
	q = t->next;
	while (p != NULL)
	{
		free(p);
		p = q;
		if (q != NULL)
			q = q->next;
	}
	return OK;
}

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

Status Destroy_set(cnf_set * S)
{
	if (!S) {
		return ERROR;
	}
	while (S->clause_num != 0)
		deleteClause(S, S->set);
	free(S->literal_bool);
	free(S);
	return OK;
}
