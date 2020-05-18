#include"cnf_parser.h"

Status literal_print(cnf_set *);//��Ԫ��ӡ

Status Create_Set(cnf_set *S, int tag) {//�������ϵĽṹ��
	if (tag == 1) {//tag == 1 ��ʾ��ȡcnf�ļ��������
		FILE *fp;//Ŀ���ļ�ָ��
		char filename[100];
		int is_eof;//�ж��Ƿ��ȡ���ļ�β
		int is_first_line = 1;//�ж��Ƿ��ȡ���ǵ�һ��
		printf("�����ļ����ƣ�");
		scanf("%s", filename);
		if ((fp = fopen(filename, "r")) == NULL)
		{
			printf("    	  �ļ���ʧ��!\n ");
			return ERROR;
		}
		printf("�ļ��򿪳ɹ���\n");
		char c[10];
		char buff[10];
		fscanf(fp, "%s", c);
		while (strcmp(c, "c") == 0)//���˵�������c��ͷ��ע������
		{
			fscanf(fp, "%s", c);
			if (strcmp(c, "p") == 0)
				break;//��Կ�ע�͵����
			else
			{
				fscanf(fp, "%*[^\n]%*c");//���У����ļ�ָ��������һ�еĿ�ͷ
				fscanf(fp, "%s", c);
			}
		}
		//��Ԫ�����Լ��Ӿ������ȡ
		fscanf(fp, "%s", buff);//�˵�cnf
		fscanf(fp, "%s", buff);//���ַ�����ʽ��ȡ��Ԫ����
		S->literal_num = atoi(buff);//�ַ�->����
		S->literal_num_init = S->literal_num;
		fscanf(fp, "%s", buff);//���ַ�����ʽ��ȡ�Ӿ����
		S->clause_num = atoi(buff);//�ַ�->����

#ifdef DEBUG
		printf("��Ԫ����Ϊ%d  �Ӿ����Ϊ%d\n", S->literal_num, S->clause_num);//......DEBUG......
#endif

//�Ӿ��ȡ������
		int i = 0;// ��¼�Ӿ��б�Ԫ�ĸ���
		First_Node *u, *v;//��ʱ����
		literal_Node *p, *q;//��ʱ����

		//��һ���Ӿ�
		S->set = (First_Node *)malloc(sizeof(First_Node));
		S->set->next_FirstNode = NULL;
		S->set->prev_FirstNode = NULL;
		p = (literal_Node *)malloc(sizeof(literal_Node));//��ȡ�Ӿ�ĵ�һ����Ԫ
		p->next_literalnode = NULL;
		S->set->next_literalNode = p;
		fscanf(fp, "%s", buff);
		p->literal_info = atoi(buff);//¼���Ԫ��Ϣ
		i = 1;

#ifdef DEBUG
		printf("%d  ", p->literal_info);//....DEBUG....
#endif

		while (TRUE) {//ͬһ�Ӿ�ĺ�����Ԫ
			fscanf(fp, "%s", buff);
			if (strcmp(buff, "0") == 0)
				break;//�жϵ�ǰ�Ӿ��Ƿ��ȡ���
			q = (literal_Node *)malloc(sizeof(literal_Node));
			q->next_literalnode = NULL;
			q->literal_info = atoi(buff);//¼���Ԫ��Ϣ
			i++;
			//����
			p->next_literalnode = q;
			p = q;

#ifdef DEBUG
			printf("%d ", p->literal_info);//......DEBUG......
#endif

		}
		S->set->num = i;//��¼�Ӿ��еı�Ԫ����
		//printf("�Ӿ��Ԫ����Ϊ%d\n", S->set->num);//....DEBUG....

		//�����Ӿ�
		while ((is_eof = fscanf(fp, "%s", buff)) != -1) {//�ж��Ƿ�����ļ�β
			v = (First_Node *)malloc(sizeof(First_Node));
			v->next_FirstNode = NULL;
			p = (literal_Node *)malloc(sizeof(literal_Node));//��ȡ�Ӿ�ĵ�һ����Ԫ
			p->next_literalnode = NULL;
			v->next_literalNode = p;
			p->literal_info = atoi(buff);//¼���Ԫ��Ϣ
			i = 1;

#ifdef DEBUG
			printf("%d ", p->literal_info);//......DEBUG......
#endif

			while (TRUE) {//ͬһ�Ӿ�ĺ�����Ԫ
				fscanf(fp, "%s", buff);
				if (strcmp(buff, "0") == 0)
					break;//�жϵ�ǰ�Ӿ��Ƿ��ȡ���
				q = (literal_Node *)malloc(sizeof(literal_Node));
				q->next_literalnode = NULL;
				q->literal_info = atoi(buff);//¼���Ԫ��Ϣ
				i++;
				//��Ԫ�������
				p->next_literalnode = q;
				p = q;

#ifdef DEBUG	
				printf("%d ", p->literal_info);
#endif
			}
			v->num = i;

			//�׽ڵ�����
			if (is_first_line)//��һ����ڶ���
			{
				S->set->next_FirstNode = v;
				v->prev_FirstNode = S->set;
				u = v;
				is_first_line = 0;

#ifdef DEBUG
				printf("�Ӿ��Ԫ����Ϊ%d\n", S->set->num);//....DEBUG....
#endif			
			}
			else {//������
#ifdef DEBUG
				printf("�Ӿ��Ԫ����Ϊ%d\n", u->num);//....DEBUG....
#endif
				u->next_FirstNode = v;
				v->prev_FirstNode = u;
				u = v;
			}
		}
	}
	else if (tag == 2) {//tag ==2 ��ʾ�����ռ��Ϻ��������ṹ����ת����
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
		printf("��Ԫ������%d\t", p->num);
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
