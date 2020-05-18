#ifndef DPLL_H_
#define DPLL_H_

#include "clause.h"
#include"main.h"

Status literal_Assign(cnf_set *, int );//存储变元赋值

Status literal_back(cnf_set *,int *);//变元的赋值进行回溯；

Status change_back(cnf_set *, stack_i *); //子句集合还原

int literal_chose(cnf_set *);

Status counter_sort_strategy(cnf_set *);//依据变元出现的次数来挑选变元

Status DPLL_rec(cnf_set *);

Status literal_print(cnf_set *);

Status booleanprint(cnf_set *);


Status result_check(cnf_set *);//验证输出结果


#endif // DPLL_H_INCLUDED
