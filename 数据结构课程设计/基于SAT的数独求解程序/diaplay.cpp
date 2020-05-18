#include"display.h"

void CNFPage()
{
	cnf_set *S = NULL;//总的结构体
	BOOL result = FALSE;
	int i, t;
	int op = 1;
	while (op) {
		//system("cls");
		printf("\n\n");
		printf("---------------基于SAT的CNF程序菜单-------------\n");
		printf("-----------------------CNF----------------------\n");
		printf("1. 加载CNF文件\n");
		printf("2. 求解CNF\n");
		printf("3. 打印CNF\n");
		printf("4. 检查答案\n");
		printf("5. 销毁CNF文件\n");
		printf("0. 返回\n");
		printf("------------------------------------------------\n");
		printf("请选择你的操作[0~5]: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			int i;
			S = (cnf_set*)malloc(sizeof(cnf_set));
			for (i = 0; i <= MAX_LITERAL; i++)
				S->literal_bool[i] = 0;
			if (Create_Set(S, 1) == TRUE)
				printf("加载成功!\n");
			getchar();
			getchar();
			break;
		case 2:
			if (S == NULL)
			{
				printf("CNF文件未加载!\n");
				getchar();
				getchar();
				break;
			}
			t = clock();
			result = DPLL_rec(S);
			t = clock() - t;
			if (result == TRUE)
			{
				printf("可满足！\n");
				literal_print(S);
				printf("用时: %dms\n", t);
			}
			else
				printf("不可满足");
			getchar();
			getchar();
			break;
		case 3:
			if (S == NULL)
			{
				printf("CNF文件未加载!\n");
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
				printf("CNF文件未加载!\n");
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
				printf("CNF文件未加载!\n");
				getchar();
				getchar();
				break;
			}
			if (Destroy_Set(S) == TRUE)
				printf("销毁成功!\n");
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
		printf("-------------基于SAT的CNF程序菜单---------------\n\n");
		printf("---------------------数独-----------------------\n");
		printf("1. 生成完整数独\n");
		printf("2. 生成随机数独\n");
		printf("0. 回退\n");
		printf("------------------------------------------------\n");
		printf("请选择你的操作[0~2]: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			//printf("请输入你的数独:\n");
			//s = inputSudoku();
			//if (!checkSudoku(s)) {
			//	printf("数独输入错误！\n");
			//}
			//else {
			//	printf("正在求解...\n");
			//	t = clock();
			//	cnf = transformToCNF(s);
			//	if (cnf) {
			//		printf("转化CNF成功!\n");
			//		dpll = DPLLRec(cnf, 0);
			//		if (dpll == TRUE) {
			//			t = clock() - t;
			//			printf("该CNF成功解出!\n");
			//			Sudoku *ss = NULL;
			//			ss = transformToSudoku(cnf);
			//			PrintSudoku(ss);
			//			free(ss);
			//			printf("用时: %dms\n", t);
			//			while (1) {
			//				int op;
			//				printf("------------------------------------------------\n");
			//				printf("1. 保存CNF及结果(后缀名为cnf)\n");
			//				//printf("2. 保存CNF\n");
			//				printf("0. 回退\n");
			//				printf("请选择你的操作[0~1]: ");
			//				scanf("%d", &op);
			//				if (op == 1) {
			//					printf("请输入保存路径:\n");
			//					scanf("%s", path);
			//					if (saveCnf(cnf, path)) {
			//						printf("CNF保存成功!\n");
			//						toSavePath(path, path);
			//						if (saveRes(path, dpll, cnf, t)) {
			//							printf("保存成功!\n");
			//							op = 0;
			//						}
			//						else {
			//							printf("保存失败!\n");
			//						}
			//					}
			//					else {
			//						printf("CNF保存失败!\n");
			//					}
			//				}
			//				/*else if(op==2){
			//					printf("请输入保存CNF路径: \n");
			//					scanf("%s",path);
			//					if(saveCnf(cnf,path)){
			//						printf("CNF保存成功!\n");
			//					}
			//					else{
			//						printf("CNF保存失败!\n");
			//					}
			//				}*/
			//				else if (op == 0) {
			//					break;
			//				}
			//			}
			//		}
			//	}
			//	else {
			//		printf("转化CNF失败!\n");
			//	}
			//}
			getchar();
			getchar();
			break;
		case 2:
			if (!(s = createSudoku(10))) {
				printf("数独生成失败！\n");
			}
			else {
				printf("数独生成成功!\n");
				sudoku_print(s);
				printf("------------------------------------------------\n");
				getchar();
				getchar();
				printf("正在求解...\n");
				t = clock();
				S = SudokuToCNF(s);
				if (S) {
					printf("转化CNF成功!\n");
					dpll = DPLL_rec(S);
					if (dpll == TRUE) {
						t = clock() - t;
						printf("该CNF成功解出!\n");
						Sudoku *ss = NULL;
						ss = CNFToSudoku(S);
						sudoku_print(ss);
						free(ss);
						printf("用时: %dms\n", t);
					}
					getchar();
					getchar();
					//		while (1) {
					//			int op;
					//			printf("------------------------------------------------\n");
					//			printf("1. 保存CNF及结果\n");
					//			//printf("2. 保存CNF\n");
					//			printf("0. 回退\n");
					//			printf("请选择你的操作[0~1]: ");
					//			scanf("%d", &op);
					//			if (op == 1) {
					//				printf("请输入保存路径(后缀名为cnf):\n");
					//				scanf("%s", path);
					//				if (saveCnf(cnf, path)) {
					//					printf("CNF保存成功!\n");
					//					toSavePath(path, path);
					//					if (saveRes(path, dpll, cnf, t)) {
					//						printf("保存成功!\n");
					//						op = 0;
					//					}
					//					else {
					//						printf("保存失败!\n");
					//					}
					//				}
					//				else {
					//					printf("CNF保存失败!\n");
					//				}
					//			}
								/*else if(op==2){
									printf("请输入保存CNF路径: \n");
									scanf("%s",path);
									if(saveCnf(cnf,path)){
										printf("CNF保存成功!\n");
									}
									else{
										printf("CNF保存失败!\n");
									}
								}*/
								/*	else if (op == 0) {
										break;
									}
								}
							}
							else {
								printf("求解失败！\n");
							}
						}
						else {
							printf("转化CNF失败!\n");
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
