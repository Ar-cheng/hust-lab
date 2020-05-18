//数独生成模块
#ifndef SUDOKU_H_
#define SUDOKU_H_

#include "clause.h"
#include"main.h"
#include<time.h>

#define LOC(i,j,x) ((i)*81+(j)*9+(x))

typedef struct Sudoku{
	int sdk[9][9];
	Sudoku *next;
}Sudoku;

Sudoku* createSudoku(int);//生成数独
cnf_set * SudokuToCNF(Sudoku *);//转化成CNF格式
Sudoku *CNFToSudoku(cnf_set *);//CNF转化成数独
BOOL sudoku_check(Sudoku *);//是否合乎规则
BOOL judge_x_y(Sudoku *,int, int);//填入数字是否正确
BOOL sudoku_rand(Sudoku *, int, int);//随机生成数独的递归函数
BOOL sudoku_solve(Sudoku *, int *);//解答数独
BOOL sudoku_dfs(Sudoku *, int , int , int *);//DFS求解数独
Status sudoku_print(Sudoku *);//打印数独

#endif // SUDOKU_H_INCLUDED
