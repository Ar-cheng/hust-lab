#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
	int compute_all(char *pt);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
	int rec_sort(char *pt,char *buff);
#ifdef __cplusplus
}
#endif

#define N 30
char goods[N][21] = { 
{'P','E','N',0,0,0,0,0,0,0,10,35,0,56,0,70,0,25,0,0,0},
{'B','O','O','K',0,0,0,0,0,0,9,12,0,30,0,25,0,24,0,0,0},
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0},
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} ,
{ 'T','e','m','p','-','V','a','l','u','e',8,15,0,20,0,30,0,2,0,0,0} };
char *buffer_order[30] = { 0 };
int main() {
	while (1) {
		system("cls");
		int i = 0;
		unsigned int n;
		int option;
		char goodsname[11] = { 0 };
		char temp_info[11] = { 0 };
		char input[5];
		char flag = 0;
		char c;
		int result;
		printf("--------------------------------------------------------------------------\n");
		printf("1.search info   \t");
		printf("2.change info   \t");
		printf("3.calculate score\n");
		printf("4.rank score    \t");
		printf("5.print all info\t");
		printf("6.exit\n");
		printf("pleasr choose your option:");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			while (1) {
				printf("please enter goodsname:");
				getchar();
				c = getchar();
				if (c == '\n') break;
				else temp_info[0] = c;
				scanf("%s", temp_info + 1);
				for (i = 0; i < N; )
				{
					strncpy(goodsname, goods[i], 10);
					result = strcmp(goodsname, temp_info);
					if (result == 0)
						break;
					i++;
				}
				if (i == 30)
					continue;
				printf("discount : %d \t\t", goods[i][10]);
				printf("price_in : %d \t\t", goods[i][11] + goods[i][12] * 128);
				printf("price_out : %d\n", goods[i][13] + goods[i][14] * 128);
				printf("num_in : %d   \t\t", goods[i][15] + goods[i][16] * 128);
				printf("num_out : %d\t\t", goods[i][17] + goods[i][18] * 128);
				printf("reconmmend: %d\n", goods[i][19] + goods[i][20] * 128);
				break;
			}
			getchar();
			getchar();
			break;
		case 2:
			while (1) {
				printf("please enter goodsname:");
				getchar();
				c = getchar();
				if (c == '\n') break;
				else temp_info[0] = c;
				scanf("%s", temp_info + 1);
				for (i = 0; i < N; )
				{
					strncpy(goodsname, goods[i], 10);
					result = strcmp(goodsname, temp_info);
					if (result == 0)
						break;
					i++;
				}
				if (i == 30)
					continue;
				break;
			}
			if (c == '\n') break;
			while (1) {
				printf("discount : %d->", goods[i][10]);
				rewind(stdin);//清空缓存区
				n = 0;
				while ((c = getchar()) != '\n')
				{
					input[n] = c;
					n++;
				}
				if (n == 0) break;
				flag = 1;
				input[n] = '\0';
				n = atoi(input);
				if (n == 0) break;
				if (n > 10) continue;
				break;
			}
			if (flag == 1)
				goods[i][10] = n;
			while (1) {
				printf("price_in : %d->", goods[i][11] + goods[i][12] * 128);
				flag = 0;
				rewind(stdin);//清空缓存区
				n = 0;
				while ((c = getchar()) != '\n')
				{
					input[n] = c;
					n++;
				}
				if (n == 0) break;
				flag = 1;
				input[n] = '\0';
				n = atoi(input);
				if (n == 0) continue;
				break;
			}
			if (flag == 1) {
				goods[i][11] = n % 128;
				goods[i][12] = n / 128;
			}
			while (1) {
				printf("price_out : %d->", goods[i][13] + goods[i][14] * 128);
				flag = 0;
				rewind(stdin);//清空缓存区
				n = 0;
				while ((c = getchar()) != '\n')
				{
					input[n] = c;
					n++;
				}
				if (n == 0) break;
				flag = 1;
				input[n] = '\0';
				n = atoi(input);
				if (n == 0) continue;
				break;
			}
			if (flag == 1) {
				goods[i][13] = n % 128;
				goods[i][14] = n / 128;
			}
			while (1) {
				printf("num_in : %d->", goods[i][15] + goods[i][16] * 128);
				flag = 0;
				rewind(stdin);//清空缓存区
				n = 0;
				while ((c = getchar()) != '\n')
				{
					input[n] = c;
					n++;
				}
				if (n == 0) break;
				flag = 1;
				input[n] = '\0';
				n = atoi(input);
				if (n == 0) continue;
				break;
			}
			if (flag == 1) {
				goods[i][15] = n % 128;
				goods[i][16] = n / 128;
			}
			getchar();
			getchar();
			break;
		case 3:
			compute_all(goods);
			printf("compute success!");
			getchar();
			getchar();
			break;
		case 4:
			rec_sort(goods, buffer_order);
			printf("sort success!");
			getchar();
			getchar();
			break;
		case 5:
			printf(" --------------------------------------------------------------------\n");
			printf("|rank|goods_name|discount|price_in|price_out|num_in|num_out|recommend|\n");
			for (i = 0; i < 30; i++)
			{
				strncpy(temp_info, buffer_order[i], 10);
				temp_info[10] = '\0';
				printf("|%-4d|",i+1);
				printf("%-10s|", temp_info);
				printf("%-8d|", *(buffer_order[i]+10));
				printf("%-8d|", *(buffer_order[i] + 11) + *(buffer_order[i] + 12)*128);
				printf("%-9d|", *(buffer_order[i] + 13) + *(buffer_order[i] + 14)*128);
				printf("%-6d|", *(buffer_order[i] + 15) + *(buffer_order[i] + 16) * 128);
				printf("%-7d|", *(buffer_order[i] + 17) + *(buffer_order[i] + 18) * 128);
				printf("%-9d|\n", *(buffer_order[i] + 19) + *(buffer_order[i] + 20) * 128);
			}
			printf(" --------------------------------------------------------------------\n");
			getchar();
			getchar(); 
			break;
		case 6:
			return;
		}
	}
}