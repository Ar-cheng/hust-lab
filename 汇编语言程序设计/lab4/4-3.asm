.386
STACK SEGMENT USE16 STACK
    DB 200 DUP(0)
STACK ENDS

DATA SEGMENT USE16
    STR1 BYTE 0AH,0DH,'time:$'
DATA ENDS

CODE SEGMENT USE16
ASSUME CS:CODE,DS:DATA,SS:STACK

START:
    MOV AX,DATA
    MOV DS,AX
    ;时间输出
    LEA DX,STR1;9号调用
    MOV AH,9
    INT 21H
    MOV AL,04H
    OUT 70H,AL
    IN  AL,71H
    CALL BYTE_HEX_PRINT
    MOV DL,58;2号调用
    MOV AH,2
    INT 21H
    MOV AL,02H
    OUT 70H,AL
    IN  AL,71H
    CALL BYTE_HEX_PRINT
    MOV DL,58;2号调用
    MOV AH,2
    INT 21H
    MOV AL,00H
    OUT 70H,AL
    IN  AL,71H
    CALL BYTE_HEX_PRINT
    
  
    MOV AH,4
    INT 21H
;入口参数：AL
;出口参数：无
BYTE_HEX_PRINT PROC  NEAR
    PUSH   AX
    PUSH   BX
    PUSH   CX
    PUSH   DX
    MOV    DH,2    ;循环的次数为四次
    X2:             
        PUSH   AX
        AND    AL,0F0H ;保留前四位
        MOV    CL,4      ;设置循环左移位数为4
        ROL    AL,CL     ;循环左移四位
        MOV    DL,AL     ;将AL中的值送到DL进行输出
        ADD    DL,30H
        CMP    DL,39H
        JLE    word2
        ADD    DL,7H
        word2:
        MOV    AH,2
        INT    21H
        POP    AX         ;-将求与运算之前的AX出栈
        ROL    AL,CL      ;左移四位，进行下一次运算
        DEC    DH         ;DH自减
        CMP    DH,0       ;如果DH不等于0，则循环这段操作
    JNZ X2
    POP   DX
    POP   CX
    POP   BX
    POP   AX
    RET
BYTE_HEX_PRINT ENDP

CODE ENDS
    END START
    