.386
.model flat, c

.data
count db 0
imul1 dd 1280d
imul2 dd 64d

.code
compute_all proc pt:dword
    ;�����ֳ�
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
		mov cl,[esi+0ah];�ۿ�
		mov bx,[esi+0dh];���ۼ�
		imul cx,bx;cxΪ�ۿ۳������ۼ�
		mov eax,0
		mov edx,0
		mov ax,[esi+0bh];������
		imul eax,imul1;	
		idiv ecx;��ʱeaxΪ�������
        mov ecx,eax
		mov eax,0
		mov ebx,0
		mov edx,0
		mov ax,[esi+11h];��������
		mov bx,[esi+0fh];��������
		imul eax,imul2
		idiv ebx
		add eax,ecx
		mov [esi+13h],ax
		 
		lea esi,count
		inc byte ptr [esi]
		cmp byte ptr [esi],30
		js loop5;Ϊ��ת
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
    ;��д�����ݵ�ַ
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
    ;����ð������
    mov eax,0
    mov ch,29;�������ѭ��
    compare:
    mov cl,0;�����ڲ�ѭ��
    mov esi,buffer_order
    inner:
    mov edi,dword ptr [esi]
    movsx eax,word ptr 19[edi]
    mov edi,dword ptr 4[esi]
    movsx ebx,word ptr 19[edi]
    cmp eax,ebx    
    jge changed;�����ǰ��,���ý���,��֮ 
    xchg edi,dword ptr [esi];����
    mov 4[esi],edi
    changed:;
    add esi,4
    inc cl
    cmp cl,ch
    jl inner;�ڲ�ѭ����δ����
    dec ch
    cmp ch,0
    jne compare;������һ���ѭ��
    pop   edx
    pop   ecx
    pop   ebx
    pop   eax
    ret
rec_sort endp
end

