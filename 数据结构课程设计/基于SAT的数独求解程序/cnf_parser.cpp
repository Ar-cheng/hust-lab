#include"cnf_parser.h"

Status literal_print(cnf_set *);//变元打印

Status Create_Set(cnf_set *S, int tag) {//创建集合的结构体
	if (tag == 1) {//tag == 1 表示读取cnf文件进行求解
		FILE *fp;//目标文件指针
		char filename[100];
		int is_eof;//判断是否读取到文件尾
		int is_first_line = 1;//判断是否读取的是第一行
		printf("输入文件名称：");
		scanf("%s", filename);
		if ((fp = fopen(filename, "r")) == NULL)
		{
			printf("    	  文件打开失败!\n ");
			return ERROR;
		}
		printf("文件打开成功！\n");
		char c[10];
		char buff[10];
		fscanf(fp, "%s", c);
		while (strcmp(c, "c") == 0)//过滤掉所有以c开头的注释内容
		{
			fscanf(fp, "%s", c);
			if (strcmp(c, "p") == 0)
				break;//针对空注释的情况
			else
			{
				fscanf(fp, "%*[^\n]%*c");//跳行，将文件指针置于下一行的开头
				fscanf(fp, "%s", c);
			}
		}
		//变元个数以及子句个数读取
		fscanf(fp, "%s", buff);//滤掉cnf
		fscanf(fp, "%s", buff);//以字符串格式读取变元个数
		S->literal_num = atoi(buff);//字符->数字
		S->literal_num_init = S->literal_num;
		fscanf(fp, "%s", buff);//以字符串格式读取子句个数
		S->clause_num = atoi(buff);//字符->数字

#ifdef DEBUG
		printf("变元个数为%d  子句个数为%d\n", S->literal_num, S->clause_num);//......DEBUG......
#endif

//子句读取及构建
		int i = 0;// 记录子句中变元的个数
		First_Node *u, *v;//临时变量
		literal_Node *p, *q;//临时变量

		//第一个子句
		S->set = (First_Node *)malloc(sizeof(First_Node));
		S->set->next_FirstNode = NULL;
		S->set->prev_FirstNode = NULL;
		p = (literal_Node *)malloc(sizeof(literal_Node));//读取子句的第一个变元
		p->next_literalnode = NULL;
		S->set->next_literalNode = p;
		fscanf(fp, "%s", buff);
		p->literal_info = atoi(buff);//录入变元信息
		i = 1;

#ifdef DEBUG
		printf("%d  ", p->literal_info);//....DEBUG....
#endif

		while (TRUE) {//同一子句的后续变元
			fscanf(fp, "%s", buff);
			if (strcmp(buff, "0") == 0)
				break;//判断当前子句是否读取完成
			q = (literal_Node *)malloc(sizeof(literal_Node));
			q->next_literalnode = NULL;
			q->literal_info = atoi(buff);//录入变元信息
			i++;
			//链接
			p->next_literalnode = q;
			p = q;

#ifdef DEBUG
			printf("%d ", p->literal_info);//......DEBUG......
#endif

		}
		S->set->num = i;//记录子句中的变元个数
		//printf("子句变元个数为%d\n", S->set->num);//....DEBUG....

		//后续子句
		while ((is_eof = fscanf(fp, "%s", buff)) != -1) {//判断是否读到文件尾
			v = (First_Node *)malloc(sizeof(First_Node));
			v->next_FirstNode = NULL;
			p = (literal_Node *)malloc(sizeof(literal_Node));//读取子句的第一个变元
			p->next_literalnode = NULL;
			v->next_literalNode = p;
			p->literal_info = atoi(buff);//录入变元信息
			i = 1;

#ifdef DEBUG
			printf("%d ", p->literal_info);//......DEBUG......
#endif

			while (TRUE) {//同一子句的后续变元
				fscanf(fp, "%s", buff);
				if (strcmp(buff, "0") == 0)
					break;//判断当前子句是否读取完成
				q = (literal_Node *)malloc(sizeof(literal_Node));
				q->next_literalnode = NULL;
				q->literal_info = atoi(buff);//录入变元信息
				i++;
				//变元结点链接
				p->next_literalnode = q;
				p = q;

#ifdef DEBUG	
				printf("%d ", p->literal_info);
#endif
			}
			v->num = i;

			//首节点链接
			if (is_first_line)//第一行与第二行
			{
				S->set->next_FirstNode = v;
				v->prev_FirstNode = S->set;
				u = v;
				is_first_line = 0;

#ifdef DEBUG
				printf("子句变元个数为%d\n", S->set->num);//....DEBUG....
#endif			
			}
			else {//后续行
#ifdef DEBUG
				printf("子句变元个数为%d\n", u->num);//....DEBUG....
#endif
				u->next_FirstNode = v;
				v->prev_FirstNode = u;
				u = v;
			}
		}
	}
	else if (tag == 2) {//tag ==2 表示创建空集合后以数独结构进行转换。
		S->clause_num = 0;
		S->literal_num = 9 * 9 * 9;
		S->literal_num_init = 0;
		S->set = NULL;
	}
	return TRUE;
}

Status set_print(cnf_set * S) {
	First_Node * p = S->set;
	for (; p != NULL; p = p->next_FirstNode)
	{
		printf("变元个数：%d\t", p->num);
		literal_Node * q = p->next_literalNode;
		for (; q != NULL; q = q->next_literalnode)
			printf("%d ", q->literal_info);
		printf("\n");
	}
	printf("\n");
	return OK;
}

Status literal_print(cnf_set *S) {
	int i;
	for (i = 1; i <= MAX_LITERAL; i++) {
		if (S->literal_bool[i] > 0)
		{
			if ((i - 1) % 5 == 0)
				printf("\n");
			printf("%d:TRUE ", i);
		}
		else if (S->literal_bool[i] < 0)
		{
			if ((i - 1) % 5 == 0)
				printf("\n");
			printf("%d:FALSE ", i);
		}
	}
	return OK;
}
