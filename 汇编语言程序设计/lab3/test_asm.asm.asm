.386
.model flat, c

.data
count db 0
imul1 dd 1280d
imul2 dd 64d

.code
compute_all proc pt:dword
    ;保护现场
    push esi
    push edi
    push eax
    push ebx
    push ecx
    push edx
	lea edi,count
	mov byte ptr[edi],0
	loop5:
		mov esi,pt
		lea edi,count
		mov edx,0h
		mov dl,byte ptr [edi]
		imul dx,21
		add esi,edx

		mov ecx,0
		mov cl,[esi+0ah];折扣
		mov bx,[esi+0dh];销售价
		imul cx,bx;cx为折扣乘以销售价
		mov eax,0
		mov edx,0
		mov ax,[esi+0bh];进货价
		imul eax,imul1;	
		idiv ecx;此时eax为结果部分
        mov ecx,eax
		mov eax,0
		mov ebx,0
		mov edx,0
		mov ax,[esi+11h];已售数量
		mov bx,[esi+0fh];进货数量
		imul eax,imul2
		idiv ebx
		add eax,ecx
		mov [esi+13h],ax
		 
		lea esi,count
		inc byte ptr [esi]
		cmp byte ptr [esi],30
		js loop5;为负转
		pop edx
        pop ecx
        pop ebx
        pop eax
        pop edi
        pop esi
        ret
compute_all endp

rec_sort proc pt:dword,buffer_order:dword
    push   eax
    push   ebx
    push   ecx
    push   edx
    ;先写入数据地址
    mov ecx,0
    mov esi,pt
    mov edi,buffer_order
    write:
        mov dword ptr [edi],esi
        add esi,21
        add edi,4
        inc ecx
        cmp ecx,30
        jne write
    ;进行冒泡排序
    mov eax,0
    mov ch,29;控制外层循环
    compare:
    mov cl,0;控制内层循环
    mov esi,buffer_order
    inner:
    mov edi,dword ptr [esi]
    movsx eax,word ptr 19[edi]
    mov edi,dword ptr 4[esi]
    movsx ebx,word ptr 19[edi]
    cmp eax,ebx    
    jge changed;大的在前面,则不用交换,跳之 
    xchg edi,dword ptr [esi];交换
    mov 4[esi],edi
    changed:;
    add esi,4
    inc cl
    cmp cl,ch
    jl inner;内层循环尚未结束
    dec ch
    cmp ch,0
    jne compare;进入下一层大循环
    pop   edx
    pop   ecx
    pop   ebx
    pop   eax
    ret
rec_sort endp
end

