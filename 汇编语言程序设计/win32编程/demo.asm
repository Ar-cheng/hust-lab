.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD
Compute_all proto 
radix proto :word,:dword

include      menuID.INC

include      windows.inc
include      user32.inc
include      kernel32.inc
include      gdi32.inc
include      shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib

ga	struct
	    goods_name  db  10 dup(0)
		discount 		db 0
	    price_in  		dw 0
		price_out  		dw 0
		num_in  		dw 0
		num_out   		dw 0
		recommend  		dw 0
ga  ends

ga1	struct
	   	goods_name  db  10 dup(0)
		discount 		db 3 dup(0)
	    price_in  		db 3 dup(0)
		price_out  		db 3 dup(0)
		num_in  		db 3 dup(0)
		num_out   		db 3 dup(0)
		recommend  		db 3 dup(0)
ga1  ends

.data
n equ 5
count db 0
imul1 dd 1280d
imul2 dd 64d

AppName		db  		'MyWindows'
ClassName    db       'TryWinClass',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
HelpName      db      'Help_msg',0
HelpMsg     db       'I am jizhuo_zzc',0
hInstance    dd       0
CommandLine  dd       0

msg_goods_name     db       'goods_name',0
msg_discount  db       'discount',0
msg_price_in     db       'price_in',0
msg_price_out  db       'price_out',0
msg_num_in  db       'num_in',0
msg_num_out    db       'num_out',0
msg_recommend  db       'recommend',0

buf ga <'pen',10,035,056,070,025>
	ga <'book',009,012,030,025,024>
	ga <'temp-value',008,015,020,030,002>
	ga <'temp-value',008,015,020,030,002>
	ga <'temp-value',008,015,020,030,002>

buf1  ga1 <'pen','010','035','056','070','025','000'>
	ga1 <'book','009','012','030','025','024','000'>
	ga1 <'temp-value','008','015','020','030','002','000'>
	ga1 <'temp-value','008','015','020','030','002','000'>
	ga1 <'temp-value','008','015','020','030','002','000'>

.code
Start:	 invoke GetModuleHandle,NULL;获取当前程序的句柄
	     mov    hInstance,eax
	     invoke GetCommandLine;获取当前命令行缓冲区的指针
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	    mov    wc.cbSize,SIZEOF WNDCLASSEX 
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage,addr msg,NULL,0,0
             cmp    EAX,0
             je     ExitLoop
             INVOKE TranslateMessage,addr msg
             INVOKE DispatchMessage,addr msg
	     jmp    MsgLoop 
ExitLoop:    mov    eax,msg.wParam
	     ret
WinMain      endp

WndProc      proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	     LOCAL  hdc:HDC
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL
     .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
             ;;your code
	    .ENDIF
     .ELSEIF uMsg == WM_COMMAND
	    .IF     wParam == IDM_FILE_EXIT
		    invoke SendMessage,hWnd,WM_CLOSE,0,0
		.ELSEIF wParam == IDM_ACTION_RECOMMENDATION
			invoke Compute_all
			lea esi,buf+13h
			lea edi,buf1+19h
			invoke radix,word ptr [esi],edi
			add esi,15h
			add edi,1ch
			invoke radix,word ptr [esi],edi
			add esi,15h
			add edi,1ch
			invoke radix,word ptr [esi],edi
			add esi,15h
			add edi,1ch
			invoke radix,word ptr [esi],edi
			add esi,15h
			add edi,1ch
			invoke radix,word ptr [esi],edi
	    .ELSEIF wParam == IDM_ACTION_LIST
		    invoke Display,hWnd
	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr HelpMsg,addr HelpName,0
	    .ENDIF
     ;.ELSEIF uMsg == WM_PAINT
	     ;;redraw window again
     .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
     .ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp

Display     proc   hWnd:DWORD
            XX     equ  10
            YY     equ  10
	     XX_GAP equ  100
	     YY_GAP equ  30
            LOCAL  hdc:HDC
            invoke GetDC,hWnd
            mov    hdc,eax
            invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_goods_name,10
            invoke TextOut,hdc,XX+1*XX_GAP,YY+0*YY_GAP,offset msg_discount,8
            invoke TextOut,hdc,XX+2*XX_GAP,YY+0*YY_GAP,offset msg_price_in,8
            invoke TextOut,hdc,XX+3*XX_GAP,YY+0*YY_GAP,offset msg_price_out,9
            invoke TextOut,hdc,XX+4*XX_GAP,YY+0*YY_GAP,offset msg_num_in,6
            invoke TextOut,hdc,XX+5*XX_GAP,YY+0*YY_GAP,offset msg_num_out,7
   			invoke TextOut,hdc,XX+6*XX_GAP,YY+0*YY_GAP,offset msg_recommend,9			 
			 			 
             ;;
            invoke TextOut,hdc,XX+0*XX_GAP,YY+1*YY_GAP,offset buf1[0*28].goods_name,3
            invoke TextOut,hdc,XX+1*XX_GAP,YY+1*YY_GAP,offset buf1[0*28].discount,3
            invoke TextOut,hdc,XX+2*XX_GAP,YY+1*YY_GAP,offset buf1[0*28].price_in,3
            invoke TextOut,hdc,XX+3*XX_GAP,YY+1*YY_GAP,offset buf1[0*28].price_out,3
            invoke TextOut,hdc,XX+4*XX_GAP,YY+1*YY_GAP,offset buf1[0*28].num_in,3
            invoke TextOut,hdc,XX+5*XX_GAP,YY+1*YY_GAP,offset buf1[0*28].num_out,3
			invoke TextOut,hdc,XX+6*XX_GAP,YY+1*YY_GAP,offset buf1[0*28].recommend,3

			invoke TextOut,hdc,XX+0*XX_GAP,YY+2*YY_GAP,offset buf1[1*28].goods_name,4
            invoke TextOut,hdc,XX+1*XX_GAP,YY+2*YY_GAP,offset buf1[1*28].discount,3
            invoke TextOut,hdc,XX+2*XX_GAP,YY+2*YY_GAP,offset buf1[1*28].price_in,3
            invoke TextOut,hdc,XX+3*XX_GAP,YY+2*YY_GAP,offset buf1[1*28].price_out,3
            invoke TextOut,hdc,XX+4*XX_GAP,YY+2*YY_GAP,offset buf1[1*28].num_in,3
            invoke TextOut,hdc,XX+5*XX_GAP,YY+2*YY_GAP,offset buf1[1*28].num_out,3
			invoke TextOut,hdc,XX+6*XX_GAP,YY+2*YY_GAP,offset buf1[1*28].recommend,3

			invoke TextOut,hdc,XX+0*XX_GAP,YY+3*YY_GAP,offset buf1[2*28].goods_name,10
            invoke TextOut,hdc,XX+1*XX_GAP,YY+3*YY_GAP,offset buf1[2*28].discount,3
            invoke TextOut,hdc,XX+2*XX_GAP,YY+3*YY_GAP,offset buf1[2*28].price_in,3
            invoke TextOut,hdc,XX+3*XX_GAP,YY+3*YY_GAP,offset buf1[2*28].price_out,3
            invoke TextOut,hdc,XX+4*XX_GAP,YY+3*YY_GAP,offset buf1[2*28].num_in,3
            invoke TextOut,hdc,XX+5*XX_GAP,YY+3*YY_GAP,offset buf1[2*28].num_out,3
			invoke TextOut,hdc,XX+6*XX_GAP,YY+3*YY_GAP,offset buf1[2*28].recommend,3

			invoke TextOut,hdc,XX+0*XX_GAP,YY+4*YY_GAP,offset buf1[3*28].goods_name,10
            invoke TextOut,hdc,XX+1*XX_GAP,YY+4*YY_GAP,offset buf1[3*28].discount,3
            invoke TextOut,hdc,XX+2*XX_GAP,YY+4*YY_GAP,offset buf1[3*28].price_in,3
            invoke TextOut,hdc,XX+3*XX_GAP,YY+4*YY_GAP,offset buf1[3*28].price_out,3
            invoke TextOut,hdc,XX+4*XX_GAP,YY+4*YY_GAP,offset buf1[3*28].num_in,3
            invoke TextOut,hdc,XX+5*XX_GAP,YY+4*YY_GAP,offset buf1[3*28].num_out,3
			invoke TextOut,hdc,XX+6*XX_GAP,YY+4*YY_GAP,offset buf1[3*28].recommend,3

			invoke TextOut,hdc,XX+0*XX_GAP,YY+5*YY_GAP,offset buf1[4*28].goods_name,10
            invoke TextOut,hdc,XX+1*XX_GAP,YY+5*YY_GAP,offset buf1[4*28].discount,3
            invoke TextOut,hdc,XX+2*XX_GAP,YY+5*YY_GAP,offset buf1[4*28].price_in,3
            invoke TextOut,hdc,XX+3*XX_GAP,YY+5*YY_GAP,offset buf1[4*28].price_out,3
            invoke TextOut,hdc,XX+4*XX_GAP,YY+5*YY_GAP,offset buf1[4*28].num_in,3
            invoke TextOut,hdc,XX+5*XX_GAP,YY+5*YY_GAP,offset buf1[4*28].num_out,3
			invoke TextOut,hdc,XX+6*XX_GAP,YY+5*YY_GAP,offset buf1[4*28].recommend,3
		ret
Display      endp
           
Compute_all proc near 
	lea edi,count
	mov byte ptr[edi],0
	loop5:
		lea esi,buf
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
		cmp byte ptr [esi],n
		js loop5;为负转
        ret
Compute_all endp

;将32位无符号数转换为10进制数
;入口参数：num:16位无符号数
;buf:存放转换后数字字符串的缓存区首址
radix proc near num:word,buffer:dword
	push esi
	push edi
	
	movsx eax,num
	mov esi,buffer
	mov ebx,10
	xor cx,cx;计数器清零
	lop1:
	xor edx,edx
	div ebx
	push dx
	inc cx
	or eax,eax
	jnz lop1
	lop2:
	pop ax
	add al,30h
	mov [esi],al
	inc esi
	loop lop2
	pop edi
	pop esi
	ret
radix endp

 end  Start
