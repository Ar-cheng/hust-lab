.386
.model flat, c
.data
XUNHUAN_NUM DB 0
IMUL1 DD 1280
.code

THIRD PROC pt:dword

        MOV XUNHUAN_NUM,0;遍历商品
        MOV ESI,pt;取好地址
        LOOP_MAIN:
            CMP XUNHUAN_NUM,30
            ;JE FIND_GOODS;相等跳出循环
            JE LL;作死改
            MOV ECX,0
            MOV CL,[ESI+0AH];折扣
            MOV BX,[ESI+0DH];销售价
            IMUL CX,BX;CX为折扣乘以销售价
            MOV EAX,0
            MOV EDX,0
            MOV AX,[ESI+0BH];进货价
            IMUL EAX,IMUL1;	
            IDIV ECX;此时EAX为结果部分
            MOV ECX,EAX;
            MOV EAX,0
            MOV EBX,0
            MOV EDX,0
            MOV AX,[ESI+11H];已售数量
            MOV BX,[ESI+0FH];进货数量
            ; IMUL EAX,IMUL2;可以改成循环
            SHL EAX,6
            IDIV EBX
            ADD EAX,ECX
            MOV [ESI+13H],AX
            ADD ESI,21;移动到下一个GA
            ;遍历加一
            LEA EDI,XUNHUAN_NUM
            INC BYTE PTR[EDI]
            ;这个地方可能有问题
            ; LEA DI,KONGZHI_NUM
            ; DEC WORD PTR[EDI]
            JMP LOOP_MAIN

		LL: RET
		THIRD ENDP

_SORT PROC pr:dword ,pts:dword
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    PUSH DI
    MOV EDI,pts
	MOV ESI,pr
    MOV AH,1;代表顺序靠后的商品，外层循环
_5LOOPA:
    MOV AL,0;代表顺序靠前的商品,内层循环
_5LOOPB:
    MOVSX EBX,AL;防止溢出操作
    IMUL EBX,21
    ADD EBX,ESI
    ADD EBX,19
    MOV CX,[EBX];存放顺序靠前的商品的推荐度
    MOVSX EBX,AH;防止溢出操作
    IMUL EBX,21
    ADD EBX,ESI
    ADD EBX,19
    MOV DX,[EBX];存放顺序靠后的商品的推荐度
    CMP CX,DX
    JA _5B;若小于则执行A，若大于则执行B
    JE _5NEXT
_5A:
    MOVSX EDX,AL
    ADD EDX,EDI
    MOV CX,[EDX]
    INC CX
    MOV [EDX],CX;对应位置的数字+1
    JMP _5NEXT
_5B:  
    MOVSX EDX,AH
    ADD EDX,EDI
    MOV CX,[EDX]
    INC CX
    MOV [EDX],CX;对应位置的数字+1
_5NEXT:
    INC AL
    CMP AH,AL;AH=AL时，本次内层循环结束，进入外层循环
    JNE _5LOOPB
    INC AH
    CMP AH,30;AH=N时，外层循环结束，函数主要算法部分结束
    JNE _5LOOPA
    POP DI
    POP DX
    POP CX
    POP BX
    POP AX
    RET
_SORT ENDP
end
