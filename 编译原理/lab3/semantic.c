#include "def.h"
#define DEBUG 0

int IN_LOOP = 0;
int return_flag = 0;
char *BREAK_NODE, *CONTINUE_NODE;

char *strcat0(char *s1, char *s2)
{
    static char result[10];
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *newAlias()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("v", s);
}

char *newLabel()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    return strcat0("label", s);
}

char *newTemp()
{
    static int no = 1;
    char s[10];
    snprintf(s, 10, "%d", no++);
    // itoa(no++, s, 10);
    return strcat0("temp", s);
}

// 生成一条TAC代码的结点组成的双向循环链表，返回头指针
struct codenode *genIR(int op, struct opn opn1, struct opn opn2, struct opn result)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = op;
    h->opn1 = opn1;
    h->opn2 = opn2;
    h->result = result;
    h->next = h->prior = h;
    return h;
}

// 生成一条标号语句，返回头指针
struct codenode *genLabel(char *label)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = LABEL;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

// 生成GOTO语句，返回头指针
struct codenode *genGoto(char *label)
{
    struct codenode *h = (struct codenode *)malloc(sizeof(struct codenode));
    h->op = GOTO;
    strcpy(h->result.id, label);
    h->next = h->prior = h;
    return h;
}

// 合并多个中间代码的双向循环链表，首尾相连
struct codenode *merge(int num, ...)
{
    struct codenode *h1, *h2, *p, *t1, *t2;
    va_list ap;
    va_start(ap, num);
    h1 = va_arg(ap, struct codenode *);
    while (--num > 0)
    {
        h2 = va_arg(ap, struct codenode *);
        if (h1 == NULL)
            h1 = h2;
        else if (h2)
        {
            t1 = h1->prior;
            t2 = h2->prior;
            t1->next = h2;
            t2->next = h1;
            h1->prior = t2;
            h2->prior = t1;
        }
    }
    va_end(ap);
    return h1;
}

// 输出中间代码
void prnIR(struct codenode *head)
{
    char opnstr1[32], opnstr2[32], resultstr[32];
    struct codenode *h = head;
    do
    {
        if (h->opn1.kind == INT)
            sprintf(opnstr1, "#%d", h->opn1.const_int);
        if (h->opn1.kind == FLOAT)
            sprintf(opnstr1, "#%f", h->opn1.const_float);
        if (h->opn1.kind == CHAR)
            sprintf(opnstr1, "#%c", h->opn1.const_char);
        if (h->opn1.kind == ID)
            sprintf(opnstr1, "%s", h->opn1.id);
        if (h->opn2.kind == INT)
            sprintf(opnstr2, "#%d", h->opn2.const_int);
        if (h->opn2.kind == FLOAT)
            sprintf(opnstr2, "#%f", h->opn2.const_float);
        if (h->opn2.kind == CHAR)
            sprintf(opnstr2, "#%c", h->opn2.const_char);
        if (h->opn2.kind == ID)
            sprintf(opnstr2, "%s", h->opn2.id);
        sprintf(resultstr, "%s", h->result.id);
        switch (h->op)
        {
        case ASSIGNOP:
            if (h->result.kind == ID && h->opn2.kind != ARRAY_READ)
            {
                printf("  %s := %s\n", resultstr, opnstr1);
            }
            else if (h->result.kind == ARRAY_READ)
            {
                printf("  %s[%s] := %s\n", resultstr, opnstr2, opnstr1);
            }
            else if (h->result.kind == ID && h->opn2.kind == ARRAY_READ)
            {

                printf("  %s := %s[%s]\n", resultstr, opnstr1, h->opn2.id);
            }
            break;
        case DMINUS:
            printf("  %s := %s - 1\n", resultstr, opnstr1);
            break;
        case DPLUS:
            printf("  %s := %s + 1\n", resultstr, opnstr1);
            break;
        case UMINUS:
            printf("  %s := -%s\n", resultstr, opnstr1);
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            printf("  %s := %s %c %s\n", resultstr, opnstr1,
                   h->op == PLUS ? '+' : h->op == MINUS ? '-' : h->op == STAR ? '*' : '\\', opnstr2);
            break;
        case FUNCTION:
            printf("\nFUNCTION %s :\n", h->result.id);
            break;
        case PARAM:
            printf("  PARAM %s\n", h->result.id);
            break;
        case LABEL:
            printf("LABEL %s :\n", h->result.id);
            break;
        case GOTO:
            printf("  GOTO %s\n", h->result.id);
            break;
        case JLE:
            printf("  IF %s <= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case JLT:
            printf("  IF %s < %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case JGE:
            printf("  IF %s >= %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case JGT:
            printf("  IF %s > %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case EQ:
            printf("  IF %s == %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case NEQ:
            printf("  IF %s != %s GOTO %s\n", opnstr1, opnstr2, resultstr);
            break;
        case ARG:
            printf("  ARG %s\n", h->result.id);
            break;
        case CALL:
            if (!strcmp(opnstr1, "write"))
                printf("  CALL  %s\n", opnstr1);
            else
                printf("  %s := CALL %s\n", resultstr, opnstr1);
            break;
        case RETURN:
            if (h->result.kind)
                printf("  RETURN %s\n", resultstr);
            else
                printf("  RETURN\n");
            break;
        }
        h = h->next;
    } while (h != head);
}
void semantic_error(int line, char *msg1, char *msg2)
{
    //这里可以只收集错误信息，最后一次显示
    printf("在%d行,%s %s\n", line, msg1, msg2);
}
void prn_symbol()
{ //显示符号表
    int i = 0;
    printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n");
    printf("%6s   %6s   %6s   %6s   %4s   %6s\n", "变量名", "别名", "层号", "类型", "标记", "偏移量");
    for (i = 0; i < symbolTable.index; i++)
    {
        if (!strcmp(symbolTable.symbols[i].name, " "))
            continue;
        printf("%6s %6s %6d ", symbolTable.symbols[i].name, symbolTable.symbols[i].alias, symbolTable.symbols[i].level);
        switch (symbolTable.symbols[i].type)
        {
        case INT:
            if (symbolTable.symbols[i].flag != 'A')
                printf("%6s", "int");
            else
                printf("%6s", "int[]");
            break;
        case FLOAT:
            if (symbolTable.symbols[i].flag != 'A')
                printf("%6s", "float");
            else
                printf("%6s", "float[]");
            break;
        case CHAR:
            if (symbolTable.symbols[i].flag != 'A')
                printf("%6s", "char");
            else
                printf("%6s", "char[]");
            break;
        default:
            break;
        }
        printf("  %4c", (symbolTable.symbols[i].flag));
        printf("  %6d\n", symbolTable.symbols[i].offset);
    }
    printf("-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-\n");
}

int searchSymbolTable(char *name)
{
    int i, flag = 0;
    for (i = symbolTable.index - 1; i >= 0; i--)
    {
        if (symbolTable.symbols[i].level == 0)
            flag = 1;
        if (flag && symbolTable.symbols[i].level == 1)
            continue; //跳过前面函数的形式参数表项
        if (!strcmp(symbolTable.symbols[i].name, name))
            return i;
    }
    return -1;
}
int fillSymbolTable(char *name, char *alias, int level, int type, char flag, int offset)
{
    //首先根据name查符号表，不能重复定义 重复定义返回-1
    int i;
    /*符号查重，考虑外部变量声明前有函数定义，
    其形参名还在符号表中，这时的外部变量与前函数的形参重名是允许的*/
    for (i = symbolTable.index - 1; i >= 0 && (symbolTable.symbols[i].level == level || level == 0); i--)
    {
        if (level == 0 && symbolTable.symbols[i].level == 1)
            continue; //外部变量和形参不必比较重名
        if (!strcmp(symbolTable.symbols[i].name, name))
            return -1;
    }
    //填写符号表内容
    strcpy(symbolTable.symbols[symbolTable.index].name, name);
    strcpy(symbolTable.symbols[symbolTable.index].alias, alias);
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++; //返回的是符号在符号表中的位置序号，中间代码生成时可用序号取到符号别名
}

//填写临时变量到符号表，返回临时变量在符号表中的位置
int fill_Temp(char *name, int level, int type, char flag, int offset)
{
    strcpy(symbolTable.symbols[symbolTable.index].name, "");
    strcpy(symbolTable.symbols[symbolTable.index].alias, name);
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++; //返回的是临时变量在符号表中的位置序号
}

struct symbol_array_info *array_def(struct ASTNode *T, int type)
{
    struct symbol_array_info *temp = (struct symbol_array_info *)malloc(sizeof(struct symbol_array_info));
    temp->dimension = 0;
    temp->type = type;
    while (T->kind == ARRAY_DEF)
    {
        temp->dimension++;
        // Exp(T->ptr[1]);
        if (T->ptr[1]->kind != INT)
        {
            semantic_error(T->pos, "", "数组下标需要为int类型");
            return NULL;
        }
        temp->diminfo[temp->dimension - 1] = T->ptr[1]->type_int;
        T = T->ptr[0];
    }
    strcpy(temp->id, T->type_id);
    // prn_symbol();
    return temp;
}

int array_read(struct ASTNode *T) //返回数据类型
{
    // printf("offset:%d",T->offset);
    struct opn opn1, opn2, result;
    struct ASTNode *T1 = T; //记录数组的开始结点

    int i = 0,
        j = 0, k;
    int rtn, tmp, tmp1;
    int record[MAXLENGTH]; //记录访问的每一维数的大小
    struct ASTNode *Node_Array[MAXLENGTH];
    int total = 0;
    while (T->kind == ARRAY_READ)
    {
        // semantic_Analysis(T->ptr[1]);
        // printf("IR:");
        // prnIR(T->ptr[1]->code);
        switch (T->ptr[1]->type)
        {
        case FLOAT:
        case CHAR:
            semantic_error(T->pos, "", "数组下标表达式非法");
            break;
        }
        Node_Array[i] = T->ptr[1];
        T = T->ptr[0];
        i++;
    }

    rtn = searchSymbolTable(T->type_id);

    if (rtn == -1)
    {
        semantic_error(T->pos, T->type_id, "数组未定义");
        return -1;
    }
    else if (symbolTable.symbols[rtn].flag == 'F')
    {
        semantic_error(T->pos, T->type_id, "函数名不能用下标访问");
        return -1;
    }
    else if (symbolTable.symbols[rtn].flag == 'V')
    {
        semantic_error(T->pos, T->type_id, "非数组变量，不能用下标访问");
        return -1;
    }
    else if (symbolTable.symbols[rtn].flag == 'P')
    {
        semantic_error(T->pos, T->type_id, "非数组变量，不能用下标访问");
        return -1;
    }
    else if (symbolTable.symbols[rtn].array_info->dimension != i)
    {
        semantic_error(T->pos, "", "数组维数错误");
        return -1;
    }

    for (j = 0; j < i; j++)
    {
        if (record[j] >= symbolTable.symbols[rtn].array_info->diminfo[j])
        {
            semantic_error(T->pos, "", "数组越界");
            return -1;
        }
        // int temp = 1;
        // for (k = j; k > 0; k--)
        // {
        //     temp *= symbolTable.symbols[rtn].array_info->diminfo[k - 1];
        // }
        // total += temp * record[j];
        // temp = 0;

        //record 3 2 1  k
        //diminfo 4 3 2  j
        //real 2 3 4
        // total += record[]
    }
    // prn_symbol();
    // printf("%d\n", Node_Array[i - 1]->kind);

    semantic_Analysis(Node_Array[i - 1]);

    T1->code = Node_Array[i-1]->code;

    for (j = i - 2; j >= 0; j--)
    {
        //先计算乘法,乘上前一位的元素上限
        T->place = fill_Temp(newTemp(), LEV, INT, 'T', Node_Array[j]->offset);
        strcpy(result.id, symbolTable.symbols[T->place].alias);
        result.kind = ID;

        opn2.kind = INT;
        opn2.const_int = symbolTable.symbols[rtn].array_info->diminfo[j];

        opn1.kind = ID;
        strcpy(opn1.id, symbolTable.symbols[Node_Array[j + 1]->place].alias);

        T1->code = merge(2, T1->code, genIR(STAR, opn1, opn2, result));

        //分析树的右半部分生成临时变量
        semantic_Analysis(Node_Array[j]);

        //再计算加法
        tmp = fill_Temp(newTemp(), LEV, INT, 'T', Node_Array[j]->offset);

        strcpy(result.id, symbolTable.symbols[tmp].alias);
        result.kind = ID;

        opn2.kind = ID;
        strcpy(opn2.id, symbolTable.symbols[Node_Array[j]->place].alias);

        opn1.kind = ID;
        strcpy(opn1.id, symbolTable.symbols[T->place].alias);

        // printf("tmp name : %s = %s + %s \n ", symbolTable.symbols[tmp].alias, symbolTable.symbols[T->place].alias, symbolTable.symbols[Node_Array[j]->place].alias);

        T1->code = merge(3, T1->code, Node_Array[j]->code, genIR(PLUS, opn1, opn2, result));
    }

    //计算总的偏移数，以字节为基本单位

    tmp1 = fill_Temp(newTemp(), LEV, INT, 'T', T->offset);

    strcpy(result.id, symbolTable.symbols[tmp1].alias);
    result.kind = ID;

    opn2.kind = INT;
    opn2.const_int = (symbolTable.symbols[rtn].array_info->type == CHAR ? 1 : 4);

    opn1.kind = ID;
    if(i==1)
        strcpy(opn1.id, symbolTable.symbols[Node_Array[i - 1]->place].alias);
    else
        strcpy(opn1.id, symbolTable.symbols[tmp].alias);

    T1->code = merge(2, T1->code, genIR(STAR, opn1, opn2, result));

    // prnIR(T1->code);

    T1->place = searchSymbolTable(T->type_id);
    symbolTable.symbols[T1->place].array_info->tartget = tmp1;

    // prn_symbol();

    return symbolTable.symbols[rtn].array_info->type;
}

void ext_var_list(struct ASTNode *T)
{ //处理变量列表
    int rtn, num = 1;
    struct ASTNode *T0;
    switch (T->kind)
    {
    case EXT_DEC_LIST:
        // if (DEBUG)
        //     printf("EXT_DEC_LIST \n");
        T->ptr[0]->type = T->type;                //将类型属性向下传递变量结点
        T->ptr[0]->offset = T->offset;            //外部变量的偏移量向下传递
        T->ptr[1]->type = T->type;                //将类型属性向下传递变量结点
        T->ptr[1]->offset = T->offset + T->width; //外部变量的偏移量向下传递
        T->ptr[1]->width = T->width;
        ext_var_list(T->ptr[0]);
        ext_var_list(T->ptr[1]);
        T->num = T->ptr[1]->num + 1;
        break;
    case ID:
        // if (DEBUG)
        //     printf("ID: \n");
        rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'V', T->offset); //最后一个变量名
        if (rtn == -1)
            semantic_error(T->pos, T->type_id, "变量重复定义");
        else
            T->place = rtn;
        T->num = 1;
        break;
    case ARRAY_DEF: //数组定义
        // if (DEBUG)
        //     printf("ARRAY_DEF: \n");
        rtn = fillSymbolTable(T->ptr[0]->type_id, newAlias(), LEV, T->type, 'A', T->offset); //最后一个变量名
        if (rtn == -1)
            semantic_error(T->pos, T->ptr[0]->type_id, "变量名重复定义");
        else if (T->ptr[1]->type != INT)
            semantic_error(T->pos, "", "数组大小不能为float或char");
        else if (T->ptr[1]->type_int <= 0 || !strcmp(T->ptr[1]->type_id, "UMINUS"))
        {
            semantic_error(T->pos, T->type_id, "数组大小不能为负值或0");
        }
        else
        {
            T->place = rtn;
            T->num = 1;
        }
        break;
    }
}

int match_param(int i, struct ASTNode *T)
{
    int j, num = symbolTable.symbols[i].paramnum;
    int type1, type2, pos = T->pos;
    T = T->ptr[0];
    if (num == 0 && T == NULL)
        return 1;
    for (j = 1; j <= num; j++)
    {
        if (!T)
        {
            semantic_error(pos, "", "函数调用参数太少!");
            return 0;
        }
        type1 = symbolTable.symbols[i + j].type; //形参类型
        type2 = T->ptr[0]->type;
        if (type1 != type2)
        {
            semantic_error(pos, "", "参数类型不匹配");
            return 0;
        }
        T = T->ptr[1];
    }
    if (T)
    { //num个参数已经匹配完，还有实参表达式
        semantic_error(pos, "", "函数调用参数太多!");
        return 0;
    }
    return 1;
}

void boolExp(struct ASTNode *T)
{ //布尔表达式，参考文献[2]p84的思想
    struct opn opn1, opn2, result;
    int op;
    int rtn;
    if (T)
    {
        switch (T->kind)
        {
        case INT:
            if (T->type_int != 0)
                T->code = genGoto(T->Etrue);
            else
                T->code = genGoto(T->Efalse);
            T->width = 0;
            break;
        case FLOAT:
            if (T->type_float != 0.0)
                T->code = genGoto(T->Etrue);
            else
                T->code = genGoto(T->Efalse);
            T->width = 0;
            break;
        case CHAR:
            if (T->type_char[0] != '0')
                T->code = genGoto(T->Etrue);
            else
                T->code = genGoto(T->Efalse);
            break;

        case ID: //查符号表，获得符号表中的位置，类型送type
            rtn = searchSymbolTable(T->type_id);
            if (rtn == -1)
                semantic_error(T->pos, T->type_id, "变量未定义");
            if (symbolTable.symbols[rtn].flag == 'F')
                semantic_error(T->pos, T->type_id, "是函数名，类型不匹配");
            else
            {
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[rtn].alias);
                opn1.offset = symbolTable.symbols[rtn].offset;
                opn2.kind = INT;
                opn2.const_int = 0;
                result.kind = ID;
                strcpy(result.id, T->Etrue);
                T->code = genIR(NEQ, opn1, opn2, result);
                T->code = merge(2, T->code, genGoto(T->Efalse));
            }
            T->width = 0;
            break;
        case RELOP: //处理关系运算表达式,2个操作数都按基本表达式处理
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            Exp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            Exp(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn2.kind = ID;
            strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            result.kind = ID;
            strcpy(result.id, T->Etrue);
            if (strcmp(T->type_id, "<") == 0)
                op = JLT;
            else if (strcmp(T->type_id, "<=") == 0)
                op = JLE;
            else if (strcmp(T->type_id, ">") == 0)
                op = JGT;
            else if (strcmp(T->type_id, ">=") == 0)
                op = JGE;
            else if (strcmp(T->type_id, "==") == 0)
                op = EQ;
            else if (strcmp(T->type_id, "!=") == 0)
                op = NEQ;
            T->code = genIR(op, opn1, opn2, result);
            T->code = merge(4, T->ptr[0]->code, T->ptr[1]->code, T->code, genGoto(T->Efalse));
            break;
        case AND:
        case OR:
            if (T->kind == AND)
            {
                strcpy(T->ptr[0]->Etrue, newLabel());
                strcpy(T->ptr[0]->Efalse, T->Efalse);
            }
            else
            {
                strcpy(T->ptr[0]->Etrue, T->Etrue);
                strcpy(T->ptr[0]->Efalse, newLabel());
            }
            strcpy(T->ptr[1]->Etrue, T->Etrue);
            strcpy(T->ptr[1]->Efalse, T->Efalse);
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            boolExp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            boolExp(T->ptr[1]);
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            if (T->kind == AND)
                T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
            else
                T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Efalse), T->ptr[1]->code);
            break;
        case NOT:
            strcpy(T->ptr[0]->Etrue, T->Efalse);
            strcpy(T->ptr[0]->Efalse, T->Etrue);
            boolExp(T->ptr[0]);
            T->code = T->ptr[0]->code;
            break;
        default:
            break;
        }
    }
}

void Exp(struct ASTNode *T)
{ //处理基本表达式，参考文献[2]p82的思想
    // printf("Exp-kind:%d\n",T->kind);
    int rtn, num, width,op;
    char label1[30] ,label2[30];
    struct ASTNode *T0;
    struct opn opn1, opn2, result;
    struct opn result_1;
    if (T)
    {
        switch (T->kind)
        {
        case ID: //查符号表，获得符号表中的位置，类型送type
            rtn = searchSymbolTable(T->type_id);
            // printf("TYPE_ID:   %s \n",T->type_id);
            if (rtn == -1)
                semantic_error(T->pos, T->type_id, "变量未定义");
            if (symbolTable.symbols[rtn].flag == 'F')
            {
                semantic_error(T->pos, T->type_id, "对函数名采用非函数调用形式  ");
            }
            else if (symbolTable.symbols[rtn].flag == 'A')
                semantic_error(T->pos, T->type_id, "访问数组方式错误");
            else
            {
                T->place = rtn; //结点保存变量在符号表中的位置
                T->code = NULL; //标识符不需要生成TAC
                T->type = symbolTable.symbols[rtn].type;
                T->offset = symbolTable.symbols[rtn].offset;
                T->width = 0; //未再使用新单元
            }
            break;

        case INT:
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为整常量生成一个临时变量
            T->type = INT;
            opn1.kind = INT;
            opn1.const_int = T->type_int;
            // printf("T->typeint:%d\n",T->type_int);
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = genIR(ASSIGNOP, opn1, opn2, result);
            T->width = 4;
            break;

        case FLOAT:
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset); //为浮点常量生成一个临时变量
            T->type = FLOAT;
            opn1.kind = FLOAT;
            opn1.const_float = T->type_float;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = genIR(ASSIGNOP, opn1, opn2, result);
            T->width = 4;
            break;

        case CHAR:
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->type = CHAR;
            opn1.kind = CHAR;
            opn1.const_char = T->type_char[0];
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = genIR(ASSIGNOP, opn1, opn2, result);
            T->width = 1;
            break;

        case ASSIGNOP:

            if (T->ptr[0]->kind == ARRAY_READ && T->ptr[1]->kind == ARRAY_READ)
            {
                semantic_error(T->pos, "", "赋值语句只允许一侧为数组");
            }

            if (T->ptr[0]->kind != ID && T->ptr[0]->kind != ARRAY_READ)
            {
                semantic_error(T->pos, "", "赋值语句需要左值");
            }
            else
            {
                Exp(T->ptr[0]); //处理左值，例中仅为变量
                T->ptr[1]->offset = T->offset;
                Exp(T->ptr[1]);

                // printf("kind1:%d   ,kind2:%d  \n", T->ptr[0]->type, T->ptr[1]->type);
                if (T->ptr[0]->type != T->ptr[1]->type && T->ptr[0]->kind != ARRAY_READ && T->ptr[1]->kind != ARRAY_READ)
                {
                    semantic_error(T->pos, "", "赋值语句类型不匹配");
                    break;
                }
                T->type = T->ptr[0]->type;
                T->width = T->ptr[1]->width;
                T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);
                //add
                T->place = T->ptr[0]->place;
                //?
                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias); //右值一定是个变量或临时变量
                opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;

                opn2.kind = ID;

                // printf("KIND: %d , %d \n", T->ptr[0]->kind, T->ptr[1]->kind);
                //     printf("------------------------\n");
                if (T->ptr[0]->kind == ID && T->ptr[1]->kind != ARRAY_READ)
                {
                    result.kind = ID;
                    strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
                }
                else if (T->ptr[0]->kind == ARRAY_READ)
                {
                    result.kind = ARRAY_READ;
                    strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
                    opn2.kind = ID;
                    strcpy(opn2.id, symbolTable.symbols[symbolTable.symbols[T->ptr[0]->place].array_info->tartget].alias);
                }
                else if (T->ptr[0]->kind == ID && T->ptr[1]->kind == ARRAY_READ)
                {
                    result.kind = ID;
                    strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
                    opn2.kind = ARRAY_READ;
                    strcpy(opn2.id, symbolTable.symbols[symbolTable.symbols[T->ptr[1]->place].array_info->tartget].alias);
                }
                result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
                T->code = merge(2, T->code, genIR(ASSIGNOP, opn1, opn2, result));

            }
            break;
        case PLUS_ASSIGNOP:
        case MINUS_ASSIGNOP:
        case STAR_ASSIGNOP:
        case DIV_ASSIGNOP:
            if (T->ptr[0]->kind != ID && T->ptr[0]->kind != ARRAY_READ)
            {
                semantic_error(T->pos, "", "赋值语句需要左值");
            }
            else
            {
                T->ptr[0]->offset = T->offset;
                Exp(T->ptr[0]);
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                Exp(T->ptr[1]);
                T->type = T->ptr[0]->type;
                T->width = T->ptr[1]->width;
                T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);

                opn1.kind = ID;
                strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
                opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;

                opn2.kind = ID;
                strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
                opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;

                result.kind = ID;
                strcpy(result.id, newTemp());
                if (T->kind == PLUS_ASSIGNOP)
                    T->code = merge(2, T->code, genIR(PLUS, opn1, opn2, result));
                else if (T->kind == MINUS_ASSIGNOP)
                    T->code = merge(2, T->code, genIR(MINUS, opn1, opn2, result));
                else if (T->kind == STAR_ASSIGNOP)
                    T->code = merge(2, T->code, genIR(STAR, opn1, opn2, result));
                else if (T->kind == DIV_ASSIGNOP)
                    T->code = merge(2, T->code, genIR(DIV, opn1, opn2, result));

                result_1.kind = ID;
                strcpy(result_1.id, symbolTable.symbols[T->ptr[0]->place].alias);
                result_1.type = T->type;
                result_1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
                T->code = merge(2, T->code, genIR(ASSIGNOP, result, opn2, result_1));
            }
            break;

        case AND:   //按算术表达式方式计算布尔值，未写完
            T->type = INT;
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->code = T->ptr[0]->code;
           
            strcpy(label1, newLabel());
            strcpy(label2, newLabel());
           
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn1.type = T->ptr[0]->type;

            opn2.kind = INT;
            opn2.const_int = 0;
            result.kind = ID;
            strcpy(result.id, label1);
            op = EQ;
            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));
            
            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            Exp(T->ptr[1]);
            T->code = merge(2, T->code, T->ptr[1]->code);
            
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            opn1.type = T->ptr[1]->type;

            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));
          
            opn1.kind = INT;
            opn1.const_int = 1;

            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.type = T->type;
            result.offset = symbolTable.symbols[T->place].offset;
            
            T->code = merge(4, T->code, genIR(ASSIGNOP, opn1, opn2, result), genGoto(label2), genLabel(label1));
            
            
            opn1.kind = INT;
            opn1.const_int = 0;
            opn1.type = INT;

            T->code = merge(3, T->code, genIR(ASSIGNOP, opn1, opn2, result), genLabel(label2));
            break;
        case OR:    //按算术表达式方式计算布尔值，未写完
            // Exp(T->ptr[0]);
            // Exp(T->ptr[1]);
            // break;
            T->type = INT;
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            
            T->code = T->ptr[0]->code;
            strcpy(label1, newLabel());
            strcpy(label2, newLabel());
           
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn1.type = T->ptr[0]->type;

            opn2.kind = INT;
            opn2.const_int = 0;
            result.kind = ID;
            strcpy(result.id, label1);
            op = NEQ;
            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));

            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            Exp(T->ptr[1]);
            T->code = merge(2, T->code, T->ptr[1]->code);
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn1.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            opn1.type = T->ptr[1]->type;

            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));
            opn1.kind = INT;
            opn1.const_int = 0;
            
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.type = T->type;
            result.offset = symbolTable.symbols[T->place].offset;
            
            T->code = merge(4, T->code, genIR(ASSIGNOP, opn1, opn2, result), genGoto(label2), genLabel(label1));
            
            opn1.kind = INT;
            opn1.const_int = 1;
            opn1.type = INT;

            T->code = merge(3, T->code, genIR(ASSIGNOP, opn1, opn2, result), genLabel(label2));
            break;

        case RELOP: //按算术表达式方式计算布尔值，未写完
            T->type = INT;
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            Exp(T->ptr[1]);

            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code);
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn2.kind = ID;
            strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            
            result.kind = ID;
            strcpy(result.id, newLabel());
            if (strcmp(T->type_id, "<") == 0)
                op = JLT;
            else if (strcmp(T->type_id, "<=") == 0)
                op = JLE;
            else if (strcmp(T->type_id, ">") == 0)
                op = JGT;
            else if (strcmp(T->type_id, ">=") == 0)
                op = JGE;
            else if (strcmp(T->type_id, "==") == 0)
                op = EQ;
            else if (strcmp(T->type_id, "!=") == 0)
                op = NEQ;
            T->code = merge(2, T->code, genIR(op, opn1, opn2, result));
            
            opn1.kind = INT;
            opn1.const_int = 0;
            
            result_1.kind = ID;
            strcpy(result_1.id, symbolTable.symbols[T->place].alias);
            result_1.offset = symbolTable.symbols[T->place].offset;
            
            strcpy(label2, newLabel());
            
            T->code = merge(4, T->code, genIR(ASSIGNOP, opn1, opn2, result_1), genGoto(label2), genLabel(result.id));
            opn1.const_int = 1;
            
            T->code = merge(3, T->code, genIR(ASSIGNOP, opn1, opn2, result_1), genLabel(label2));
            break;

            // T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            // T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            // T->type = INT;
            // Exp(T->ptr[0]);
            // Exp(T->ptr[1]);

            // break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->ptr[1]->offset = T->offset + T->ptr[0]->width;
            Exp(T->ptr[1]);
            //判断T->ptr[0]，T->ptr[1]类型是否正确，可能根据运算符生成不同形式的代码，给T的type赋值
            //下面的类型属性计算，没有考虑错误处理情况
            if (T->ptr[0]->type == FLOAT && T->ptr[1]->type == FLOAT)
                T->type = FLOAT, T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
            else if (T->ptr[0]->type == INT && T->ptr[1]->type == INT)
                T->type = INT, T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
            else
            {
                semantic_error(T->pos, "", "运算符左右变量类型不匹配");
                break;
            }
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->ptr[0]->width + T->ptr[1]->width);
            opn1.kind = ID;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);
            opn1.type = T->ptr[0]->type;
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            opn2.kind = ID;
            strcpy(opn2.id, symbolTable.symbols[T->ptr[1]->place].alias);
            opn2.type = T->ptr[1]->type;
            opn2.offset = symbolTable.symbols[T->ptr[1]->place].offset;
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.type = T->type;
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = merge(3, T->ptr[0]->code, T->ptr[1]->code, genIR(T->kind, opn1, opn2, result));
            T->width = T->ptr[0]->width + T->ptr[1]->width + (T->type == CHAR ? 1 : 4);

            // printf("RESULT_ID: %s, OPN1_ID,%s, OPN2_ID: %s \n",result.id,opn1.id,opn2.id);
            // prnIR(T->code);
            // prn_symbol();
            // printf("%s , %s \n", opn1.id, opn2.id);

            break;
        case NOT: //未写完整
            strcpy(T->ptr[0]->Etrue, T->Efalse);
            strcpy(T->ptr[0]->Efalse, T->Etrue);
            boolExp(T->ptr[0]);
            T->code = T->ptr[0]->code;
            break;

        case UMINUS: //未写完整
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);

            opn1.kind = ID;
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);

            result.kind = ID;
            result.offset = symbolTable.symbols[T->place].offset;
            strcpy(result.id, symbolTable.symbols[T->place].alias);

            T->type = T->ptr[0]->type;
            T->code = merge(2, T->ptr[0]->code, genIR(UMINUS, opn1, opn2, result));

            switch (T->type)
            {
            case INT:
                T->width = T->ptr[0]->width + 4;
            case CHAR:
                T->width = T->ptr[0]->width + 1;
            case FLOAT:
                T->width = T->ptr[0]->width + 4;
            }

            break;

        case DPLUS_EXP:
        case EXP_DPLUS:
            if (T->ptr[0]->kind != ID)
            {
                semantic_error(T->pos, "", "自增语句对象需要为左值");
                break;
            }

            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);

            opn1.kind = ID;
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);

            result.kind = ID;
            result.offset = symbolTable.symbols[T->place].offset;
            strcpy(result.id, symbolTable.symbols[T->place].alias);

            T->type = T->ptr[0]->type;
            T->code = merge(2, T->ptr[0]->code, genIR(DPLUS, opn1, opn2, result));
            //生成tempn = v + 1
            //下面还需要v = tempn
            T->code = merge(2, T->code, genIR(ASSIGNOP, result, opn2, opn1));

            switch (T->type)
            {
            case INT:
                T->width = T->ptr[0]->width + 4;
            case CHAR:
                T->width = T->ptr[0]->width + 1;
            case FLOAT:
                T->width = T->ptr[0]->width + 4;
            }

            break;

        case DMINUS_EXP:
        case EXP_DMINUS:
            if (T->ptr[0]->kind != ID)
            {
                semantic_error(T->pos, "", "自减语句对象需要为左值");
                break;
            }
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset);
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);

            opn1.kind = ID;
            opn1.offset = symbolTable.symbols[T->ptr[0]->place].offset;
            strcpy(opn1.id, symbolTable.symbols[T->ptr[0]->place].alias);

            result.kind = ID;
            result.offset = symbolTable.symbols[T->place].offset;
            strcpy(result.id, symbolTable.symbols[T->place].alias);

            T->type = T->ptr[0]->type;
            T->code = merge(2, T->ptr[0]->code, genIR(DMINUS, opn1, opn2, result));
            //生成tempn = v -1
            //下面还需要v = tempn

            T->code = merge(2, T->code, genIR(ASSIGNOP, result, opn2, opn1));

            switch (T->type)
            {
            case INT:
                T->width = T->ptr[0]->width + 4;
            case CHAR:
                T->width = T->ptr[0]->width + 1;
            case FLOAT:
                T->width = T->ptr[0]->width + 4;
            }

            break;

        case FUNC_CALL: //根据T->type_id查出函数的定义，如果语言中增加了实验教材的read，write需要单独处理一下
            // printf("fasfasf!!!!!!11\n");
            rtn = searchSymbolTable(T->type_id);
            if (rtn == -1)
            {
                semantic_error(T->pos, T->type_id, "函数未定义");
                break;
            }
            if (symbolTable.symbols[rtn].flag != 'F')
            {
                semantic_error(T->pos, T->type_id, "调用对象不是函数");
                break;
            }
            T->type = symbolTable.symbols[rtn].type;
            width = T->type == INT ? (CHAR ? 1 : 4) : 8; //存放函数返回值的单数字节数
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                Exp(T->ptr[0]);                      //处理所有实参表达式求值，及类型
                T->width = T->ptr[0]->width + width; //累加上计算实参使用临时变量的单元数
                T->code = T->ptr[0]->code;
            }
            else
            {
                T->width = width;
                T->code = NULL;
            }
            match_param(rtn, T); //处理所有参数的匹配
                //处理参数列表的中间代码
            T0 = T->ptr[0];
            while (T0)
            {
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
                result.offset = symbolTable.symbols[T0->ptr[0]->place].offset;
                T->code = merge(2, T->code, genIR(ARG, opn1, opn2, result));
                T0 = T0->ptr[1];
            }
            T->place = fill_Temp(newTemp(), LEV, T->type, 'T', T->offset + T->width - width);
            opn1.kind = ID;
            strcpy(opn1.id, T->type_id); //保存函数名
            opn1.offset = rtn;           //这里offset用以保存函数定义入口,在目标代码生成时，能获取相应信息
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[T->place].alias);
            result.offset = symbolTable.symbols[T->place].offset;
            T->code = merge(2, T->code, genIR(CALL, opn1, opn2, result)); //生成函数调用中间代码
            break;
        case ARGS: //此处仅处理各实参表达式的求值的代码序列，不生成ARG的实参系列
            T->ptr[0]->offset = T->offset;
            Exp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            T->code = T->ptr[0]->code;
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                Exp(T->ptr[1]);
                T->width += T->ptr[1]->width;
                T->code = merge(2, T->code, T->ptr[1]->code);
            }
            break;

        case ARRAY_READ: //数组访问
            if ((rtn = array_read(T)) != -1)
                T->type = rtn;
            break;
        }
    }
}

void semantic_Analysis(struct ASTNode *T)
{ //对抽象语法树的先根遍历,按display的控制结构修改完成符号表管理和语义检查和TAC生成（语句部分）
    int rtn, num, width;
    struct ASTNode *T0;
    struct ASTNode *T1, *T2, *T3;
    struct opn opn1, opn2, result;
    if (T)
    {
        // printf("T->kind: %d \n", T->kind);
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            if (!T->ptr[0])
                break;
            T->ptr[0]->offset = T->offset;
            semantic_Analysis(T->ptr[0]); //访问外部定义列表中的第一个
            T->code = T->ptr[0]->code;
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
                semantic_Analysis(T->ptr[1]); //访问该外部定义列表中的其它外部定义
                T->code = merge(2, T->code, T->ptr[1]->code);
            }
            break;
        case EXT_VAR_DEF: //处理外部说明,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
            // printf("%s\n", T->ptr[1]->type_id);
            if (!strcmp(T->ptr[0]->type_id, "int"))
            {
                T->type = T->ptr[1]->type = INT;
                T->ptr[1]->width = 4;
            }
            if (!strcmp(T->ptr[0]->type_id, "float"))
            {
                T->type = T->ptr[1]->type = FLOAT;
                T->ptr[1]->width = 4;
            }
            if (!strcmp(T->ptr[0]->type_id, "char"))
            {
                T->type = T->ptr[1]->type = CHAR;
                T->ptr[1]->width = 1;
            }
            T->ptr[1]->offset = T->offset;                  //这个外部变量的偏移量向下传
            ext_var_list(T->ptr[1]);                        //处理外部变量说明中的标识符序列
            T->width = (T->ptr[1]->width) * T->ptr[1]->num; //计算这个外部变量说明的宽度
            T->code = NULL;                                 //这里假定外部变量不支持初始化
            break;
        case FUNC_DEF: //填写函数定义信息到符号表
            if (!strcmp(T->ptr[0]->type_id, "int"))
            //获取函数返回类型送到含函数名、参数的结点
            {
                T->ptr[1]->type = INT;
                return_flag++;
            }
            if (!strcmp(T->ptr[0]->type_id, "float"))
            {
                T->ptr[1]->type = FLOAT;
                return_flag++;
            }
            if (!strcmp(T->ptr[0]->type_id, "char"))
            {
                T->ptr[1]->type = CHAR;
                return_flag++;
            }
            T->width = 0;                  //函数的宽度设置为0，不会对外部变量的地址分配产生影响
            T->offset = DX;                //设置局部变量在活动记录中的偏移量初值
            semantic_Analysis(T->ptr[1]);  //处理函数名和参数结点部分，这里不考虑用寄存器传递参数
            T->offset += T->ptr[1]->width; //用形参单元宽度修改函数局部变量的起始偏移量
            T->ptr[2]->offset = T->offset;
            strcpy(T->ptr[2]->Snext, newLabel()); //函数体语句执行结束后的位置属性
            semantic_Analysis(T->ptr[2]);         //处理函数体结点
            //计算活动记录大小,这里offset属性存放的是活动记录大小，不是偏移
            symbolTable.symbols[T->ptr[1]->place].offset = T->offset + T->ptr[2]->width;
            T->code = merge(3, T->ptr[1]->code, T->ptr[2]->code, genLabel(T->ptr[2]->Snext)); //函数体的代码作为函数的代码
            break;
        case FUNC_DEC:                                                           //根据返回类型，函数名填写符号表
            rtn = fillSymbolTable(T->type_id, newAlias(), LEV, T->type, 'F', 0); //函数不在数据区中分配单元，偏移量为0
            if (rtn == -1)
            {
                semantic_error(T->pos, T->type_id, "函数重复定义");
                break;
            }
            else
                T->place = rtn;
            result.kind = ID;
            strcpy(result.id, T->type_id);
            result.offset = rtn;
            T->code = genIR(FUNCTION, opn1, opn2, result); //生成中间代码：FUNCTION 函数名
            T->offset = DX;                                //设置形式参数在活动记录中的偏移量初值
            if (T->ptr[0])
            { //判断是否有参数
                T->ptr[0]->offset = T->offset;
                semantic_Analysis(T->ptr[0]); //处理函数参数列表
                T->width = T->ptr[0]->width;
                symbolTable.symbols[rtn].paramnum = T->ptr[0]->num;
                T->code = merge(2, T->code, T->ptr[0]->code); //连接函数名和参数代码序列
            }
            else
                symbolTable.symbols[rtn].paramnum = 0, T->width = 0;
            break;
        case PARAM_LIST: //处理函数形式参数列表
            T->ptr[0]->offset = T->offset;
            semantic_Analysis(T->ptr[0]);
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                semantic_Analysis(T->ptr[1]);
                T->num = T->ptr[0]->num + T->ptr[1]->num;             //统计参数个数
                T->width = T->ptr[0]->width + T->ptr[1]->width;       //累加参数单元宽度
                T->code = merge(2, T->ptr[0]->code, T->ptr[1]->code); //连接参数代码
            }
            else
            {
                T->num = T->ptr[0]->num;
                T->width = T->ptr[0]->width;
                T->code = T->ptr[0]->code;
            }
            break;
        case PARAM_DEC:
            rtn = fillSymbolTable(T->ptr[1]->type_id, newAlias(), 1, T->ptr[0]->type, 'P', T->offset);
            if (rtn == -1)
                semantic_error(T->ptr[1]->pos, T->ptr[1]->type_id, "参数名重复定义");
            else
                T->ptr[1]->place = rtn;
            T->num = 1;                                //参数个数计算的初始值
            T->width = T->ptr[0]->type == INT ? 4 : 8; //参数宽度
            result.kind = ID;
            strcpy(result.id, symbolTable.symbols[rtn].alias);
            result.offset = T->offset;
            T->code = genIR(PARAM, opn1, opn2, result); //生成：FUNCTION 函数名
            break;
        case COMP_STM:
            LEV++;
            //设置层号加1，并且保存该层局部变量在符号表中的起始位置在symbol_scope_TX
            symbol_scope_TX.TX[symbol_scope_TX.top++] = symbolTable.index;
            T->width = 0;
            T->code = NULL;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                semantic_Analysis(T->ptr[0]); //处理该层的局部变量DEF_LIST
                T->width += T->ptr[0]->width;
                T->code = T->ptr[0]->code;
            }
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->width;
                strcpy(T->ptr[1]->Snext, T->Snext); //S.next属性向下传递
                semantic_Analysis(T->ptr[1]);       //处理复合语句的语句序列
                T->width += T->ptr[1]->width;
                T->code = merge(2, T->code, T->ptr[1]->code);
            }
            if (DEBUG)
                prn_symbol(); //c在退出一个符合语句前显示的符号表

            LEV--;                                                         //出复合语句，层号减1
            symbolTable.index = symbol_scope_TX.TX[--symbol_scope_TX.top]; //删除该作用域中的符号
            break;
        case DEF_LIST:
            // if (DEBUG)
            //     printf("DEF_LIST:\n");
            T->code = NULL;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                semantic_Analysis(T->ptr[0]); //处理一个局部变量定义
                T->code = T->ptr[0]->code;
                T->width = T->ptr[0]->width;
            }
            if (T->ptr[1])
            {
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                semantic_Analysis(T->ptr[1]); //处理剩下的局部变量定义
                T->code = merge(2, T->code, T->ptr[1]->code);
                T->width += T->ptr[1]->width;
            }
            break;
        case VAR_DEF: //处理一个局部变量定义,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
            // if (DEBUG)
            //     printf("VAR_DEF:\n");
            // printf("type_id:%s", T->ptr[0]->type_id);
            T->code = NULL;
            if (!strcmp(T->ptr[0]->type_id, "int"))
            {
                T->ptr[1]->type = INT;
                width = 4;
            }
            if (!strcmp(T->ptr[0]->type_id, "float"))
            {
                T->ptr[1]->type = FLOAT;
                width = 4;
            }
            if (!strcmp(T->ptr[0]->type_id, "char"))
            {
                T->ptr[1]->type = CHAR;
                width = 1;
            }
            T0 = T->ptr[1]; //T0为变量名列表子树根指针，对ID、ASSIGNOP类结点在登记到符号表，作为局部变量
            num = 0;
            T0->offset = T->offset;
            T->width = 0;
            if (T->ptr[1]->type == CHAR)
                width = 1;
            else
                width = 4;
            while (T0)
            { //处理所以DEC_LIST结点
                num++;
                T0->ptr[0]->type = T0->type; //类型属性向下传递
                if (T0->ptr[1])
                    T0->ptr[1]->type = T0->type;
                T0->ptr[0]->offset = T0->offset; //类型属性向下传递
                if (T0->ptr[1])
                    T0->ptr[1]->offset = T0->offset + width;
                if (T0->ptr[0]->kind == ID)
                {
                    rtn = fillSymbolTable(T0->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
                    if (rtn == -1)
                        semantic_error(T0->ptr[0]->pos, T0->ptr[0]->type_id, "变量重复定义");
                    else
                        T0->ptr[0]->place = rtn;
                    T->width += width;
                }
                else if (T0->ptr[0]->kind == ASSIGNOP)
                {
                    rtn = fillSymbolTable(T0->ptr[0]->ptr[0]->type_id, newAlias(), LEV, T0->ptr[0]->type, 'V', T->offset + T->width); //此处偏移量未计算，暂时为0
                    if (rtn == -1)
                        semantic_error(T0->ptr[0]->ptr[0]->pos, T0->ptr[0]->ptr[0]->type_id, "变量重复定义");
                    else
                    {
                        T0->ptr[0]->place = rtn;
                        T0->ptr[0]->ptr[1]->offset = T->offset + T->width + width;
                        Exp(T0->ptr[0]->ptr[1]);
                        opn1.kind = ID;
                        strcpy(opn1.id, symbolTable.symbols[T0->ptr[0]->ptr[1]->place].alias);
                        result.kind = ID;
                        strcpy(result.id, symbolTable.symbols[T0->ptr[0]->place].alias);
                        T->code = merge(3, T->code, T0->ptr[0]->ptr[1]->code, genIR(ASSIGNOP, opn1, opn2, result));
                    }
                    T->width += width + T0->ptr[0]->ptr[1]->width;
                }
                else if (T0->ptr[0]->kind == ARRAY_DEF)
                {
                    // printf("fsaf%s \n", T0->ptr[0]->type_id);
                    struct symbol_array_info *array = array_def(T0->ptr[0], T0->type);
                    if (array)
                    {
                        // printf("%d %s %d \n",array->dimension , array->id , array->type);

                        int value = fillSymbolTable(array->id, newAlias(), LEV, array->type, 'A', T->offset + T->width);
                        if (value == -1)
                            semantic_error(T0->pos, array->id, "重复定义的数组变量");
                        else
                        {
                            symbolTable.symbols[value].array_info = array;
                            T0->ptr[0]->place = rtn;
                        }
                        T->width += width;
                    }
                }
                T0 = T0->ptr[1];
            }
            break;
        case STM_LIST:
            if (!T->ptr[0])
            {
                // T->code = NULL;
                T->width = 0;
                break;
            }              //空语句序列
            if (T->ptr[1]) //2条以上语句连接，生成新标号作为第一条语句结束后到达的位置
                strcpy(T->ptr[0]->Snext, newLabel());
            else //语句序列仅有一条语句，S.next属性向下传递
                strcpy(T->ptr[0]->Snext, T->Snext);
            T->ptr[0]->offset = T->offset;
            semantic_Analysis(T->ptr[0]);
            T->code = T->ptr[0]->code;
            T->width = T->ptr[0]->width;
            if (T->ptr[1])
            { //2条以上语句连接,S.next属性向下传递
                strcpy(T->ptr[1]->Snext, T->Snext);
                T->ptr[1]->offset = T->offset; //顺序结构共享单元方式
                                               //                  T->ptr[1]->offset=T->offset+T->ptr[0]->width; //顺序结构顺序分配单元方式
                semantic_Analysis(T->ptr[1]);
                // 序列中第1条为表达式语句，返回语句，复合语句时，第2条前不需要标号
                if (T->ptr[0]->kind == RETURN || T->ptr[0]->kind == EXP_STMT || T->ptr[0]->kind == COMP_STM)
                    T->code = merge(2, T->code, T->ptr[1]->code);
                else
                    T->code = merge(3, T->code, genLabel(T->ptr[0]->Snext), T->ptr[1]->code);
                if (T->ptr[1]->width > T->width)
                    T->width = T->ptr[1]->width; //顺序结构共享单元方式
                                                 //                        T->width+=T->ptr[1]->width;//顺序结构顺序分配单元方式
            }
            break;
        case IF_THEN:
            strcpy(T->ptr[0]->Etrue, newLabel()); //设置条件语句真假转移位置
            strcpy(T->ptr[0]->Efalse, T->Snext);
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            boolExp(T->ptr[0]);
            T->width = T->ptr[0]->width;
            strcpy(T->ptr[1]->Snext, T->Snext);
            semantic_Analysis(T->ptr[1]); //if子句
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
            break; //控制语句都还没有处理offset和width属性
        case IF_THEN_ELSE:
            strcpy(T->ptr[0]->Etrue, newLabel()); //设置条件语句真假转移位置
            strcpy(T->ptr[0]->Efalse, newLabel());
            T->ptr[0]->offset = T->ptr[1]->offset = T->ptr[2]->offset = T->offset;
            boolExp(T->ptr[0]); //条件，要单独按短路代码处理
            T->width = T->ptr[0]->width;
            strcpy(T->ptr[1]->Snext, T->Snext);
            semantic_Analysis(T->ptr[1]); //if子句
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            strcpy(T->ptr[2]->Snext, T->Snext);
            semantic_Analysis(T->ptr[2]); //else子句
            if (T->width < T->ptr[2]->width)
                T->width = T->ptr[2]->width;
            T->code = merge(6, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code,
                            genGoto(T->Snext), genLabel(T->ptr[0]->Efalse), T->ptr[2]->code);
            break;
        case WHILE:
            strcpy(T->ptr[0]->Etrue, newLabel()); //子结点继承属性的计算
            strcpy(T->ptr[0]->Efalse, T->Snext);
            T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
            boolExp(T->ptr[0]); //循环条件，要单独按短路代码处理
            T->width = T->ptr[0]->width;
            strcpy(T->ptr[1]->Snext, newLabel());
            IN_LOOP++;

            BREAK_NODE = T->Snext;
            CONTINUE_NODE = T->ptr[1]->Snext;

            semantic_Analysis(T->ptr[1]); //循环体
            if (T->width < T->ptr[1]->width)
                T->width = T->ptr[1]->width;
            T->code = merge(5, genLabel(T->ptr[1]->Snext), T->ptr[0]->code,
                            genLabel(T->ptr[0]->Etrue), T->ptr[1]->code, genGoto(T->ptr[1]->Snext));
            IN_LOOP--;
            break;

        case FOR:
            T0 = T->ptr[0];
            T1 = T0->ptr[0];
            T2 = T0->ptr[1];
            T3 = T0->ptr[2];
            T0->offset = T->offset;
            T1->offset = T0->offset;
            Exp(T1);
            T0->width = T1->width;
            // 循环条件
            strcpy(T2->Etrue, newLabel());
            strcpy(T2->Efalse, T->Snext);
            T2->offset = T0->offset + T0->width;
            boolExp(T2);
            if (T0->width < T2->width)
                T0->width = T2->width;
            // 循环体
            strcpy(T->ptr[1]->Snext, newLabel());
            BREAK_NODE = T->Snext;
            CONTINUE_NODE = T->ptr[1]->Snext;
            semantic_Analysis(T->ptr[1]);

            T3->offset = T0->offset + T0->width;
            strcpy(T3->Snext, newLabel());
            semantic_Analysis(T3);

            if (T0->width < T3->width)
                T0->width = T3->width;
            if (T0->width > T->ptr[1]->width)
                T->width = T0->width;
            else
                T->width = T->ptr[1]->width;
            T->code = merge(9, T1->code, genLabel(T3->Snext), T2->code, genLabel(T2->Etrue), T->ptr[1]->code, genGoto(T->ptr[1]->Snext), genLabel(T->ptr[1]->Snext), T3->code, genGoto(T3->Snext));
            break;

        case BREAK:
            if (IN_LOOP == 0)
                semantic_error(T->pos, " ", "不在循环体内部，break语句出现位置错误");
            else
                T->code = genGoto(BREAK_NODE);
            break;

        case CONTINUE:
            if (IN_LOOP == 0)
                semantic_error(T->pos, " ", "不在循环体内部，continue语句出现位置错误");
            else
                T->code = genGoto(CONTINUE_NODE);
            break;

        case EXP_STMT:
            T->ptr[0]->offset = T->offset;
            semantic_Analysis(T->ptr[0]);
            T->code = T->ptr[0]->code;
            T->width = T->ptr[0]->width;
            break;
        case RETURN:
            return_flag--;
            if (T->ptr[0])
            {
                T->ptr[0]->offset = T->offset;
                Exp(T->ptr[0]);

                /*需要判断返回值类型是否匹配*/
                int i = symbolTable.index;
                do
                    i--;
                while (symbolTable.symbols[i].flag != 'F');
                if (T->ptr[0]->type != symbolTable.symbols[i].type)
                {
                    semantic_error(T->pos, "", "函数返回值类型与函数定义的返回值类型不匹配");
                    break;
                }

                T->width = T->ptr[0]->width;
                result.kind = ID;
                strcpy(result.id, symbolTable.symbols[T->ptr[0]->place].alias);
                result.offset = symbolTable.symbols[T->ptr[0]->place].offset;
                T->code = merge(2, T->ptr[0]->code, genIR(RETURN, opn1, opn2, result));
            }
            else
            {
                T->width = 0;
                result.kind = 0;
                T->code = genIR(RETURN, opn1, opn2, result);
            }
            break;
        case ID:
        case INT:
        case FLOAT:
        case CHAR:
        case ASSIGNOP:
        case AND:
        case OR:
        case RELOP:
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
        case NOT:
        case UMINUS:
        case EXP_DPLUS:
        case DPLUS_EXP:
        case DMINUS_EXP:
        case EXP_DMINUS:
        case PLUS_ASSIGNOP:
        case MINUS_ASSIGNOP:
        case DIV_ASSIGNOP:
        case STAR_ASSIGNOP:
        case FUNC_CALL:
        // case ARRAY_DEF:
        case ARRAY_READ:
            Exp(T); //处理基本表达式
            break;
        }
    }
}

void semantic_Analysis0(struct ASTNode *T)
{
    symbolTable.index = 0;
    fillSymbolTable("read", "", 0, INT, 'F', 4);
    symbolTable.symbols[0].paramnum = 0; //read的形参个数
    fillSymbolTable("write", "", 0, INT, 'F', 4);
    symbolTable.symbols[1].paramnum = 1;
    fillSymbolTable("x", "", 1, INT, 'P', 12);
    symbol_scope_TX.TX[0] = 0; //外部变量在符号表中的起始序号为0
    symbol_scope_TX.top = 1;
    T->offset = 0; //外部变量在数据区的偏移量
    semantic_Analysis(T);
    prnIR(T->code);
    if (return_flag > 0)
        semantic_error(-1, " ", "缺少return语句");
    // prn_symbol();
}
