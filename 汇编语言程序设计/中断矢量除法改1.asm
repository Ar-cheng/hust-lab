;实验二：编写0 号中断的处理程序，使得在除法溢出发生时，在屏幕中间显示字符串“divide error！”，然后返回到DOS。源程序下：
assume cs:code 
code segment 
start: 
    mov ax,cs 
    mov ds,ax 
    mov si,offset do 
    mov di,200h  
  
    mov ax,0 
    mov es,ax;重置es 

    mov cx,offset doend - offset do ;安装中断例程 ,cx计数
    cld  ;LD与STD是用来操作方向标志位DF（Direction Flag）。CLD使DF复位，即DF=0，STD使DF置位，即DF=1.用于串操作指令中。
    ;MOV CX ,100
    ;LEA SI,FIRST
    ;LEA DI,SECOND
    ;REP MOVSB
    ;以上程序段的功能是从缓冲区FIRST传送100个字节到SECOND缓冲区.
    rep movsb  ;终止条件为ecx为0
    mov word ptr es:[0],200h 
    mov word ptr es:[2],0 ;设置中断向量表 ，中断向量表每项的四个字节存放着该项对应中断的中断处理程序的入口地址。四个字节也就是两个字，高字存放中断处理程序入口地址的段CS，低字存放偏移IP。 
    
    mov dx,0ffffh ;这行好像有点问题ax?
    mov bx,1 ;测试一下 
    div bx  
    
    mov ah,4ch 
    int 21h  

do:
    jmp short dostart 
    db 'divide error!' ;设置ds:si指向字符串 202= 200+2（2个字节是jmpshort do0start）
    dostart: 
    mov ax,0 
    mov ds,ax 
    mov si,202h ;
    mov ax,0b800h ;内存地址中，b8000h-bffffh共32kb空间，为80*25彩色字符模式的显示缓冲区。向这个地址空间写入数据，写入的内容会立即出现在显示器上。
    mov es,ax  
    mov di,160*12+60 ;和显示位置有关系，这个是第十二行靠前面好像
    mov cx,13 
    s:  mov al,ds:[si] 
    mov ah,15  ;这个是设置颜色
    mov es:[di],ax 
    inc si 
    inc di 
    inc di 
    loop s  
    
    mov ah,4ch 
    int 21h  
doend:nop ;no operation,延长一个时间周期
    
    code ends 
end start