#include "DPLL.h"

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

Status literal_print(cnf_set *S) {
	First_Node *p = S->set;
	int i;
	for (i = 1; i <= S->literal_num_init; i++)
		if (S->literal_bool[i] > 0) {
			if (i % 10 == 1)
				printf("\n");
			printf("%d:TRUE", i);
		}
		else if (S->literal_bool[i] < 0) {
			if (i % 10 == 1)
				printf("\n");
			printf("%d:FALSE", i);
		}
	return OK;
}

Status booleanprint(cnf_set * S) {
	First_Node *p = S->set;
	int i;
	for (i = 1; i <= S->literal_num_init; i++)
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
		int *visitedplus = (int*)malloc((S->literal_num_init + 1) * sizeof(int));
		if (visitedplus == NULL)exit(-1);
		int *visitedminus = (int*)malloc((S->literal_num_init + 1) * sizeof(int));
		if (visitedminus == NULL)exit(-1);
		for (i = 1; i <= S->literal_num_init; i++) {
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

int literal_chose(cnf_set * S) {
	return counter_sort_strategy(S);
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
