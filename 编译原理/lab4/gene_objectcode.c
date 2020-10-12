//目标代码生成

#include "def.h"

void objectCode(struct codenode *head)
{
    char opnstr1[32], opnstr2[32], resultstr[32];
    
    struct codenode *h = head, *p;
    
    int i, temp;

    FILE *fp;
    fp = fopen("object.s", "w");
    
    fprintf(fp, ".data\n");
    fprintf(fp, "_Prompt: .asciiz \"Enter an integer:  \"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    
    
    //add main0 jmp to main
    fprintf(fp, "main0:\n");
    fprintf(fp, " jal main\n");
    fprintf(fp, " li $v0,10\n");
    fprintf(fp, " syscall\n");


    //read
    fprintf(fp, "read:\n");
    fprintf(fp, "  li $v0,4\n");
    fprintf(fp, "  la $a0,_Prompt\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0,5\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  jr $ra\n");


    //write
    fprintf(fp, "write:\n");
    fprintf(fp, "  li $v0,1\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0,4\n");
    fprintf(fp, "  la $a0,_ret\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  move $v0,$0\n");
    fprintf(fp, "  jr $ra\n");
    do
    {
        switch (h->op)
        {
        case ASSIGNOP:

            if (h->result.kind == ID && h->opn2.kind != ARRAY_READ)
            {
                if (h->opn1.kind == INT)
                    fprintf(fp, "  li $t3, %d\n", h->opn1.const_int);
                else
                {
                    fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                    fprintf(fp, "  move $t3, $t1\n");
                }
                fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
            }

            else if (h->result.kind == ARRAY_READ)
            {
                // fprintf(fp, "debug!!!!!!!!!!\n");
                fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
                fprintf(fp, "  lw $t3, %d($sp)\n", h->result.offset);
                fprintf(fp, "  add $t4, $t2, $t3 \n");

                fprintf(fp, "  move $t5, $sp \n");

                fprintf(fp, "  add $sp, $t4, $sp \n");

                fprintf(fp, "  sw $t1, ($sp)\n");

                fprintf(fp, "  move $sp, $t5 \n");
                // fprintf(fp, "debug!!!!!!!!!!\n");

                // printf("  %s[%s] := %s\n", resultstr, opnstr2, opnstr1);
            }


            else if (h->result.kind == ID && h->opn2.kind == ARRAY_READ)
            {
                // fprintf(fp, "debug!!!!!!!!!!--------------------\n");
                fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
                fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);

                fprintf(fp, "  add $t4, $t1, $t2 \n");

                fprintf(fp, "  move $t5, $sp \n");

                fprintf(fp, "  add $sp, $sp, $t4 \n");
                fprintf(fp, "  lw $t6, ($sp)\n");

                fprintf(fp, "  move $sp, $t5 \n");

                fprintf(fp, "  sw $t1, %d($sp)\n", h->result.offset);

                // fprintf(fp, "debug!!!!!!!!!!\n");

                // printf("  %s := %s[%s]\n", resultstr, opnstr1, h->opn2.id);
            }

            // if (h->opn1.kind == INT)
            //     fprintf(fp, "  li $t3, %d\n", h->opn1.const_int);
            // else
            // {
            //     fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
            //     fprintf(fp, "  move $t3, $t1\n");
            // }
            // fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
            break;

        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            // fprintf(fp, "relop!!!!!!!!!!--------------------\n");

            fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);

            if (h->opn2.kind == INT)
                fprintf(fp, "  li $t2, %d\n", h->opn2.const_int);
            else
                fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
            if (h->op == PLUS)
                fprintf(fp, "  add $t3,$t1,$t2\n");
            else if (h->op == MINUS)
                fprintf(fp, "  sub $t3,$t1,$t2\n");
            // fprintf(fp, "relop!!!!!!!!!!--------------------\n");

            else if (h->op == STAR)
                fprintf(fp, "  mul $t3,$t1,$t2\n");
            else
            {
                fprintf(fp, "  div $t1, $t2\n");
                fprintf(fp, "  mflo $t3\n");
            }
            fprintf(fp, "  sw $t3, %d($sp)\n", h->result.offset);
            break;

            // fprintf(fp, "relop!!!!!!!!!!--------------------\n");

        case FUNCTION:
            // fprintf(fp, "function!!!!!!!!!!--------------------\n");

            fprintf(fp, "\n%s:\n", h->result.id);
            if (!strcmp(h->result.id, "main"))
                fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->result.offset].offset);
            break;
        
        case PARAM:
            break;
        
        case LABEL:
            fprintf(fp, "%s:\n", h->result.id);
            break;
        
        case GOTO:
            fprintf(fp, "  j %s\n", h->result.id);
            break;
        
        case JLE:
        case JLT:
        case JGE:
        case JGT:
        case EQ:
        case NEQ:
            fprintf(fp, "  lw $t1, %d($sp)\n", h->opn1.offset);
            fprintf(fp, "  lw $t2, %d($sp)\n", h->opn2.offset);
            if (h->op == JLE)
                fprintf(fp, "  ble $t1,$t2,%s\n", h->result.id);
            else if (h->op == JLT)
                fprintf(fp, "  blt $t1,$t2,%s\n", h->result.id);
            else if (h->op == JGE)
                fprintf(fp, "  bge $t1,$t2,%s\n", h->result.id);
            else if (h->op == JGT)
                fprintf(fp, "  bgt $t1,$t2,%s\n", h->result.id);
            else if (h->op == EQ)
                fprintf(fp, "  beq $t1,$t2,%s\n", h->result.id);
            else
                fprintf(fp, "  bne $t1,$t2,%s\n", h->result.id);
            break;
            // fprintf(fp, "EQ!!!!!!!!!!--------------------\n");

        case ARG:
            break;
        
        case CALL:
            // fprintf(fp, "CALL!!!!!!!!!!--------------------\n");

            //write
            if (!strcmp(h->opn1.id, "write"))
            {
                fprintf(fp, "  lw $a0, %d($sp)\n", h->prior->result.offset);
                fprintf(fp, "  addi $sp, $sp, -4\n");
                fprintf(fp, "  sw $ra,0($sp)\n");
                fprintf(fp, "  jal write\n");
                fprintf(fp, "  lw $ra,0($sp)\n");
                fprintf(fp, "  addi $sp, $sp, 4\n");
                break;
            }

            //read
            if (!strcmp(h->opn1.id, "read"))
            {
                fprintf(fp, "  addi $sp, $sp, -4\n");
                fprintf(fp, "  sw $ra,0($sp)\n");
                fprintf(fp, "  jal read\n");
                fprintf(fp, "  lw $ra,0($sp)\n");
                fprintf(fp, "  addi $sp, $sp, 4\n");
                fprintf(fp, "  sw $v0, %d($sp)\n", h->result.offset);
                break;
            }

            
            //参数处理
            for (p = h, i = 0; i < symbolTable.symbols[h->opn1.offset].paramnum; i++)
                p = p->prior;

            fprintf(fp, "  move $t0,$sp\n");
            fprintf(fp, "  addi $sp, $sp, -%d\n", symbolTable.symbols[h->opn1.offset].offset);
            fprintf(fp, "  sw $ra,0($sp)\n");
            i = h->opn1.offset + 1;

            while (symbolTable.symbols[i].flag == 'P')
            {
                fprintf(fp, "  lw $t1, %d($t0)\n", p->result.offset);
                fprintf(fp, "  move $t3,$t1\n");
                fprintf(fp, "  sw $t3,%d($sp)\n", symbolTable.symbols[i].offset);
                p = p->next;
                i++;
            }

            // fprintf(fp, "DEBUG1!!!!!!!!!!--------------------\n");

            fprintf(fp, "  jal %s\n", h->opn1.id);
            fprintf(fp, "  lw $ra,0($sp)\n");
            fprintf(fp, "  addi $sp,$sp,%d\n", symbolTable.symbols[h->opn1.offset].offset);
            fprintf(fp, "  sw $v0,%d($sp)\n", h->result.offset);
            break;
            // fprintf(fp, "EQ!!!!!!!!!!--------------------\n");

        case RETURN:
            // fprintf(fp, "return!!!!!!!!!!--------------------\n");
            fprintf(fp, "  lw $v0,%d($sp)\n", h->result.offset);
            fprintf(fp, "  jr $ra\n");
            break;


        // case PLUS_ASSIGNOP:

        // case MINUS_ASSIGNOP:

        // case STAR_ASSIGNOP:

        // case DIV_ASSIGNOP:

        }
        h = h->next;
    } while (h != head);
    fclose(fp);
}
