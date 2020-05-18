汇编语言实验：编写0号中断处理程序
任务：编写0号中断处理程序，使得在除法溢出发生时，在屏幕中间显示字符串“divide error!”,然后返回操作系统。

下面写给出效果，再给出实现代码，最后给出设计思路（为什么这样做呢？因为本次实验没有任何难度，改编之前的示范程序就可以了，我也偷个懒，不写注释了）

这里写图片描述

实现代码如下：

assume      cs:code,ss:stack

stack       segment
    db  512 dup(?)
stack       ends

code        segment

main:           mov     ax,stack
                mov     ss,ax
                mov     sp,512
                mov     ax,0
                mov     ds,ax

                call    install_do0

                mov     ax,1000h
                mov     bh,0
                div     bh


                mov ah,4ch 
                int 21h  
;***********************************************************
install_do0:    push    ax
                push    cx
                push    ds
                push    es
                push    si
                push    di

                mov     ax,0
                mov     es,ax
                mov     di,200h

                mov     ax,cs
                mov     ds,ax
                mov     si,offset do0
                mov     cx,offset install_end - offset do0
                cld
                rep     movsb

                mov     ax,0
                mov     es,ax
                mov     word ptr es:[0*4],200h
                mov     word ptr es:[0*4+2],0

                jmp     near ptr install_end
;------------------------------------------------------------
do0:            jmp     short do0_start
                db 'divide error!'
    do0_start:  mov     ax,cs
                mov     ds,ax
                mov     si,202h

                mov     ax,0b800h
                mov     es,ax
                mov     di,10*160+20*2

                mov     cx,13
   
    s:          mov     al,[si]
                mov     es:[di],al
                mov     byte ptr es:[di+1],2
                inc     si
                add     di,2
                loop    s

                mov     ax,4c00h
                int     21h
;------------------------------------------------------------
install_end:    pop     di
                pop     si
                pop     es
                pop     ds
                pop     cx
                pop     ax
                ret
code        ends

end     main
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
中断的过程其实很容易理解，概括的说就是CPU自己完成一下操作 
1. 取得中断类型码N 
2. pushf， 标志寄存器压栈 
3. 设置标志为TF=0，IF=0 
4. push CS，将CS压栈 
5. push IP，将IP压栈 
6. 设置IP，CS为中断向量表存放的地址，也就是使(IP) = (N*4), 
(CS) = (N*4+2)

至于编写中断处理程序，和编写普通的子程序没有多大区别： 
1. 保存用到的寄存器 
2. 处理中断 
3. 恢复寄存器 
4. iret 返回 
其中，iret 指令相当于先retf ，然后popf。

这里我在编写0号中断处理程序do0时，直接返回操作系统，没有使用iret,因为我在debug中调试时，发现中断过程发生时，堆栈区存入的CS，IP指向的仍然时div bh 指令（这不是玩我吗），所以干脆在do0中直接返回操作系统算了。

最后，总结一下我此次实验的思路：

首先，编写安装子程序install_do0，功能是将中断处理程序do0安装到内存空间0:0200~0:02FF（中断向量表中的空余表项，没有任何信息，是一段安全空间）中。
在子程序install_do0中，修改中断向量表，使得0号中断发生时，可以执行程序do0（do0程序的代码就在子程序install_do0中，只不过作为数据传送到目的地址中，没有被执行罢了，这也充分说明了代码和数据没有本质的区别）
好了，总算是把王爽的教材中“内中断”的部分学习完了，任务也算基本完成了。可以继续学习新的内容了，我在学习汇编的路上越走越远……