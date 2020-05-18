#include "DPLL.h"

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
