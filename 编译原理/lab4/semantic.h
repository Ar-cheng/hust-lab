// #include "def.h"
#include "gene_objectcode.c"

#define DEBUG 0

int IN_LOOP = 0;
int return_flag = 0;
char *BREAK_NODE, *CONTINUE_NODE;

char *strcat0(char *s1, char *s2);
char *newAlias();
char *newLabel();
char *newTemp();
struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result);
struct codenode *genLabel(char *label);
struct codenode *genGoto(char *label);
struct codenode *merge(int num, ...);
void prnIR(struct codenode *head);
void semantic_error(int line, char *msg1, char *msg2);
void prn_symbol();
int searchSymbolTable(char *name);
int fillSymbolTable(char *name, char *alias, int level, int type, char flag, int offset);
int fill_Temp(char *name, int level, int type, char flag, int offset);
struct symbol_array_info *array_def(struct ASTNode *T, int type);
int array_read(struct ASTNode *T);
void ext_var_list(struct ASTNode *T);
int match_param(int i, struct ASTNode *T);
void boolExp(struct ASTNode *T);
void Exp(struct ASTNode *T);
void semantic_Analysis(struct ASTNode *T);
void semantic_Analysis0(struct ASTNode *T);