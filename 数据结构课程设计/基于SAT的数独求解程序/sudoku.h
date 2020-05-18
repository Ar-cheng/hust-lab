//��������ģ��
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

Sudoku* createSudoku(int);//��������
cnf_set * SudokuToCNF(Sudoku *);//ת����CNF��ʽ
Sudoku *CNFToSudoku(cnf_set *);//CNFת��������
BOOL sudoku_check(Sudoku *);//�Ƿ�Ϻ�����
BOOL judge_x_y(Sudoku *,int, int);//���������Ƿ���ȷ
BOOL sudoku_rand(Sudoku *, int, int);//������������ĵݹ麯��
BOOL sudoku_solve(Sudoku *, int *);//�������
BOOL sudoku_dfs(Sudoku *, int , int , int *);//DFS�������
Status sudoku_print(Sudoku *);//��ӡ����

#endif // SUDOKU_H_INCLUDED
