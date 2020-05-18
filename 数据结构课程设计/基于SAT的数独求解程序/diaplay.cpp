#include"display.h"

void CNFPage()
{
	cnf_set *S = NULL;//�ܵĽṹ��
	BOOL result = FALSE;
	int i, t;
	int op = 1;
	while (op) {
		//system("cls");
		printf("\n\n");
		printf("---------------����SAT��CNF����˵�-------------\n");
		printf("-----------------------CNF----------------------\n");
		printf("1. ����CNF�ļ�\n");
		printf("2. ���CNF\n");
		printf("3. ��ӡCNF\n");
		printf("4. ����\n");
		printf("5. ����CNF�ļ�\n");
		printf("0. ����\n");
		printf("------------------------------------------------\n");
		printf("��ѡ����Ĳ���[0~5]: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			int i;
			S = (cnf_set*)malloc(sizeof(cnf_set));
			for (i = 0; i <= MAX_LITERAL; i++)
				S->literal_bool[i] = 0;
			if (Create_Set(S, 1) == TRUE)
				printf("���سɹ�!\n");
			getchar();
			getchar();
			break;
		case 2:
			if (S == NULL)
			{
				printf("CNF�ļ�δ����!\n");
				getchar();
				getchar();
				break;
			}
			t = clock();
			result = DPLL_rec(S);
			t = clock() - t;
			if (result == TRUE)
			{
				printf("�����㣡\n");
				literal_print(S);
				printf("��ʱ: %dms\n", t);
			}
			else
				printf("��������");
			getchar();
			getchar();
			break;
		case 3:
			if (S == NULL)
			{
				printf("CNF�ļ�δ����!\n");
				getchar();
				getchar();
				break;
			}
			set_print(S);
			getchar();
			getchar();
			break;
		case 4:
			if (S == NULL)
			{
				printf("CNF�ļ�δ����!\n");
				getchar();
				getchar();
				break;
			}
			result_check(S);
			getchar();
			getchar();
			break;
		case 5:
			if (S == NULL)
			{
				printf("CNF�ļ�δ����!\n");
				getchar();
				getchar();
				break;
			}
			if (Destroy_Set(S) == TRUE)
				printf("���ٳɹ�!\n");
			S = NULL;
			getchar();
			getchar();
			break;
		case 0:
			break;
		}
	}
	if (S) {
		Destroy_Set(S);
		S = NULL;
	}
}
void sudokuPage()
{
	int t;
	int dpll;
	int op = 1;
	char path[256];
	cnf_set * S = NULL;
	Sudoku *s = (Sudoku *)malloc(sizeof(Sudoku));
	s->next = NULL;
	while (op) {
		system("cls");
		printf("\n\n");
		printf("-------------����SAT��CNF����˵�---------------\n\n");
		printf("---------------------����-----------------------\n");
		printf("1. ������������\n");
		printf("2. �����������\n");
		printf("0. ����\n");
		printf("------------------------------------------------\n");
		printf("��ѡ����Ĳ���[0~2]: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			//printf("�������������:\n");
			//s = inputSudoku();
			//if (!checkSudoku(s)) {
			//	printf("�����������\n");
			//}
			//else {
			//	printf("�������...\n");
			//	t = clock();
			//	cnf = transformToCNF(s);
			//	if (cnf) {
			//		printf("ת��CNF�ɹ�!\n");
			//		dpll = DPLLRec(cnf, 0);
			//		if (dpll == TRUE) {
			//			t = clock() - t;
			//			printf("��CNF�ɹ����!\n");
			//			Sudoku *ss = NULL;
			//			ss = transformToSudoku(cnf);
			//			PrintSudoku(ss);
			//			free(ss);
			//			printf("��ʱ: %dms\n", t);
			//			while (1) {
			//				int op;
			//				printf("------------------------------------------------\n");
			//				printf("1. ����CNF�����(��׺��Ϊcnf)\n");
			//				//printf("2. ����CNF\n");
			//				printf("0. ����\n");
			//				printf("��ѡ����Ĳ���[0~1]: ");
			//				scanf("%d", &op);
			//				if (op == 1) {
			//					printf("�����뱣��·��:\n");
			//					scanf("%s", path);
			//					if (saveCnf(cnf, path)) {
			//						printf("CNF����ɹ�!\n");
			//						toSavePath(path, path);
			//						if (saveRes(path, dpll, cnf, t)) {
			//							printf("����ɹ�!\n");
			//							op = 0;
			//						}
			//						else {
			//							printf("����ʧ��!\n");
			//						}
			//					}
			//					else {
			//						printf("CNF����ʧ��!\n");
			//					}
			//				}
			//				/*else if(op==2){
			//					printf("�����뱣��CNF·��: \n");
			//					scanf("%s",path);
			//					if(saveCnf(cnf,path)){
			//						printf("CNF����ɹ�!\n");
			//					}
			//					else{
			//						printf("CNF����ʧ��!\n");
			//					}
			//				}*/
			//				else if (op == 0) {
			//					break;
			//				}
			//			}
			//		}
			//	}
			//	else {
			//		printf("ת��CNFʧ��!\n");
			//	}
			//}
			getchar();
			getchar();
			break;
		case 2:
			if (!(s = createSudoku(10))) {
				printf("��������ʧ�ܣ�\n");
			}
			else {
				printf("�������ɳɹ�!\n");
				sudoku_print(s);
				printf("------------------------------------------------\n");
				getchar();
				getchar();
				printf("�������...\n");
				t = clock();
				S = SudokuToCNF(s);
				if (S) {
					printf("ת��CNF�ɹ�!\n");
					dpll = DPLL_rec(S);
					if (dpll == TRUE) {
						t = clock() - t;
						printf("��CNF�ɹ����!\n");
						Sudoku *ss = NULL;
						ss = CNFToSudoku(S);
						sudoku_print(ss);
						free(ss);
						printf("��ʱ: %dms\n", t);
					}
					getchar();
					getchar();
					//		while (1) {
					//			int op;
					//			printf("------------------------------------------------\n");
					//			printf("1. ����CNF�����\n");
					//			//printf("2. ����CNF\n");
					//			printf("0. ����\n");
					//			printf("��ѡ����Ĳ���[0~1]: ");
					//			scanf("%d", &op);
					//			if (op == 1) {
					//				printf("�����뱣��·��(��׺��Ϊcnf):\n");
					//				scanf("%s", path);
					//				if (saveCnf(cnf, path)) {
					//					printf("CNF����ɹ�!\n");
					//					toSavePath(path, path);
					//					if (saveRes(path, dpll, cnf, t)) {
					//						printf("����ɹ�!\n");
					//						op = 0;
					//					}
					//					else {
					//						printf("����ʧ��!\n");
					//					}
					//				}
					//				else {
					//					printf("CNF����ʧ��!\n");
					//				}
					//			}
								/*else if(op==2){
									printf("�����뱣��CNF·��: \n");
									scanf("%s",path);
									if(saveCnf(cnf,path)){
										printf("CNF����ɹ�!\n");
									}
									else{
										printf("CNF����ʧ��!\n");
									}
								}*/
								/*	else if (op == 0) {
										break;
									}
								}
							}
							else {
								printf("���ʧ�ܣ�\n");
							}
						}
						else {
							printf("ת��CNFʧ��!\n");
						}
					}*/
					//	getchar();
					//	getchar();
					//	break;
					//}
				/*	if (cnf) {
						destroyCNF(cnf);
						cnf = NULL;
					}
					if (s) {
						free(s);
						s = NULL;
					}*/
				}
			}
		}
	}
}
