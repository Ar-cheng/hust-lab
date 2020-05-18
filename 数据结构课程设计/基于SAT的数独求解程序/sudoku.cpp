#include"sudoku.h"

Sudoku* createSudoku(int difficult)
{
	int i, j, t;
	int c, flag = 0;
	int x, y;
	srand(time(0));
	Sudoku *s = (Sudoku*)malloc(sizeof(Sudoku));
	Sudoku *ss = NULL;
	s->next = NULL;
	if (!s) {
		return NULL;
	}
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			s->sdk[i][j] = 0;
		}
	}
	if (sudoku_rand(s, 0, 0) == TRUE) {//随机生成完整数独
		sudoku_print(s);
		for (c = 0; c < 81 - 78; c++) {//挖掉3个空
			x = rand() % 9;
			y = rand() % 9;
			s->sdk[x][y] = 0;
		}
		while (1) {
			sudoku_solve(s, &c);//求解该数独，得到解的个数c
			if (c > 1) {
				s->sdk[x][y] = t;
				flag++;
				if (flag >= difficult) {
					break;
				}
				for (ss = s->next; ss; ss = s->next) {
					s->next = ss->next;
					free(ss);
				}
			}
			else {
				do {
					x = rand() % 9;
					y = rand() % 9;
				} while (s->sdk[x][y] == 0);
				t = s->sdk[x][y];
				s->sdk[x][y] = 0;
			}
		}
		return s;
	}
	else {
		return NULL;
	}
}

BOOL sudoku_rand(Sudoku *s, int x, int y)
{
	int c = 0;
	s->sdk[x][y] = rand() % 9 + 1;
	do {
		do {
			c++;
			if (c > 9) {
				s->sdk[x][y] = 0;
				return FALSE;
			}
			s->sdk[x][y] = s->sdk[x][y] % 9 + 1;
		} while (judge_x_y(s, x, y) != TRUE);
		if (x == 8 && y == 8) {
			return TRUE;
		}
	} while (((y == 8) ? sudoku_rand(s, x + 1, 0) : sudoku_rand(s, x, y + 1)) != TRUE);
	return TRUE;
}
//1

cnf_set * SudokuToCNF(Sudoku *s)
{
	/*用X(i,j,x)表示第i行第j列的格子填k是否为真*/
	/*1为真, 0为假*/
	First_Node * p = NULL;
	int i, j, k, l, c, m;
	int b[9], b2[9], b3[9];
	cnf_set S;//总的结构体
	for (i = 0; i <= 729; i++)
		S.literal_bool[i] = 0;
	Create_Set(&S, 2);
	/*生成每个格子的情况*/
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			//如果该格子有数字
			if (s->sdk[i][j] != 0) {
				//X(i,j,x)为真,其他x为假
				for (k = 1; k <= 9; k++) {
					if (k == s->sdk[i][j]) {
						b[0] = LOC(i, j, k);
					}
					else {
						b[0] = -LOC(i, j, k);
					}
					p = creatClause(b, 1);
					addClause(p, &S);
				}

				//横排空格处不相等,向右搜索
				for (k = j + 1; k < 9; k++) {
					if (s->sdk[i][k] == 0) {
						b[0] = -LOC(i, j, s->sdk[i][j]);
						b[1] = -LOC(i, k, s->sdk[i][j]);
						p = creatClause(b, 2);
						addClause(p, &S);
					}
				}
				//纵排空格处不相等,向下搜索
				for (k = i + 1; k < 9; k++) {
					if (s->sdk[k][j] == 0) {
						b[0] = -LOC(i, j, s->sdk[i][j]);
						b[1] = -LOC(k, j, s->sdk[i][j]);
						p = creatClause(b, 2);
						addClause(p, &S);
					}
				}
				//九宫格空格处不相等,向右下角搜索
				for (k = i + 1; k < i / 3 * 3 + 3; k++) {
					for (l = j / 3 * 3; l < j / 3 * 3 + 3; l++) {
						//横排与纵排已经比较过
						if (l == j) {
							continue;
						}
						if (s->sdk[k][l] == 0) {
							b[0] = 0 - LOC(i, j, s->sdk[i][j]);
							b[1] = 0 - LOC(k, l, s->sdk[i][j]);
							p = creatClause(b, 2);
							addClause(p, &S);
						}
					}
				}
			}
			//如果是空格
			else {
				//空格处只能填一个数字
				for (k = 1, c = 0; k <= 9; k++) {
					s->sdk[i][j] = k;
					if (judge_x_y(s, i, j)) {
						b[c] = k;
						b2[c] = LOC(i, j, k);
						c++;
					}
				}
				s->sdk[i][j] = 0;
				p = creatClause(b2, c);
				addClause(p, &S);
				for (k = 0; k < c - 1; k++) {
					for (l = k + 1; l < c; l++) {
						b2[0] = -LOC(i, j, b[k]);
						b2[1] = -LOC(i, j, b[l]);
						p = creatClause(b2, 2);
						addClause(p, &S);
					}
				}
				//横排搜索
				for (k = j + 1; k < 9; k++) {
					//空格处与已填不相等
					if (s->sdk[i][k] != 0) {
						b2[0] = 0 - LOC(i, j, s->sdk[i][k]);
						b2[1] = 0 - LOC(i, k, s->sdk[i][k]);
						p = creatClause(b2, 2);
						addClause(p, &S);
					}
					//都是空格处不能填相同
					else {
						for (l = 0; l < c; l++) {
							b2[0] = 0 - LOC(i, j, b[l]);
							b2[1] = 0 - LOC(i, k, b[l]);
							p = creatClause(b2, 2);
							addClause(p, &S);
						}
					}
				}
				//纵排搜索
				for (k = i + 1; k < 9; k++) {
					//空格处与已填不相等
					if (s->sdk[k][j] != 0) {
						b2[0] = 0 - LOC(i, j, s->sdk[k][j]);
						b2[1] = 0 - LOC(k, j, s->sdk[k][j]);
						p = creatClause(b2, 2);
						addClause(p, &S);
					}
					//都是空格处不能填相同
					else {
						for (l = 0; l < c; l++) {
							b2[0] = 0 - LOC(i, j, b[l]);
							b2[1] = 0 - LOC(k, j, b[l]);
							p = creatClause(b2, 2);
							addClause(p, &S);
						}
					}
				}
				//九宫格搜索
				for (k = i + 1; k < i / 3 * 3 + 3; k++) {
					for (l = j / 3 * 3; l < j / 3 * 3 + 3; l++) {
						if (l == j) {
							continue;
						}
						//空格处与已填不相等
						if (s->sdk[k][l] != 0) {
							b2[0] = 0 - LOC(i, j, s->sdk[k][l]);
							b2[1] = 0 - LOC(k, j, s->sdk[k][l]);
							p = creatClause(b2, 2);
							addClause(p, &S);
						}
						//都是空格处不能填相同
						else {
							for (m = 0; m < c; m++) {
								b2[0] = 0 - LOC(i, j, b[m]);
								b2[1] = 0 - LOC(k, l, b[m]);
								p = creatClause(b2, 2);
								addClause(p, &S);
							}
						}
					}
				}
			}
		}
	}
	//每行必须填1~9
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			b[j] = 0;
		}
		for (j = 0, l = 0; j < 9; j++) {
			if (s->sdk[i][j] != 0) {
				b[s->sdk[i][j] - 1] = 1;//存放未填的数字
			}
			else {
				b2[l] = j;//存放未填的位置
				l++;
			}
		}
		for (j = 0, k = 0; j < 9; j++) {
			if (b[j] == 0) {
				b[k] = j + 1;
				k++;
			}
		}
		for (j = 0; j < k; j++) {
			for (c = 0; c < l; c++) {
				b3[c] = LOC(i, b2[c], b[j]);
			}
			p = creatClause(b3, 1);
			addClause(p, &S);
		}
	}
	//每列必须填1~9
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			b[j] = 0;
		}
		for (j = 0, l = 0; j < 9; j++) {
			if (s->sdk[j][i] != 0) {
				b[s->sdk[j][i] - 1] = 1;//存放未填的数字
			}
			else {
				b2[l] = i;//存放未填的位置
				l++;
			}
		}
		for (j = 0, k = 0; j < 9; j++) {
			if (b[j] == 0) {
				b[k] = j + 1;
			}
		}
		for (j = 0; j < k; j++) {
			for (c = 0; c < l; c++) {
				b3[c] = LOC(i, b2[c], b[j]);
			}
			p = creatClause(b3, 1);
			addClause(p, &S);
		}
	}
	//九宫格必须填1~9
	for (i = 0; i < 9; i += 3) {
		for (m = 0; m < 9; m += 3) {
			for (j = 0; j < 9; j++) {
				b[j] = 0;
			}
			for (j = 0, l = 0; j < 9; j++) {
				if (s->sdk[i + j / 3][m + j % 3] != 0) {
					b[s->sdk[i + j / 3][m + j % 3] - 1] = 1;//存放未填的数字
				}
				else {
					b2[l] = j;//存放未填的位置
					l++;
				}
			}
			for (j = 0, k = 0; j < 9; j++) {
				if (b[j] == 0) {
					b[k] = j + 1;
				}
			}
			for (j = 0; j < k; j++) {
				for (c = 0; c < l; c++) {
					b3[c] = LOC(i, b2[c], b[j]);
				}
				p = creatClause(b3, 1);
				addClause(p, &S);
			}
		}
	}
	//set_print(&S);
	return &S;
}

Sudoku *CNFToSudoku(cnf_set *S) {
	Sudoku *s = (Sudoku*)malloc(sizeof(Sudoku));
	s->next = NULL;
	int i, j, k;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			for (k = 1; k <= 9; k++) {
				if (S->literal_bool[LOC(i, j, k)] == TRUE) {
					s->sdk[i][j] = k;
				}
			}
		}
	}
	return s;
}

BOOL sudoku_check(Sudoku *s)
{
	int i, j, k, l;
	int flag = 0;
	int b[9];//记录出现次数
	/*横向检查*/
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			b[j] = 0;
		}
		for (j = 0; j < 9; j++) {
			if (!s->sdk[i][j]) {
				flag = 1;
			}
			else if (b[s->sdk[i][j] - 1] == 0) {
				b[s->sdk[i][j] - 1] = 1;//数字sdk[i][j]已出现
			}
			else {
				return FALSE;
			}
		}
	}
	/*纵向检查*/
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			b[j] = 0;
		}
		for (j = 0; j < 9; j++) {
			if (!s->sdk[j][i]) {
				flag = 1;
			}
			else if (b[s->sdk[j][i] - 1] == 0) {
				b[s->sdk[j][i] - 1] = 1;
			}
			else {
				return FALSE;
			}
		}
	}
	/*九格检查*/
	for (i = 0; i < 9; i += 3) {
		for (j = 0; j < 9; j += 3) {
			for (k = 0; k < 9; k++) {
				b[k] = 0;
			}
			for (k = i; k < i + 3; k++) {
				for (l = j; l < j + 3; l++) {
					if (s->sdk[k][l] == 0) {
						flag = 1;
					}
					else if (b[s->sdk[k][l] - 1] == 0) {
						b[s->sdk[k][l] - 1] = 1;
					}
					else {
						return FALSE;
					}
				}
			}
		}
	}
	return (flag) ? UNSURE : TRUE;
}

BOOL judge_x_y(Sudoku *s, int x, int y)
{
	int i, j;

	for (i = 0; i < 9; i++) {
		if (s->sdk[i][y] == s->sdk[x][y] && i != x) {
			return FALSE;
		}

	}
	for (i = 0; i < 9; i++) {
		if (s->sdk[x][i] == s->sdk[x][y] && i != y) {
			return FALSE;
		}

	}
	for (i = x / 3 * 3; i < x / 3 * 3 + 3; i++) {
		for (j = y / 3 * 3; j < y / 3 * 3 + 3; j++) {
			if (s->sdk[i][j] == s->sdk[x][y] && (i != x || j != y)) {
				return FALSE;
			}

		}
	}
	return TRUE;
}//1

BOOL sudoku_solve(Sudoku *s, int *solvecount)
{
	*solvecount = 0;
	sudoku_dfs(s, 0, 0, solvecount);
	return (solvecount > 0) ? TRUE : FALSE;
}

BOOL sudoku_dfs(Sudoku *s, int x, int y, int *solvecount)
{
	int i, j, k;
	Sudoku *ss;
	while (s->sdk[x][y] != 0 && x <= 8) {
		y++;
		if (y == 9) {
			x += 1;
			y = 0;
		}
	}
	if (x > 8) {
		ss = (Sudoku*)malloc(sizeof(Sudoku));
		for (j = 0; j < 9; j++) {
			for (k = 0; k < 9; k++) {
				ss->sdk[j][k] = s->sdk[j][k];
			}
		}
		ss->next = s->next;
		s->next = ss;
		(*solvecount)++;
		return TRUE;
	}
	for (i = 1; i <= 9; i++) {
		s->sdk[x][y] = i;
		switch (judge_x_y(s, x, y))
		{
		case FALSE:
			break;
		case TRUE:
			if (x == 8 && y == 8) {
				ss = (Sudoku*)malloc(sizeof(Sudoku));
				for (j = 0; j < 9; j++) {
					for (k = 0; k < 9; k++) {
						ss->sdk[j][k] = s->sdk[j][k];
					}
				}
				ss->next = s->next;
				s->next = ss;
				s->sdk[x][y] = 0;
				(*solvecount)++;
				return TRUE;
			}
			else {
				(y == 8) ? sudoku_dfs(s, x + 1, 0, solvecount) : sudoku_dfs(s, x, y + 1, solvecount);
			}
			break;
		default:
			break;
		}
	}
	s->sdk[x][y] = 0;
	return FALSE;
}

Status sudoku_print(Sudoku *s)
{
	int i, j;
	printf("打印数独:\n");
	for (j = 0; j < 19; j++) {
		printf("-");
	}
	printf("\n");
	for (i = 0; i < 9; i++) {
		printf("|");
		for (j = 0; j < 9; j++) {
			printf("%d%c", s->sdk[i][j], ((j + 1) % 3 == 0) ? '|' : ' ');
		}
		printf("\n");
		if ((i + 1) % 3 == 0) {
			printf("|");
			for (j = 0; j < 17; j++) {
				printf("-");
			}
			printf("|\n");
		}
	}
	return OK;
}
