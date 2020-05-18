.386
stack segment use16 stack 
db 199 dup(0)
stack ends

data segment use16
output_msg1 db 0ah,'welcome to----','$'
output_msg2 db 0ah,0ah,'please enter your name : ','$'
output_msg3 db 0ah,'please enter you password : ' ,'$'
output_msg4 db 0ah,'please enter the goods name : ' ,'$'
output_msg5 db 0ah,'fail find!',0ah,'$'
output_msg6 db 0ah,'success find! ',0ah ,'$'
output_msg7 db 0ah,'level: ','$'
error_msg_n db 0ah,'name wrong! please enter again!','$'
error_msg_p db 0ah,'password wrong!please enter again!','$'
register_success db 0ah,'register success!',0ah,'$'
sold_out_msg db 0ah,'sold out!',0ah,'$'
boss_name  db  'zzc666';姓名（必须是自己名字的拼音）
boss_name_length equ $-boss_name ;字符串长度
password    db ('a'-29h)*3;密码
            db ('d'-29h)*3
            db ('m'-29h)*3
            db ('i'-29h)*3
            db ('n'-29h)*3
password_length db 5 xor 'c';字符串长度
try_time db 0
shop_name  db  'my----shop----0.0','$';网店名称

        ;地址表（用于间接转移反跟踪）

g1      dw caidan
g2      dw info_print
g3      dw info_change
g4      dw find
g5      dw word_hex_print
g6      dw byte_hex_print
g7      dw compute_all
g8      dw rec_sort
g9      dw all_info_print

oldint1 dw  0,0           ;1号中断的原中断矢量（用于中断矢量表反跟踪）
oldint3 dw  0,0           ;3号中断的原中断矢量


in_name	    db  60  ;用户键入姓名
			db  ?
			db  60 dup('$')
in_pwd      db	60	;用户键入密码
			db  ?
			db  60 dup('$')
    
gongneng1 db 0ah,0ah,0dh,'1.search information of ga','$'
gongneng2 db 0ah,0dh,'2.change information of ga','$'
gongneng3 db 0ah,0dh,'3.calculate the score of ga','$'
gongneng4 db 0ah,0dh,'4.rank the ga with score','$'
gongneng5 db 0ah,0dh,'5.print the information of all ga','$'
gongneng6 db 0ah,0dh,'6.exit','$'
msg_goods_name  db 0ah,0dh,'please input goodsname:','$';商品名称录入
msg_discount    db 0ah,0dh,'discount:','$';折扣录入
msg_price_in    db 0ah,0dh,'price_in:','$';进货价录入
msg_price_out   db 0ah,0dh,'price_out:','$';销售价录入
msg_num_in      db 0ah,0dh,'goods_num:','$';进货总数录入
msg_num_out     db 0ah,0dh,'goods_sale:','$';已售出商品
msg_split       db '->','$';分隔符
msg_opt         db 0ah,0dh,'please choose option:','$'
msg_rec         db 0ah,0dh,'recommend:','$'
goods_name	db 11	;用户键入商品名称
			db ?
			db 11 dup(0)
temp_info   db 4    ;存储暂时修改信息
            db ?
            db 4 dup(0)
n equ 3
auth   db 0
order db 0
opt db 0
count db 0
imul1 dd 1280d
imul2 dd 64d
buff_order dw n dup(0)
ga1  db    'pen',7 dup(0),10;商品名称及折扣
	dw  35 xor 's',56,70,25,?;推荐度还未计算
ga2  db    'book',6 dup(0) ,9; 商品名称及折扣
	dw  12 xor 's',30,25,24,?;推荐度还未计算
ga3  db    'temp-value',8
    dw  15 xor 's',20,30,2,?
data ends

code segment use16 
assume cs:code,ds:data,ss:stack
start:
    mov ax,data
    mov ds,ax
   
    xor  ax,ax                  ;接管调试用中断，中断矢量表反跟踪
    mov  es,ax
    mov  ax,es:[1*4]            ;保存原1号和3号中断矢量
    mov  oldint1,ax
    mov  ax,es:[1*4+2]
    mov  oldint1+2,ax
    mov  ax,es:[3*4]
    mov  oldint3,ax
    mov  ax,es:[3*4+2]
    mov  oldint3+2,ax
    cli                           ;设置新的中断矢量
    mov  ax,offset exit
    mov  es:[1*4],ax
    mov  es:[1*4+2],cs
    mov  es:[3*4],ax
    mov  es:[3*4+2],cs
    sti

    lea dx,output_msg1;输出店名信息提示
	mov ah,09h
	int 21h
	mov dx,offset shop_name;店名
	mov ah,9
	int 21h

l1:
	lea dx,output_msg2;输入姓名提示
	mov ah,9
	int 21h
	lea dx,in_name;读入姓名
	mov ah,0ah
	int 21h
	cmp 2[in_name],0dh;判断是否为回车
	je index1
	cmp 1[in_name],1;判断是否只有一个字符
	jne l1_yes;不止一个字符
	cmp 2[in_name],'q';只有一个字符为q
    je exit;退出程序		
	l1_yes:;输入密码

		lea dx,output_msg3;输入密码提示
		mov ah,9
		int 21h

        lea dx,in_pwd;读入密码
		mov ah,0ah
		int 21h

        cli                       ;计时反跟踪开始 
        mov  ah,2ch 
        int  21h
        push dx                   ;保存获取的秒和百分秒
		
        mov ax,0
        mov cx,0

        mov  ah,2ch                 ;获取第二次秒与百分秒
        int  21h
        sti      
        cmp  dx,[esp]               ;计时是否相同
        pop  dx       
        jz l2                  
        jmp exit ;如果计时不相同，通过本次计时反跟踪   

l2:
	cmp_name:
        cmp 1[in_name],boss_name_length;先判断姓名长度是否相等
		jne error_name

		mov cx,0
		lea si,in_name+2
		lea di,boss_name
		loopa:
			mov al,[si]
			mov bl,[di]
			cmp al,bl
			jne error_name
			inc cx
			inc si
			inc di
			cmp cx,boss_name_length
			jne loopa		
	cmp_pwd:
        lea si,password_length;先解密
        mov ah,[si]
        xor ah,'c'
        mov byte ptr [si],ah
        
        mov ch,password_length
		cmp 1[in_pwd],ch;先判断密码长度是否相等
		jne error_pwd

		mov cl,0
		lea si,in_pwd+2
		lea di,password

        mov cl,0
    	loopb:
			mov ax,0
            mov bx,0
            mov dl,3
            mov al,byte ptr [si]
			mov bl,byte ptr [di]

            sub ax,29h
            mul dl

			cmp ax,bx
			jne error_pwd

			inc cl
			inc si
			inc di
			cmp cl,password_length
			jne loopb
	
    	mov auth,1
		lea dx,register_success
		mov ah,09h
		int 21h

l3:
    lea si,try_time
    mov byte ptr [si],0
    func1:;菜单信息
        mov ax,g1
        call ax
        mov dx,offset msg_opt;9号调用
        mov ah,9
        int 21h
        mov ah,01h
        int 21h
        cmp auth,1
        jne guest_option
        boss_optinon:
        cmp al,31h
        je func2
        cmp al,32h
        je func3
        cmp al,33h
        je func4
        cmp al,34h
        je func5
        cmp al,35h
        je func6
        cmp al,36h
        je l1
        jmp func1
        guest_option:
        cmp al,31h
        je func2
        cmp al,36h
        je l1
        jmp func1
    func2:;查询商品信息
        mov ax,g4
        call ax
        jmp func1
    func3:;修改商品信息
        mov ax,g3
        call ax
        jmp func1
    func4:;计算推荐度
        mov ax,g7
        call ax
        jmp func1
    func5:;推荐度排序
        mov ax,g8
        call ax
        jmp func1
    func6:;输出全部商品信息   
        mov ax,g9
        call ax
        jmp func1

exit:
    cli  ;还原中断矢量
    mov  ax,oldint1
    mov  es:[1*4],ax
    mov  ax,oldint1+2
    mov  es:[1*4+2],ax
    mov  ax,oldint3
    mov  es:[3*4],ax
    mov  ax,oldint3+2
    mov  es:[3*4+2],ax 
    sti

    mov ah,4ch
    int 21h
index1:
	mov dl,0ah;换行
	mov ah,02h
	int 21h
	mov auth,0
	jmp l3
error_name:
    
    lea dx,error_msg_n
	mov ah,9
	int 21h
    lea si,try_time
    inc byte ptr [si]
    cmp byte ptr [si],3
    je l3
	jmp l1
error_pwd:
	lea si,password_length;加密
    mov ah,[si]
    xor ah,'c'
    mov byte ptr [si],ah
	
    lea dx,error_msg_p
	mov ah,9
	int 21h
    inc byte ptr [si]
    cmp byte ptr [si],3
    je l3
	jmp l1

info_change proc
    ;保护现场
    push si
    push di
    push ax
    push bx
    push cx
    push dx
    begin0: ; 清空goods-name数据
        mov ax,0
        lea si,goods_name+2
        init0:
            mov byte ptr [si],0
            inc si
            inc ax
            cmp ax,10
            jne init0
        mov dx,offset msg_goods_name;输入商品信息
        mov ah,9
        int 21h
        mov dx,offset goods_name;输入商品名称
        mov ah,0ah
        int 21h

	goods_name_judge:
		cmp 2[goods_name],0dh;键入回车
		je space_back
        movsx ax,1[goods_name];
        cmp ax,10
        je find_goods
		lea si,goods_name+2
		add si,ax
		mov word ptr [si],0
	find_goods:
		mov ch,0;遍历商品
		mov cl,0;遍历名称
		loop1:
			lea si,ga1
			movsx dx,ch
			imul dx,21
			add si,dx
			lea di,goods_name+2
			loop2:
				mov ah,[si]
				mov al,[di]
				cmp ah,	al
				jne next_goods
				inc si
				inc di
				inc cl
				cmp cl,10
				je success
				jmp loop2
			next_goods:
				inc ch
				cmp ch,n
				je fail
				jmp loop1
    success:
        lea si,ga1
        movsx dx,ch
        imul dx,21
        add si,dx
        discount_input:
            mov dx,offset msg_discount;9号调用
            mov ah,9
            int 21h
           
            push si
            add si,0ah
            call byte_hex_print
            pop si

            mov dx,offset msg_split;9号调用
            mov ah,9
            int 21h
            lea dx,temp_info;10号调用
            mov ah,0ah
            int 21h
            ;直接回车时，对这项信息不做修改
            cmp 2[temp_info],0dh
            je price_in_input
            ;输入了非法数值，下一行重新显示和输入
            lea di,temp_info+2
            mov bx,0;记录字符串长度
            input_judge1:
                cmp byte ptr [di],30h ;第一位大于等于0
                jl discount_input
                cmp byte ptr [di],39h;第一位小于等于9
                jg discount_input
                cmp byte ptr 1[di],0dh;第二位为回车
                je on_1
                cmp byte ptr [di],31h;第一位为1
                jne discount_input
                cmp byte ptr 1[di],30h;第二位为0
                jne discount_input
                cmp byte ptr 2[di],0dh;第三位为回车
                jne discount_input
                on_1:
                lea di,temp_info+2
                mov bx, 0
            change1:
                imul bx, 10
                add bl, byte ptr [di]
                sub bl, 30h
                inc di
                cmp byte ptr [di],0dh
                jne change1
                mov [si+0ah],bl
        price_in_input:
            lea dx,msg_price_in;9号调用
            mov ah,9
            int 21h

            push si
            add si,0bh
            call word_hex_print
            pop si

            mov dx,offset msg_split;9号调用
            mov ah,9
            int 21h
            mov dx,offset temp_info;10号调用
            mov ah,0ah
            int 21h
            ;直接回车时，对这项信息不做修改
            cmp 2[temp_info],0dh
            je price_out_input
            ;输入了非法数值，下一行重新显示和输入
            mov ch,0
            lea di,temp_info+2
            input_judge2:
                cmp byte ptr [di],30h
                jle price_in_input
                cmp byte ptr [di],39h
                jg price_in_input
                inc di
                cmp byte ptr [di],0dh
                jne input_judge2
                
                lea di,temp_info+2
                mov bx,0
                mov cx,0
                ;movsx bx, byte ptr [di]
            change2:
                imul bx, 10
                movsx cx,byte ptr [di]
                add bx, cx
                sub bx, 30h
                inc di
                cmp byte ptr [di],0dh
                jne change2
                xor bx,'s'
                mov [si+0bh],bx
        price_out_input:
            mov dx,offset msg_price_out;9号调用
            mov ah,9
            int 21h

            push si
            add si,0dh
            call word_hex_print
            pop si

            mov dx,offset msg_split;9号调用
            mov ah,9
            int 21h
            mov dx,offset temp_info;10号调用
            mov ah,0ah
            int 21h
            ;直接回车时，对这项信息不做修改
            cmp 2[temp_info],0dh
            je num_input
            ;输入了非法数值，下一行重新显示和输入
            mov ch,0
            lea di,temp_info+2
            input_judge3:
                cmp byte ptr [di],30h
                jle price_out_input
                cmp byte ptr [di],39h
                jg price_out_input
                inc di
                cmp byte ptr [di],0dh
                jne input_judge3
                
                lea di,temp_info+2
                mov bx,0
                ;movsx bx, byte ptr [di]
            change3:
                imul bx, 10
                movsx cx,byte ptr [di]
                add bx, cx
                sub bx, 30h
                inc di
                cmp byte ptr [di],0dh
                jne change3
                mov [si+0dh],bx
        num_input:
            mov dx,offset msg_num_in;9号调用
            mov ah,9
            int 21h

            push si
            add si,0fh
            call word_hex_print
            pop si

            mov dx,offset msg_split;9号调用
            mov ah,9
            int 21h
            mov dx,offset temp_info;10号调用
            mov ah,0ah
            int 21h
            ;直接回车时，对这项信息不做修改
            cmp 2[temp_info],0dh
            je exit_0
            ;输入了非法数值，下一行重新显示和输入
            mov ch,0
            lea di,temp_info+2
            input_judge4:
                cmp byte ptr [di],30h
                jle num_input
                cmp byte ptr [di],39h
                jg num_input
                inc di
                cmp byte ptr [di],0dh
                jne input_judge4
                
                lea di,temp_info+2
                mov bx,0
                ;movsx bx, byte ptr [di]
            change4:
                imul bx,10
                movsx cx,byte ptr [di]
                add bx, cx
                sub bx, 30h
                inc di
                cmp byte ptr [di],0dh
                jne change4
                mov [si+0fh],bx
                exit_0:
                lea di,order
                mov byte ptr [di],2
                jmp exit_1
    space_back:;键入回车
        lea di,order
        mov byte ptr [di],0
        jmp exit_1
    fail:;未找到商品
        lea di,order
        mov byte ptr [di],1
        jmp begin0
    ;出口
    exit_1:
        pop dx
        pop cx
        pop bx
        pop ax
        pop di
        pop si
        ret
info_change endp
;入口参数：无
;出口参数：无
caidan proc
    push dx
    push ax
    cmp auth,1
    jne guest
    boss:
        mov dx,offset gongneng1;9号调用
        mov ah,09h
        int 21h

        mov dx,offset gongneng2;9号调用
        mov ah,09h
        int 21h

        mov dx,offset gongneng3;9号调用
        mov ah,09h
        int 21h

        mov dx,offset gongneng4;9号调用
        mov ah,09h
        int 21h

        mov dx,offset gongneng5;9号调用
        mov ah,09h
        int 21h

        mov dx,offset gongneng6;9号调用
        mov ah,09h
        int 21h

        jmp over1

    guest:
        mov dx,offset gongneng1;9号调用
        mov ah,09h
        int 21h

        mov dx,offset gongneng6;9号调用
        mov ah,09h
        int 21h

    over1:
        pop ax
        pop dx;保护现场
        ret
caidan endp
;入口参数：si记录目标打印商品偏移地址
;出口参数：无
info_print proc
    push ax
    push bx
    push cx
    push dx
    mov dl,0ah;2号调用
    mov ah,2
    int 21h
    ; mov dx,offset goods_name+2;9号调用
    ; mov ah,9
    ; int 21h
    push si
    mov cl,0
    loop7:
        mov dl,byte ptr [si];2号调用
        mov ah,2
        int 21h
        inc si
        inc cl
        cmp cl,10
        je follow
        cmp byte ptr [si],30h
        jne loop7

    follow:
    pop si
    add si,0ah
    mov dx,offset msg_discount;9号调用
    mov ah,9
    int 21h
    call byte_hex_print

    add si,1
    mov dx,offset msg_price_in;9号调用
    mov ah,9
    int 21h
    xor word ptr [si],'s'
    call word_hex_print
    xor word ptr [si],'s'

    add si,2
    mov dx,offset msg_price_out;9号调用
    mov ah,9
    int 21h
    call word_hex_print

    add si,2
    mov dx,offset msg_num_in;9号调用
    mov ah,9
    int 21h
    call word_hex_print
   
    add si,2
    mov dx,offset msg_num_out;9号调用
    mov ah,9
    int 21h
    call word_hex_print

    add si,2
    mov dx,offset msg_rec;9号调用
    mov ah,9
    int 21h
    call word_hex_print

    pop dx
    pop cx
    pop bx
    pop ax
    ret
info_print endp
;入口参数：无
;出口参数：无
find proc near
    begin1: ; 清空goods-name数据
        mov ax,0
        lea si,goods_name+2
        init:
            mov byte ptr [si],0
            inc si
            inc ax
            cmp ax,10
            jne init
        mov dx,offset msg_goods_name;输入商品信息
        mov ah,9
        int 21h
        mov dx,offset goods_name;输入商品名称
        mov ah,0ah
        int 21h
        cmp 2[goods_name],0dh;键入回车
		je out1
        movsx ax,1[goods_name];
        cmp ax,10
        je find_goods_index
		lea si,goods_name+2
		add si,ax
		mov word ptr [si],0
        find_goods_index:
            mov ch,0;遍历商品
            loop1_index:
                mov cl,0;遍历名称
                lea si,ga1
                movsx dx,ch
                imul dx,21
                add si,dx
                lea di,goods_name+2
                loop2_index:
                    mov ah,[si]
                    mov al,[di]
                    cmp ah,	al
                    jne next_goods_index
                    inc si
                    inc di
                    inc cl
                    cmp cl,10
                    je success_index
                    jmp loop2_index
                next_goods_index:
                    inc ch
                    cmp ch,n
                    je begin1
                    jmp loop1_index
        success_index:;找到商品,定位目标
            lea si,ga1
			movsx dx,ch
			imul dx,21
			add si,dx
            call info_print
        out1:
            ret
find endp
;入口参数：si,指向word的地址
;出口参数：无
word_hex_print proc  near
    push   ax
    push   bx
    push   cx
    push   dx

    mov    ax,word ptr [si]
    mov    dh,4     ;循环的次数为四次
    x1:             
      push   ax
        and    ax,0f000h ;保留前四位
        mov    cl,4      ;设置循环左移位数为4
        rol    ax,cl     ;循环左移四位 
        mov    dl,al     ;将al中的值送到dl进行输出
        add    dl,30h
        cmp    dl,39h
        jle    word1
        add    dl,7h
        word1:
        mov    ah,2
        int    21h
        pop    ax         ;-将求与运算之前的ax出栈
        rol    ax,cl      ;左移四位，进行下一次运算
        dec    dh         ;dh自减
        cmp    dh,0       ;如果dh不等于0，则循环这段操作
    jnz x1
    pop   dx
    pop   cx
    pop   bx
    pop   ax
    ret
word_hex_print endp
;入口参数：si,指向byte的地址
;出口参数：无
byte_hex_print proc  near
    push   ax
    push   bx
    push   cx
    push   dx
    movsx    ax,byte ptr [si]
    mov    dh,2    ;循环的次数为四次
    x2:             
         push   ax
        and    al,0f0h ;保留前四位
        mov    cl,4      ;设置循环左移位数为4
        rol    al,cl     ;循环左移四位
        mov    dl,al     ;将al中的值送到dl进行输出
        add    dl,30h
        cmp    dl,39h
        jle    word2
        add    dl,7h
        word2:
        mov    ah,2
        int    21h
        pop    ax         ;-将求与运算之前的ax出栈
        rol    al,cl      ;左移四位，进行下一次运算
        dec    dh         ;dh自减
        cmp    dh,0       ;如果dh不等于0，则循环这段操作
    jnz x2
    pop   dx
    pop   cx
    pop   bx
    pop   ax
    ret
byte_hex_print endp
;入口参数：无
;出口参数：无
compute_all proc
    ;保护现场
    push di
    push ax
    push bx
    push cx
    push dx
	lea di,count
	mov byte ptr[di],0
	loop5:
		lea si,ga1
		lea di,count
		mov dl,byte ptr [di]
		mov dh,0h
		imul dx,21
		add si,dx

		mov ecx,0
		mov cl,[si+0ah];折扣
		mov bx,[si+0dh];销售价
		imul cx,bx;cx为折扣乘以销售价
		mov eax,0
		mov edx,0
		mov ax,[si+0bh];进货价
        xor ax,'s'
		imul eax,imul1;	
		idiv ecx;此时eax为结果部分
        mov ecx,eax
		mov eax,0
		mov ebx,0
		mov edx,0
		mov ax,[si+11h];已售数量
		mov bx,[si+0fh];进货数量
		imul eax,imul2
		idiv ebx
		add eax,ecx
		mov [si+13h],ax
		 
		lea si,count
		inc byte ptr [si]
		cmp byte ptr [si],n
		js loop5;为负转
		pop dx
        pop cx
        pop bx
        pop ax
        pop di
        ret
compute_all endp
;入口参数：无
;出口参数：无
rec_sort proc near
    push   ax
    push   bx
    push   cx
    push   dx
    ;先写入数据地址
    mov cx,0
    lea si,ga1
    lea di,buff_order
    write:
        mov word ptr [di],si
        add si,21
        add di,2
        inc cx
        cmp cx,n
        jne write
    ;进行冒泡排序
    mov ax,0
    mov ch,n-1;控制外层循环
    compare:
    mov cl,0;控制内层循环
    lea si,buff_order
    inner:
    mov di,word ptr [si]
    mov ax,19[di]
    mov di,word ptr 2[si]
    mov bx,19[di]
    cmp ax,bx    
    jge changed;大的在前面,则不用交换,跳之 
    xchg di,word ptr [si];交换
    mov 2[si],di
    changed:;
    add si,2
    inc cl
    cmp cl,ch
    jl inner;内层循环尚未结束
    dec ch
    cmp ch,0
    jne compare;进入下一层大循环

    pop   dx
    pop   cx
    pop   bx
    pop   ax
    ret
rec_sort endp
;入口参数：无
;出口参数：无
all_info_print proc near
    mov cx,0        
        lea di,buff_order  
        mov si,word ptr [di]   
        p:
            call info_print
            inc cx
            cmp cx , n
            je q
            add di,2
            mov si,word ptr [di]
            jmp p
        q:
            ret
all_info_print endp
code ends
    end start