#ifndef DPLL_H_
#define DPLL_H_

#include "clause.h"
#include"main.h"

Status literal_Assign(cnf_set *, int );//�洢��Ԫ��ֵ

Status literal_back(cnf_set *,int *);//��Ԫ�ĸ�ֵ���л��ݣ�

Status change_back(cnf_set *, stack_i *); //�Ӿ伯�ϻ�ԭ

int literal_chose(cnf_set *);

Status counter_sort_strategy(cnf_set *);//���ݱ�Ԫ���ֵĴ�������ѡ��Ԫ

Status DPLL_rec(cnf_set *);

Status literal_print(cnf_set *);

Status booleanprint(cnf_set *);


Status result_check(cnf_set *);//��֤������


#endif // DPLL_H_INCLUDED
