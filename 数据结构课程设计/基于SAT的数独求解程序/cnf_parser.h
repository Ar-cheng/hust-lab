//cnf文件解析模块
//以邻接表的格式来存储子句，首节点存储子局中的变元个数，后续节点存储变元序号
#ifndef CNF_PARSER_H_
#define CNF_PARSER_H_

#include"main.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>



Status Create_Set(cnf_set *,int);//创建子句集

Status set_print(cnf_set *);//打印集合


#endif // CNF_PARSER_H