
bomb：     文件格式 elf32-i386


Disassembly of section .init:

080486f4 <_init>:
 80486f4:	53                   	push   %ebx
 80486f5:	83 ec 08             	sub    $0x8,%esp
 80486f8:	e8 13 02 00 00       	call   8048910 <__x86.get_pc_thunk.bx>
 80486fd:	81 c3 03 39 00 00    	add    $0x3903,%ebx
 8048703:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 8048709:	85 c0                	test   %eax,%eax
 804870b:	74 05                	je     8048712 <_init+0x1e>
 804870d:	e8 be 01 00 00       	call   80488d0 <__sprintf_chk@plt+0x10>
 8048712:	83 c4 08             	add    $0x8,%esp
 8048715:	5b                   	pop    %ebx
 8048716:	c3                   	ret    

Disassembly of section .plt:

08048720 <read@plt-0x10>:
 8048720:	ff 35 04 c0 04 08    	pushl  0x804c004
 8048726:	ff 25 08 c0 04 08    	jmp    *0x804c008
 804872c:	00 00                	add    %al,(%eax)
	...

08048730 <read@plt>:
 8048730:	ff 25 0c c0 04 08    	jmp    *0x804c00c
 8048736:	68 00 00 00 00       	push   $0x0
 804873b:	e9 e0 ff ff ff       	jmp    8048720 <_init+0x2c>

08048740 <fflush@plt>:
 8048740:	ff 25 10 c0 04 08    	jmp    *0x804c010
 8048746:	68 08 00 00 00       	push   $0x8
 804874b:	e9 d0 ff ff ff       	jmp    8048720 <_init+0x2c>

08048750 <fgets@plt>:
 8048750:	ff 25 14 c0 04 08    	jmp    *0x804c014
 8048756:	68 10 00 00 00       	push   $0x10
 804875b:	e9 c0 ff ff ff       	jmp    8048720 <_init+0x2c>

08048760 <signal@plt>:
 8048760:	ff 25 18 c0 04 08    	jmp    *0x804c018
 8048766:	68 18 00 00 00       	push   $0x18
 804876b:	e9 b0 ff ff ff       	jmp    8048720 <_init+0x2c>

08048770 <sleep@plt>:
 8048770:	ff 25 1c c0 04 08    	jmp    *0x804c01c
 8048776:	68 20 00 00 00       	push   $0x20
 804877b:	e9 a0 ff ff ff       	jmp    8048720 <_init+0x2c>

08048780 <alarm@plt>:
 8048780:	ff 25 20 c0 04 08    	jmp    *0x804c020
 8048786:	68 28 00 00 00       	push   $0x28
 804878b:	e9 90 ff ff ff       	jmp    8048720 <_init+0x2c>

08048790 <__stack_chk_fail@plt>:
 8048790:	ff 25 24 c0 04 08    	jmp    *0x804c024
 8048796:	68 30 00 00 00       	push   $0x30
 804879b:	e9 80 ff ff ff       	jmp    8048720 <_init+0x2c>

080487a0 <strcpy@plt>:
 80487a0:	ff 25 28 c0 04 08    	jmp    *0x804c028
 80487a6:	68 38 00 00 00       	push   $0x38
 80487ab:	e9 70 ff ff ff       	jmp    8048720 <_init+0x2c>

080487b0 <getenv@plt>:
 80487b0:	ff 25 2c c0 04 08    	jmp    *0x804c02c
 80487b6:	68 40 00 00 00       	push   $0x40
 80487bb:	e9 60 ff ff ff       	jmp    8048720 <_init+0x2c>

080487c0 <puts@plt>:
 80487c0:	ff 25 30 c0 04 08    	jmp    *0x804c030
 80487c6:	68 48 00 00 00       	push   $0x48
 80487cb:	e9 50 ff ff ff       	jmp    8048720 <_init+0x2c>

080487d0 <__memmove_chk@plt>:
 80487d0:	ff 25 34 c0 04 08    	jmp    *0x804c034
 80487d6:	68 50 00 00 00       	push   $0x50
 80487db:	e9 40 ff ff ff       	jmp    8048720 <_init+0x2c>

080487e0 <exit@plt>:
 80487e0:	ff 25 38 c0 04 08    	jmp    *0x804c038
 80487e6:	68 58 00 00 00       	push   $0x58
 80487eb:	e9 30 ff ff ff       	jmp    8048720 <_init+0x2c>

080487f0 <__libc_start_main@plt>:
 80487f0:	ff 25 3c c0 04 08    	jmp    *0x804c03c
 80487f6:	68 60 00 00 00       	push   $0x60
 80487fb:	e9 20 ff ff ff       	jmp    8048720 <_init+0x2c>

08048800 <write@plt>:
 8048800:	ff 25 40 c0 04 08    	jmp    *0x804c040
 8048806:	68 68 00 00 00       	push   $0x68
 804880b:	e9 10 ff ff ff       	jmp    8048720 <_init+0x2c>

08048810 <__isoc99_sscanf@plt>:
 8048810:	ff 25 44 c0 04 08    	jmp    *0x804c044
 8048816:	68 70 00 00 00       	push   $0x70
 804881b:	e9 00 ff ff ff       	jmp    8048720 <_init+0x2c>

08048820 <fopen@plt>:
 8048820:	ff 25 48 c0 04 08    	jmp    *0x804c048
 8048826:	68 78 00 00 00       	push   $0x78
 804882b:	e9 f0 fe ff ff       	jmp    8048720 <_init+0x2c>

08048830 <__errno_location@plt>:
 8048830:	ff 25 4c c0 04 08    	jmp    *0x804c04c
 8048836:	68 80 00 00 00       	push   $0x80
 804883b:	e9 e0 fe ff ff       	jmp    8048720 <_init+0x2c>

08048840 <__printf_chk@plt>:
 8048840:	ff 25 50 c0 04 08    	jmp    *0x804c050
 8048846:	68 88 00 00 00       	push   $0x88
 804884b:	e9 d0 fe ff ff       	jmp    8048720 <_init+0x2c>

08048850 <socket@plt>:
 8048850:	ff 25 54 c0 04 08    	jmp    *0x804c054
 8048856:	68 90 00 00 00       	push   $0x90
 804885b:	e9 c0 fe ff ff       	jmp    8048720 <_init+0x2c>

08048860 <__fprintf_chk@plt>:
 8048860:	ff 25 58 c0 04 08    	jmp    *0x804c058
 8048866:	68 98 00 00 00       	push   $0x98
 804886b:	e9 b0 fe ff ff       	jmp    8048720 <_init+0x2c>

08048870 <gethostbyname@plt>:
 8048870:	ff 25 5c c0 04 08    	jmp    *0x804c05c
 8048876:	68 a0 00 00 00       	push   $0xa0
 804887b:	e9 a0 fe ff ff       	jmp    8048720 <_init+0x2c>

08048880 <strtol@plt>:
 8048880:	ff 25 60 c0 04 08    	jmp    *0x804c060
 8048886:	68 a8 00 00 00       	push   $0xa8
 804888b:	e9 90 fe ff ff       	jmp    8048720 <_init+0x2c>

08048890 <connect@plt>:
 8048890:	ff 25 64 c0 04 08    	jmp    *0x804c064
 8048896:	68 b0 00 00 00       	push   $0xb0
 804889b:	e9 80 fe ff ff       	jmp    8048720 <_init+0x2c>

080488a0 <close@plt>:
 80488a0:	ff 25 68 c0 04 08    	jmp    *0x804c068
 80488a6:	68 b8 00 00 00       	push   $0xb8
 80488ab:	e9 70 fe ff ff       	jmp    8048720 <_init+0x2c>

080488b0 <__ctype_b_loc@plt>:
 80488b0:	ff 25 6c c0 04 08    	jmp    *0x804c06c
 80488b6:	68 c0 00 00 00       	push   $0xc0
 80488bb:	e9 60 fe ff ff       	jmp    8048720 <_init+0x2c>

080488c0 <__sprintf_chk@plt>:
 80488c0:	ff 25 70 c0 04 08    	jmp    *0x804c070
 80488c6:	68 c8 00 00 00       	push   $0xc8
 80488cb:	e9 50 fe ff ff       	jmp    8048720 <_init+0x2c>

Disassembly of section .plt.got:

080488d0 <.plt.got>:
 80488d0:	ff 25 fc bf 04 08    	jmp    *0x804bffc
 80488d6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

080488e0 <_start>:
 80488e0:	31 ed                	xor    %ebp,%ebp
 80488e2:	5e                   	pop    %esi
 80488e3:	89 e1                	mov    %esp,%ecx
 80488e5:	83 e4 f0             	and    $0xfffffff0,%esp
 80488e8:	50                   	push   %eax
 80488e9:	54                   	push   %esp
 80488ea:	52                   	push   %edx
 80488eb:	68 40 9f 04 08       	push   $0x8049f40
 80488f0:	68 e0 9e 04 08       	push   $0x8049ee0
 80488f5:	51                   	push   %ecx
 80488f6:	56                   	push   %esi
 80488f7:	68 db 89 04 08       	push   $0x80489db
 80488fc:	e8 ef fe ff ff       	call   80487f0 <__libc_start_main@plt>
 8048901:	f4                   	hlt    
 8048902:	66 90                	xchg   %ax,%ax
 8048904:	66 90                	xchg   %ax,%ax
 8048906:	66 90                	xchg   %ax,%ax
 8048908:	66 90                	xchg   %ax,%ax
 804890a:	66 90                	xchg   %ax,%ax
 804890c:	66 90                	xchg   %ax,%ax
 804890e:	66 90                	xchg   %ax,%ax

08048910 <__x86.get_pc_thunk.bx>:
 8048910:	8b 1c 24             	mov    (%esp),%ebx
 8048913:	c3                   	ret    
 8048914:	66 90                	xchg   %ax,%ax
 8048916:	66 90                	xchg   %ax,%ax
 8048918:	66 90                	xchg   %ax,%ax
 804891a:	66 90                	xchg   %ax,%ax
 804891c:	66 90                	xchg   %ax,%ax
 804891e:	66 90                	xchg   %ax,%ax

08048920 <deregister_tm_clones>:
 8048920:	b8 a3 c3 04 08       	mov    $0x804c3a3,%eax
 8048925:	2d a0 c3 04 08       	sub    $0x804c3a0,%eax
 804892a:	83 f8 06             	cmp    $0x6,%eax
 804892d:	76 1a                	jbe    8048949 <deregister_tm_clones+0x29>
 804892f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048934:	85 c0                	test   %eax,%eax
 8048936:	74 11                	je     8048949 <deregister_tm_clones+0x29>
 8048938:	55                   	push   %ebp
 8048939:	89 e5                	mov    %esp,%ebp
 804893b:	83 ec 14             	sub    $0x14,%esp
 804893e:	68 a0 c3 04 08       	push   $0x804c3a0
 8048943:	ff d0                	call   *%eax
 8048945:	83 c4 10             	add    $0x10,%esp
 8048948:	c9                   	leave  
 8048949:	f3 c3                	repz ret 
 804894b:	90                   	nop
 804894c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

08048950 <register_tm_clones>:
 8048950:	b8 a0 c3 04 08       	mov    $0x804c3a0,%eax
 8048955:	2d a0 c3 04 08       	sub    $0x804c3a0,%eax
 804895a:	c1 f8 02             	sar    $0x2,%eax
 804895d:	89 c2                	mov    %eax,%edx
 804895f:	c1 ea 1f             	shr    $0x1f,%edx
 8048962:	01 d0                	add    %edx,%eax
 8048964:	d1 f8                	sar    %eax
 8048966:	74 1b                	je     8048983 <register_tm_clones+0x33>
 8048968:	ba 00 00 00 00       	mov    $0x0,%edx
 804896d:	85 d2                	test   %edx,%edx
 804896f:	74 12                	je     8048983 <register_tm_clones+0x33>
 8048971:	55                   	push   %ebp
 8048972:	89 e5                	mov    %esp,%ebp
 8048974:	83 ec 10             	sub    $0x10,%esp
 8048977:	50                   	push   %eax
 8048978:	68 a0 c3 04 08       	push   $0x804c3a0
 804897d:	ff d2                	call   *%edx
 804897f:	83 c4 10             	add    $0x10,%esp
 8048982:	c9                   	leave  
 8048983:	f3 c3                	repz ret 
 8048985:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048989:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048990 <__do_global_dtors_aux>:
 8048990:	80 3d c8 c3 04 08 00 	cmpb   $0x0,0x804c3c8
 8048997:	75 13                	jne    80489ac <__do_global_dtors_aux+0x1c>
 8048999:	55                   	push   %ebp
 804899a:	89 e5                	mov    %esp,%ebp
 804899c:	83 ec 08             	sub    $0x8,%esp
 804899f:	e8 7c ff ff ff       	call   8048920 <deregister_tm_clones>
 80489a4:	c6 05 c8 c3 04 08 01 	movb   $0x1,0x804c3c8
 80489ab:	c9                   	leave  
 80489ac:	f3 c3                	repz ret 
 80489ae:	66 90                	xchg   %ax,%ax

080489b0 <frame_dummy>:
 80489b0:	b8 10 bf 04 08       	mov    $0x804bf10,%eax
 80489b5:	8b 10                	mov    (%eax),%edx
 80489b7:	85 d2                	test   %edx,%edx
 80489b9:	75 05                	jne    80489c0 <frame_dummy+0x10>
 80489bb:	eb 93                	jmp    8048950 <register_tm_clones>
 80489bd:	8d 76 00             	lea    0x0(%esi),%esi
 80489c0:	ba 00 00 00 00       	mov    $0x0,%edx
 80489c5:	85 d2                	test   %edx,%edx
 80489c7:	74 f2                	je     80489bb <frame_dummy+0xb>
 80489c9:	55                   	push   %ebp
 80489ca:	89 e5                	mov    %esp,%ebp
 80489cc:	83 ec 14             	sub    $0x14,%esp
 80489cf:	50                   	push   %eax
 80489d0:	ff d2                	call   *%edx
 80489d2:	83 c4 10             	add    $0x10,%esp
 80489d5:	c9                   	leave  
 80489d6:	e9 75 ff ff ff       	jmp    8048950 <register_tm_clones>

080489db <main>:
 80489db:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 80489df:	83 e4 f0             	and    $0xfffffff0,%esp
 80489e2:	ff 71 fc             	pushl  -0x4(%ecx)
 80489e5:	55                   	push   %ebp
 80489e6:	89 e5                	mov    %esp,%ebp
 80489e8:	53                   	push   %ebx
 80489e9:	51                   	push   %ecx
 80489ea:	8b 01                	mov    (%ecx),%eax
 80489ec:	8b 59 04             	mov    0x4(%ecx),%ebx
 80489ef:	83 f8 01             	cmp    $0x1,%eax
 80489f2:	0f 84 01 01 00 00    	je     8048af9 <main+0x11e>
 80489f8:	83 f8 02             	cmp    $0x2,%eax
 80489fb:	0f 85 24 01 00 00    	jne    8048b25 <main+0x14a>
 8048a01:	83 ec 08             	sub    $0x8,%esp
 8048a04:	68 60 9f 04 08       	push   $0x8049f60
 8048a09:	ff 73 04             	pushl  0x4(%ebx)
 8048a0c:	e8 0f fe ff ff       	call   8048820 <fopen@plt>
 8048a11:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 8048a16:	83 c4 10             	add    $0x10,%esp
 8048a19:	85 c0                	test   %eax,%eax
 8048a1b:	0f 84 e7 00 00 00    	je     8048b08 <main+0x12d>
 8048a21:	e8 e6 06 00 00       	call   804910c <initialize_bomb>
 8048a26:	83 ec 0c             	sub    $0xc,%esp
 8048a29:	68 e4 9f 04 08       	push   $0x8049fe4
 8048a2e:	e8 8d fd ff ff       	call   80487c0 <puts@plt>
 8048a33:	c7 04 24 20 a0 04 08 	movl   $0x804a020,(%esp)
 8048a3a:	e8 81 fd ff ff       	call   80487c0 <puts@plt>
 8048a3f:	e8 b8 07 00 00       	call   80491fc <read_line>
 8048a44:	89 04 24             	mov    %eax,(%esp)
 8048a47:	e8 f6 00 00 00       	call   8048b42 <phase_1>
 8048a4c:	e8 aa 08 00 00       	call   80492fb <phase_defused>
 8048a51:	c7 04 24 4c a0 04 08 	movl   $0x804a04c,(%esp)
 8048a58:	e8 63 fd ff ff       	call   80487c0 <puts@plt>
 8048a5d:	e8 9a 07 00 00       	call   80491fc <read_line>
 8048a62:	89 04 24             	mov    %eax,(%esp)
 8048a65:	e8 fb 00 00 00       	call   8048b65 <phase_2>
 8048a6a:	e8 8c 08 00 00       	call   80492fb <phase_defused>
 8048a6f:	c7 04 24 99 9f 04 08 	movl   $0x8049f99,(%esp)
 8048a76:	e8 45 fd ff ff       	call   80487c0 <puts@plt>
 8048a7b:	e8 7c 07 00 00       	call   80491fc <read_line>
 8048a80:	89 04 24             	mov    %eax,(%esp)
 8048a83:	e8 4c 01 00 00       	call   8048bd4 <phase_3>
 8048a88:	e8 6e 08 00 00       	call   80492fb <phase_defused>
 8048a8d:	c7 04 24 b7 9f 04 08 	movl   $0x8049fb7,(%esp)
 8048a94:	e8 27 fd ff ff       	call   80487c0 <puts@plt>
 8048a99:	e8 5e 07 00 00       	call   80491fc <read_line>
 8048a9e:	89 04 24             	mov    %eax,(%esp)
 8048aa1:	e8 db 02 00 00       	call   8048d81 <phase_4>
 8048aa6:	e8 50 08 00 00       	call   80492fb <phase_defused>
 8048aab:	c7 04 24 78 a0 04 08 	movl   $0x804a078,(%esp)
 8048ab2:	e8 09 fd ff ff       	call   80487c0 <puts@plt>
 8048ab7:	e8 40 07 00 00       	call   80491fc <read_line>
 8048abc:	89 04 24             	mov    %eax,(%esp)
 8048abf:	e8 31 03 00 00       	call   8048df5 <phase_5>
 8048ac4:	e8 32 08 00 00       	call   80492fb <phase_defused>
 8048ac9:	c7 04 24 c6 9f 04 08 	movl   $0x8049fc6,(%esp)
 8048ad0:	e8 eb fc ff ff       	call   80487c0 <puts@plt>
 8048ad5:	e8 22 07 00 00       	call   80491fc <read_line>
 8048ada:	89 04 24             	mov    %eax,(%esp)
 8048add:	e8 95 03 00 00       	call   8048e77 <phase_6>
 8048ae2:	e8 14 08 00 00       	call   80492fb <phase_defused>
 8048ae7:	83 c4 10             	add    $0x10,%esp
 8048aea:	b8 00 00 00 00       	mov    $0x0,%eax
 8048aef:	8d 65 f8             	lea    -0x8(%ebp),%esp
 8048af2:	59                   	pop    %ecx
 8048af3:	5b                   	pop    %ebx
 8048af4:	5d                   	pop    %ebp
 8048af5:	8d 61 fc             	lea    -0x4(%ecx),%esp
 8048af8:	c3                   	ret    
 8048af9:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 8048afe:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 8048b03:	e9 19 ff ff ff       	jmp    8048a21 <main+0x46>
 8048b08:	ff 73 04             	pushl  0x4(%ebx)
 8048b0b:	ff 33                	pushl  (%ebx)
 8048b0d:	68 62 9f 04 08       	push   $0x8049f62
 8048b12:	6a 01                	push   $0x1
 8048b14:	e8 27 fd ff ff       	call   8048840 <__printf_chk@plt>
 8048b19:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048b20:	e8 bb fc ff ff       	call   80487e0 <exit@plt>
 8048b25:	83 ec 04             	sub    $0x4,%esp
 8048b28:	ff 33                	pushl  (%ebx)
 8048b2a:	68 7f 9f 04 08       	push   $0x8049f7f
 8048b2f:	6a 01                	push   $0x1
 8048b31:	e8 0a fd ff ff       	call   8048840 <__printf_chk@plt>
 8048b36:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048b3d:	e8 9e fc ff ff       	call   80487e0 <exit@plt>

08048b42 <phase_1>:
 8048b42:	83 ec 14             	sub    $0x14,%esp
 8048b45:	68 9c a0 04 08       	push   $0x804a09c
 8048b4a:	ff 74 24 1c          	pushl  0x1c(%esp)
 8048b4e:	e8 54 05 00 00       	call   80490a7 <strings_not_equal>
 8048b53:	83 c4 10             	add    $0x10,%esp
 8048b56:	85 c0                	test   %eax,%eax
 8048b58:	75 04                	jne    8048b5e <phase_1+0x1c>
 8048b5a:	83 c4 0c             	add    $0xc,%esp
 8048b5d:	c3                   	ret    
 8048b5e:	e8 39 06 00 00       	call   804919c <explode_bomb>
 8048b63:	eb f5                	jmp    8048b5a <phase_1+0x18>

08048b65 <phase_2>:
 8048b65:	56                   	push   %esi
 8048b66:	53                   	push   %ebx
 8048b67:	83 ec 2c             	sub    $0x2c,%esp
 8048b6a:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048b70:	89 44 24 24          	mov    %eax,0x24(%esp)
 8048b74:	31 c0                	xor    %eax,%eax
 8048b76:	8d 44 24 0c          	lea    0xc(%esp),%eax
 8048b7a:	50                   	push   %eax
 8048b7b:	ff 74 24 3c          	pushl  0x3c(%esp)
 8048b7f:	e8 3d 06 00 00       	call   80491c1 <read_six_numbers>
 8048b84:	83 c4 10             	add    $0x10,%esp
 8048b87:	83 7c 24 04 00       	cmpl   $0x0,0x4(%esp);第一个数为0
 8048b8c:	75 07                	jne    8048b95 <phase_2+0x30>
 8048b8e:	83 7c 24 08 01       	cmpl   $0x1,0x8(%esp);第二个数为1
 8048b93:	74 05                	je     8048b9a <phase_2+0x35>
 8048b95:	e8 02 06 00 00       	call   804919c <explode_bomb>
 8048b9a:	8d 5c 24 04          	lea    0x4(%esp),%ebx;$ebx=0xbfffeda4(1)
 8048b9e:	8d 74 24 14          	lea    0x14(%esp),%esi；5;$esi=0xbfffeda4(5)
 8048ba2:	eb 07                	jmp    8048bab <phase_2+0x46>
 8048ba4:	83 c3 04             	add    $0x4,%ebx;执行后指向下一个数据（第一次执行后指向第一个数据0）
 8048ba7:	39 f3                	cmp    %esi,%ebx;是否执行到第五个数据
 8048ba9:	74 11                	je     8048bbc <phase_2+0x57>
 8048bab:	8b 43 04             	mov    0x4(%ebx),%eax; 
 8048bae:	03 03                	add    (%ebx),%eax; eax = ebx + 后一个数
 8048bb0:	39 43 08             	cmp    %eax,0x8(%ebx);后一个数等于前两个数和
 8048bb3:	74 ef                	je     8048ba4 <phase_2+0x3f>
 8048bb5:	e8 e2 05 00 00       	call   804919c <explode_bomb>
 8048bba:	eb e8                	jmp    8048ba4 <phase_2+0x3f>
 8048bbc:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048bc0:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048bc7:	75 06                	jne    8048bcf <phase_2+0x6a>
 8048bc9:	83 c4 24             	add    $0x24,%esp
 8048bcc:	5b                   	pop    %ebx
 8048bcd:	5e                   	pop    %esi
 8048bce:	c3                   	ret    
 8048bcf:	e8 bc fb ff ff       	call   8048790 <__stack_chk_fail@plt>

08048bd4 <phase_3>:
 8048bd4:	83 ec 28             	sub    $0x28,%esp
 8048bd7:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048bdd:	89 44 24 18          	mov    %eax,0x18(%esp)
 8048be1:	31 c0                	xor    %eax,%eax
 8048be3:	8d 44 24 14          	lea    0x14(%esp),%eax
 8048be7:	50                   	push   %eax
 8048be8:	8d 44 24 13          	lea    0x13(%esp),%eax
 8048bec:	50                   	push   %eax
 8048bed:	8d 44 24 18          	lea    0x18(%esp),%eax
 8048bf1:	50                   	push   %eax
 8048bf2:	68 fe a0 04 08       	push   $0x804a0fe
 8048bf7:	ff 74 24 3c          	pushl  0x3c(%esp)
 8048bfb:	e8 10 fc ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048c00:	83 c4 20             	add    $0x20,%esp
 8048c03:	83 f8 02             	cmp    $0x2,%eax
 8048c06:	7e 16                	jle    8048c1e <phase_3+0x4a>
 8048c08:	83 7c 24 04 07       	cmpl   $0x7,0x4(%esp);第一个参数:小于8的整数
 8048c0d:	0f 87 00 01 00 00    	ja     8048d13 <phase_3+0x13f>
 8048c13:	8b 44 24 04          	mov    0x4(%esp),%eax
 8048c17:	ff 24 85 10 a1 04 08 	jmp    *0x804a110(,%eax,4);跳转地址表
 8048c1e:	e8 79 05 00 00       	call   804919c <explode_bomb>
 8048c23:	eb e3                	jmp    8048c08 <phase_3+0x34>
 8048c25:	b8 6c 00 00 00       	mov    $0x6c,%eax;开始的地方
 8048c2a:	81 7c 24 08 1f 01 00 	cmpl   $0x11f,0x8(%esp);-------c =11f
 8048c31:	00 
 8048c32:	0f 84 e5 00 00 00    	je     8048d1d <phase_3+0x149>
 8048c38:	e8 5f 05 00 00       	call   804919c <explode_bomb>
 8048c3d:	b8 6c 00 00 00       	mov    $0x6c,%eax
 8048c42:	e9 d6 00 00 00       	jmp    8048d1d <phase_3+0x149>
 8048c47:	b8 77 00 00 00       	mov    $0x77,%eax
 8048c4c:	83 7c 24 08 65       	cmpl   $0x65,0x8(%esp);--------c = 0x65
 8048c51:	0f 84 c6 00 00 00    	je     8048d1d <phase_3+0x149>
 8048c57:	e8 40 05 00 00       	call   804919c <explode_bomb>
 8048c5c:	b8 77 00 00 00       	mov    $0x77,%eax
 8048c61:	e9 b7 00 00 00       	jmp    8048d1d <phase_3+0x149>
 8048c66:	b8 6e 00 00 00       	mov    $0x6e,%eax
 8048c6b:	81 7c 24 08 ae 03 00 	cmpl   $0x3ae,0x8(%esp);------c=0x3ae
 8048c72:	00 
 8048c73:	0f 84 a4 00 00 00    	je     8048d1d <phase_3+0x149>
 8048c79:	e8 1e 05 00 00       	call   804919c <explode_bomb>
 8048c7e:	b8 6e 00 00 00       	mov    $0x6e,%eax
 8048c83:	e9 95 00 00 00       	jmp    8048d1d <phase_3+0x149>
 8048c88:	b8 70 00 00 00       	mov    $0x70,%eax
 8048c8d:	81 7c 24 08 f9 00 00 	cmpl   $0xf9,0x8(%esp);-----c=0xf9
 8048c94:	00 
 8048c95:	0f 84 82 00 00 00    	je     8048d1d <phase_3+0x149>
 8048c9b:	e8 fc 04 00 00       	call   804919c <explode_bomb>
 8048ca0:	b8 70 00 00 00       	mov    $0x70,%eax
 8048ca5:	eb 76                	jmp    8048d1d <phase_3+0x149>
 8048ca7:	b8 79 00 00 00       	mov    $0x79,%eax
 8048cac:	81 7c 24 08 ed 00 00 	cmpl   $0xed,0x8(%esp);-------c=0xed
 8048cb3:	00 
 8048cb4:	74 67                	je     8048d1d <phase_3+0x149>
 8048cb6:	e8 e1 04 00 00       	call   804919c <explode_bomb>
 8048cbb:	b8 79 00 00 00       	mov    $0x79,%eax
 8048cc0:	eb 5b                	jmp    8048d1d <phase_3+0x149>
 8048cc2:	b8 66 00 00 00       	mov    $0x66,%eax
 8048cc7:	81 7c 24 08 cd 00 00 	cmpl   $0xcd,0x8(%esp);--------c=0xcd
 8048cce:	00 
 8048ccf:	74 4c                	je     8048d1d <phase_3+0x149>
 8048cd1:	e8 c6 04 00 00       	call   804919c <explode_bomb>
 8048cd6:	b8 66 00 00 00       	mov    $0x66,%eax
 8048cdb:	eb 40                	jmp    8048d1d <phase_3+0x149>
 8048cdd:	b8 75 00 00 00       	mov    $0x75,%eax
 8048ce2:	81 7c 24 08 65 01 00 	cmpl   $0x165,0x8(%esp);------c=0x165
 8048ce9:	00 
 8048cea:	74 31                	je     8048d1d <phase_3+0x149>
 8048cec:	e8 ab 04 00 00       	call   804919c <explode_bomb>
 8048cf1:	b8 75 00 00 00       	mov    $0x75,%eax
 8048cf6:	eb 25                	jmp    8048d1d <phase_3+0x149>
 8048cf8:	b8 73 00 00 00       	mov    $0x73,%eax
 8048cfd:	81 7c 24 08 8d 00 00 	cmpl   $0x8d,0x8(%esp);--------c=0x8d
 8048d04:	00 
 8048d05:	74 16                	je     8048d1d <phase_3+0x149>
 8048d07:	e8 90 04 00 00       	call   804919c <explode_bomb>
 8048d0c:	b8 73 00 00 00       	mov    $0x73,%eax
 8048d11:	eb 0a                	jmp    8048d1d <phase_3+0x149>
 8048d13:	e8 84 04 00 00       	call   804919c <explode_bomb>
 8048d18:	b8 66 00 00 00       	mov    $0x66,%eax
 8048d1d:	3a 44 24 03          	cmp    0x3(%esp),%al
 8048d21:	74 05                	je     8048d28 <phase_3+0x154>
 8048d23:	e8 74 04 00 00       	call   804919c <explode_bomb>
 8048d28:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048d2c:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048d33:	75 04                	jne    8048d39 <phase_3+0x165>
 8048d35:	83 c4 1c             	add    $0x1c,%esp
 8048d38:	c3                   	ret    
 8048d39:	e8 52 fa ff ff       	call   8048790 <__stack_chk_fail@plt>

08048d3e <func4>:
 8048d3e:	57                   	push   %edi
 8048d3f:	56                   	push   %esi
 8048d40:	53                   	push   %ebx
 8048d41:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8048d45:	8b 7c 24 14          	mov    0x14(%esp),%edi
 8048d49:	85 db                	test   %ebx,%ebx
 8048d4b:	7e 2d                	jle    8048d7a <func4+0x3c>;ebx <= 0
 8048d4d:	89 f8                	mov    %edi,%eax
 8048d4f:	83 fb 01             	cmp    $0x1,%ebx
 8048d52:	74 22                	je     8048d76 <func4+0x38>;ebx = 1结束
 8048d54:	83 ec 08             	sub    $0x8,%esp
 8048d57:	57                   	push   %edi
 8048d58:	8d 43 ff             	lea    -0x1(%ebx),%eax
 8048d5b:	50                   	push   %eax
 8048d5c:	e8 dd ff ff ff       	call   8048d3e <func4>
 8048d61:	83 c4 08             	add    $0x8,%esp
 8048d64:	8d 34 07             	lea    (%edi,%eax,1),%esi
 8048d67:	57                   	push   %edi
 8048d68:	83 eb 02             	sub    $0x2,%ebx
 8048d6b:	53                   	push   %ebx
 8048d6c:	e8 cd ff ff ff       	call   8048d3e <func4>
 8048d71:	83 c4 10             	add    $0x10,%esp
 8048d74:	01 f0                	add    %esi,%eax
 8048d76:	5b                   	pop    %ebx
 8048d77:	5e                   	pop    %esi
 8048d78:	5f                   	pop    %edi
 8048d79:	c3                   	ret    
 8048d7a:	b8 00 00 00 00       	mov    $0x0,%eax
 8048d7f:	eb f5                	jmp    8048d76 <func4+0x38>

08048d81 <phase_4>:
 8048d81:	83 ec 1c             	sub    $0x1c,%esp
 8048d84:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048d8a:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048d8e:	31 c0                	xor    %eax,%eax
 8048d90:	8d 44 24 04          	lea    0x4(%esp),%eax
 8048d94:	50                   	push   %eax
 8048d95:	8d 44 24 0c          	lea    0xc(%esp),%eax
 8048d99:	50                   	push   %eax
 8048d9a:	68 4f a2 04 08       	push   $0x804a24f
 8048d9f:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048da3:	e8 68 fa ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8048da8:	83 c4 10             	add    $0x10,%esp
 8048dab:	83 f8 02             	cmp    $0x2,%eax;是否匹配到两个
 8048dae:	74 32                	je     8048de2 <phase_4+0x61>
 8048db0:	e8 e7 03 00 00       	call   804919c <explode_bomb>
 8048db5:	83 ec 08             	sub    $0x8,%esp
 8048db8:	ff 74 24 0c          	pushl  0xc(%esp);第二个参数
 8048dbc:	6a 06                	push   $0x6
 8048dbe:	e8 7b ff ff ff       	call   8048d3e <func4>
 8048dc3:	83 c4 10             	add    $0x10,%esp
 8048dc6:	3b 44 24 08          	cmp    0x8(%esp),%eax;第一个参数和eax比较，相等满足
 8048dca:	74 05                	je     8048dd1 <phase_4+0x50>
 8048dcc:	e8 cb 03 00 00       	call   804919c <explode_bomb>
 8048dd1:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048dd5:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048ddc:	75 12                	jne    8048df0 <phase_4+0x6f>
 8048dde:	83 c4 1c             	add    $0x1c,%esp
 8048de1:	c3                   	ret    
 8048de2:	8b 44 24 04          	mov    0x4(%esp),%eax;第二个参数放到eax
 8048de6:	83 e8 02             	sub    $0x2,%eax;第二个参数减2
 8048de9:	83 f8 02             	cmp    $0x2,%eax
 8048dec:	76 c7                	jbe    8048db5 <phase_4+0x34>;第二个参数小于等于4
 8048dee:	eb c0                	jmp    8048db0 <phase_4+0x2f>;第二个参数大于4，炸了
 8048df0:	e8 9b f9 ff ff       	call   8048790 <__stack_chk_fail@plt>

08048df5 <phase_5>:
 8048df5:	53                   	push   %ebx
 8048df6:	83 ec 24             	sub    $0x24,%esp
 8048df9:	8b 5c 24 2c          	mov    0x2c(%esp),%ebx
 8048dfd:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048e03:	89 44 24 18          	mov    %eax,0x18(%esp)
 8048e07:	31 c0                	xor    %eax,%eax
 8048e09:	53                   	push   %ebx
 8048e0a:	e8 79 02 00 00       	call   8049088 <string_length>
 8048e0f:	83 c4 10             	add    $0x10,%esp
 8048e12:	83 f8 06             	cmp    $0x6,%eax;字符串长度为6
 8048e15:	74 05                	je     8048e1c <phase_5+0x27>
 8048e17:	e8 80 03 00 00       	call   804919c <explode_bomb>
 8048e1c:	b8 00 00 00 00       	mov    $0x0,%eax
 8048e21:	0f b6 14 03          	movzbl (%ebx,%eax,1),%edx
 8048e25:	83 e2 0f             	and    $0xf,%edx
 8048e28:	0f b6 92 30 a1 04 08 	movzbl x0804a130(%edx),%edx
 8048e2f:	88 54 04 05          	mov    %dl,0x5(%esp,%eax,1)
 8048e33:	83 c0 01             	add    $0x1,%eax
 8048e36:	83 f8 06             	cmp    $0x6,%eax
 8048e39:	75 e6                	jne    8048e21 <phase_5+0x2c>
 8048e3b:	c6 44 24 0b 00       	movb   $0x0,0xb(%esp)
 8048e40:	83 ec 08             	sub    $0x8,%esp
 8048e43:	68 07 a1 04 08       	push   $0x804a107
 8048e48:	8d 44 24 11          	lea    0x11(%esp),%eax
 8048e4c:	50                   	push   %eax
 8048e4d:	e8 55 02 00 00       	call   80490a7 <strings_not_equal>
 8048e52:	83 c4 10             	add    $0x10,%esp
 8048e55:	85 c0                	test   %eax,%eax
 8048e57:	75 12                	jne    8048e6b <phase_5+0x76>
 8048e59:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048e5d:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048e64:	75 0c                	jne    8048e72 <phase_5+0x7d>
 8048e66:	83 c4 18             	add    $0x18,%esp
 8048e69:	5b                   	pop    %ebx
 8048e6a:	c3                   	ret    
 8048e6b:	e8 2c 03 00 00       	call   804919c <explode_bomb>
 8048e70:	eb e7                	jmp    8048e59 <phase_5+0x64>
 8048e72:	e8 19 f9 ff ff       	call   8048790 <__stack_chk_fail@plt>

08048e77 <phase_6>:
 8048e77:	56                   	push   %esi
 8048e78:	53                   	push   %ebx
 8048e79:	83 ec 4c             	sub    $0x4c,%esp
 8048e7c:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8048e82:	89 44 24 44          	mov    %eax,0x44(%esp)
 8048e86:	31 c0                	xor    %eax,%eax
 8048e88:	8d 44 24 14          	lea    0x14(%esp),%eax
 8048e8c:	50                   	push   %eax
 8048e8d:	ff 74 24 5c          	pushl  0x5c(%esp)
 8048e91:	e8 2b 03 00 00       	call   80491c1 <read_six_numbers>
 8048e96:	83 c4 10             	add    $0x10,%esp
 8048e99:	be 00 00 00 00       	mov    $0x0,%esi
 8048e9e:	eb 1c                	jmp    8048ebc <phase_6+0x45>
 8048ea0:	83 c6 01             	add    $0x1,%esi
 8048ea3:	83 fe 06             	cmp    $0x6,%esi
 8048ea6:	74 2e                	je     8048ed6 <phase_6+0x5f>
 8048ea8:	89 f3                	mov    %esi,%ebx
 8048eaa:	8b 44 9c 0c          	mov    0xc(%esp,%ebx,4),%eax
 8048eae:	39 44 b4 08          	cmp    %eax,0x8(%esp,%esi,4)
 8048eb2:	74 1b                	je     8048ecf <phase_6+0x58>
 8048eb4:	83 c3 01             	add    $0x1,%ebx
 8048eb7:	83 fb 05             	cmp    $0x5,%ebx
 8048eba:	7e ee                	jle    8048eaa <phase_6+0x33>;ebx>5跳出循环
 8048ebc:	8b 44 b4 0c          	mov    0xc(%esp,%esi,4),%eax
 8048ec0:	83 e8 01             	sub    $0x1,%eax
 8048ec3:	83 f8 05             	cmp    $0x5,%eax
 8048ec6:	76 d8                	jbe    8048ea0 <phase_6+0x29>;eax>5->boom!
 8048ec8:	e8 cf 02 00 00       	call   804919c <explode_bomb>
 8048ecd:	eb d1                	jmp    8048ea0 <phase_6+0x29>
 8048ecf:	e8 c8 02 00 00       	call   804919c <explode_bomb>
 8048ed4:	eb de                	jmp    8048eb4 <phase_6+0x3d>
 8048ed6:	bb 00 00 00 00       	mov    $0x0,%ebx
 8048edb:	89 de                	mov    %ebx,%esi
 8048edd:	8b 4c 9c 0c          	mov    0xc(%esp,%ebx,4),%ecx
 8048ee1:	b8 01 00 00 00       	mov    $0x1,%eax
 8048ee6:	ba 3c c1 04 08       	mov    $0x804c13c,%edx
 8048eeb:	83 f9 01             	cmp    $0x1,%ecx
 8048eee:	7e 0a                	jle    8048efa <phase_6+0x83>
 8048ef0:	8b 52 08             	mov    0x8(%edx),%edx
 8048ef3:	83 c0 01             	add    $0x1,%eax
 8048ef6:	39 c8                	cmp    %ecx,%eax
 8048ef8:	75 f6                	jne    8048ef0 <phase_6+0x79>
 8048efa:	89 54 b4 24          	mov    %edx,0x24(%esp,%esi,4)
 8048efe:	83 c3 01             	add    $0x1,%ebx
 8048f01:	83 fb 06             	cmp    $0x6,%ebx
 8048f04:	75 d5                	jne    8048edb <phase_6+0x64>
 8048f06:	8b 5c 24 24          	mov    0x24(%esp),%ebx
 8048f0a:	89 d9                	mov    %ebx,%ecx
 8048f0c:	b8 01 00 00 00       	mov    $0x1,%eax
 8048f11:	8b 54 84 24          	mov    0x24(%esp,%eax,4),%edx
 8048f15:	89 51 08             	mov    %edx,0x8(%ecx)
 8048f18:	83 c0 01             	add    $0x1,%eax
 8048f1b:	89 d1                	mov    %edx,%ecx
 8048f1d:	83 f8 06             	cmp    $0x6,%eax
 8048f20:	75 ef                	jne    8048f11 <phase_6+0x9a>
 8048f22:	c7 42 08 00 00 00 00 	movl   $0x0,0x8(%edx)
 8048f29:	be 05 00 00 00       	mov    $0x5,%esi
 8048f2e:	eb 08                	jmp    8048f38 <phase_6+0xc1>
 8048f30:	8b 5b 08             	mov    0x8(%ebx),%ebx
 8048f33:	83 ee 01             	sub    $0x1,%esi
 8048f36:	74 10                	je     8048f48 <phase_6+0xd1>
 8048f38:	8b 43 08             	mov    0x8(%ebx),%eax
 8048f3b:	8b 00                	mov    (%eax),%eax
 8048f3d:	39 03                	cmp    %eax,(%ebx)
 8048f3f:	7e ef                	jle    8048f30 <phase_6+0xb9>
 8048f41:	e8 56 02 00 00       	call   804919c <explode_bomb>
 8048f46:	eb e8                	jmp    8048f30 <phase_6+0xb9>
 8048f48:	8b 44 24 3c          	mov    0x3c(%esp),%eax
 8048f4c:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 8048f53:	75 06                	jne    8048f5b <phase_6+0xe4>
 8048f55:	83 c4 44             	add    $0x44,%esp
 8048f58:	5b                   	pop    %ebx
 8048f59:	5e                   	pop    %esi
 8048f5a:	c3                   	ret    
 8048f5b:	e8 30 f8 ff ff       	call   8048790 <__stack_chk_fail@plt>

08048f60 <fun7>:
 8048f60:	53                   	push   %ebx
 8048f61:	83 ec 08             	sub    $0x8,%esp
 8048f64:	8b 54 24 10          	mov    0x10(%esp),%edx
 8048f68:	8b 4c 24 14          	mov    0x14(%esp),%ecx
 8048f6c:	85 d2                	test   %edx,%edx
 8048f6e:	74 3a                	je     8048faa <fun7+0x4a>
 8048f70:	8b 1a                	mov    (%edx),%ebx
 8048f72:	39 cb                	cmp    %ecx,%ebx
 8048f74:	7f 21                	jg     8048f97 <fun7+0x37>
 8048f76:	b8 00 00 00 00       	mov    $0x0,%eax
 8048f7b:	39 cb                	cmp    %ecx,%ebx
 8048f7d:	74 13                	je     8048f92 <fun7+0x32>
 8048f7f:	83 ec 08             	sub    $0x8,%esp
 8048f82:	51                   	push   %ecx
 8048f83:	ff 72 08             	pushl  0x8(%edx)
 8048f86:	e8 d5 ff ff ff       	call   8048f60 <fun7>
 8048f8b:	83 c4 10             	add    $0x10,%esp
 8048f8e:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048f92:	83 c4 08             	add    $0x8,%esp
 8048f95:	5b                   	pop    %ebx
 8048f96:	c3                   	ret    
 8048f97:	83 ec 08             	sub    $0x8,%esp
 8048f9a:	51                   	push   %ecx
 8048f9b:	ff 72 04             	pushl  0x4(%edx)
 8048f9e:	e8 bd ff ff ff       	call   8048f60 <fun7>
 8048fa3:	83 c4 10             	add    $0x10,%esp
 8048fa6:	01 c0                	add    %eax,%eax
 8048fa8:	eb e8                	jmp    8048f92 <fun7+0x32>
 8048faa:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8048faf:	eb e1                	jmp    8048f92 <fun7+0x32>

08048fb1 <secret_phase>:
 8048fb1:	53                   	push   %ebx
 8048fb2:	83 ec 08             	sub    $0x8,%esp
 8048fb5:	e8 42 02 00 00       	call   80491fc <read_line>
 8048fba:	83 ec 04             	sub    $0x4,%esp
 8048fbd:	6a 0a                	push   $0xa
 8048fbf:	6a 00                	push   $0x0
 8048fc1:	50                   	push   %eax
 8048fc2:	e8 b9 f8 ff ff       	call   8048880 <strtol@plt>
 8048fc7:	89 c3                	mov    %eax,%ebx
 8048fc9:	8d 40 ff             	lea    -0x1(%eax),%eax
 8048fcc:	83 c4 10             	add    $0x10,%esp
 8048fcf:	3d e8 03 00 00       	cmp    $0x3e8,%eax
 8048fd4:	77 32                	ja     8049008 <secret_phase+0x57>
 8048fd6:	83 ec 08             	sub    $0x8,%esp
 8048fd9:	53                   	push   %ebx
 8048fda:	68 88 c0 04 08       	push   $0x804c088
 8048fdf:	e8 7c ff ff ff       	call   8048f60 <fun7>
 8048fe4:	83 c4 10             	add    $0x10,%esp
 8048fe7:	83 f8 01             	cmp    $0x1,%eax
 8048fea:	74 05                	je     8048ff1 <secret_phase+0x40>
 8048fec:	e8 ab 01 00 00       	call   804919c <explode_bomb>
 8048ff1:	83 ec 0c             	sub    $0xc,%esp
 8048ff4:	68 d8 a0 04 08       	push   $0x804a0d8
 8048ff9:	e8 c2 f7 ff ff       	call   80487c0 <puts@plt>
 8048ffe:	e8 f8 02 00 00       	call   80492fb <phase_defused>
 8049003:	83 c4 18             	add    $0x18,%esp
 8049006:	5b                   	pop    %ebx
 8049007:	c3                   	ret    
 8049008:	e8 8f 01 00 00       	call   804919c <explode_bomb>
 804900d:	eb c7                	jmp    8048fd6 <secret_phase+0x25>

0804900f <sig_handler>:
 804900f:	83 ec 18             	sub    $0x18,%esp
 8049012:	68 40 a1 04 08       	push   $0x804a140
 8049017:	e8 a4 f7 ff ff       	call   80487c0 <puts@plt>
 804901c:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
 8049023:	e8 48 f7 ff ff       	call   8048770 <sleep@plt>
 8049028:	83 c4 08             	add    $0x8,%esp
 804902b:	68 02 a2 04 08       	push   $0x804a202
 8049030:	6a 01                	push   $0x1
 8049032:	e8 09 f8 ff ff       	call   8048840 <__printf_chk@plt>
 8049037:	83 c4 04             	add    $0x4,%esp
 804903a:	ff 35 c4 c3 04 08    	pushl  0x804c3c4
 8049040:	e8 fb f6 ff ff       	call   8048740 <fflush@plt>
 8049045:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 804904c:	e8 1f f7 ff ff       	call   8048770 <sleep@plt>
 8049051:	c7 04 24 0a a2 04 08 	movl   $0x804a20a,(%esp)
 8049058:	e8 63 f7 ff ff       	call   80487c0 <puts@plt>
 804905d:	c7 04 24 10 00 00 00 	movl   $0x10,(%esp)
 8049064:	e8 77 f7 ff ff       	call   80487e0 <exit@plt>

08049069 <invalid_phase>:
 8049069:	83 ec 10             	sub    $0x10,%esp
 804906c:	ff 74 24 14          	pushl  0x14(%esp)
 8049070:	68 12 a2 04 08       	push   $0x804a212
 8049075:	6a 01                	push   $0x1
 8049077:	e8 c4 f7 ff ff       	call   8048840 <__printf_chk@plt>
 804907c:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049083:	e8 58 f7 ff ff       	call   80487e0 <exit@plt>

08049088 <string_length>:
 8049088:	8b 54 24 04          	mov    0x4(%esp),%edx
 804908c:	80 3a 00             	cmpb   $0x0,(%edx)
 804908f:	74 10                	je     80490a1 <string_length+0x19>
 8049091:	b8 00 00 00 00       	mov    $0x0,%eax
 8049096:	83 c0 01             	add    $0x1,%eax
 8049099:	80 3c 02 00          	cmpb   $0x0,(%edx,%eax,1)
 804909d:	75 f7                	jne    8049096 <string_length+0xe>
 804909f:	f3 c3                	repz ret 
 80490a1:	b8 00 00 00 00       	mov    $0x0,%eax
 80490a6:	c3                   	ret    

080490a7 <strings_not_equal>:
 80490a7:	57                   	push   %edi
 80490a8:	56                   	push   %esi
 80490a9:	53                   	push   %ebx
 80490aa:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 80490ae:	8b 74 24 14          	mov    0x14(%esp),%esi
 80490b2:	53                   	push   %ebx
 80490b3:	e8 d0 ff ff ff       	call   8049088 <string_length>
 80490b8:	89 c7                	mov    %eax,%edi
 80490ba:	89 34 24             	mov    %esi,(%esp)
 80490bd:	e8 c6 ff ff ff       	call   8049088 <string_length>
 80490c2:	83 c4 04             	add    $0x4,%esp
 80490c5:	ba 01 00 00 00       	mov    $0x1,%edx
 80490ca:	39 c7                	cmp    %eax,%edi
 80490cc:	74 06                	je     80490d4 <strings_not_equal+0x2d>
 80490ce:	89 d0                	mov    %edx,%eax
 80490d0:	5b                   	pop    %ebx
 80490d1:	5e                   	pop    %esi
 80490d2:	5f                   	pop    %edi
 80490d3:	c3                   	ret    
 80490d4:	0f b6 03             	movzbl (%ebx),%eax
 80490d7:	84 c0                	test   %al,%al
 80490d9:	74 23                	je     80490fe <strings_not_equal+0x57>
 80490db:	3a 06                	cmp    (%esi),%al
 80490dd:	75 26                	jne    8049105 <strings_not_equal+0x5e>
 80490df:	83 c3 01             	add    $0x1,%ebx
 80490e2:	83 c6 01             	add    $0x1,%esi
 80490e5:	0f b6 03             	movzbl (%ebx),%eax
 80490e8:	84 c0                	test   %al,%al
 80490ea:	74 0b                	je     80490f7 <strings_not_equal+0x50>
 80490ec:	3a 06                	cmp    (%esi),%al
 80490ee:	74 ef                	je     80490df <strings_not_equal+0x38>
 80490f0:	ba 01 00 00 00       	mov    $0x1,%edx
 80490f5:	eb d7                	jmp    80490ce <strings_not_equal+0x27>
 80490f7:	ba 00 00 00 00       	mov    $0x0,%edx
 80490fc:	eb d0                	jmp    80490ce <strings_not_equal+0x27>
 80490fe:	ba 00 00 00 00       	mov    $0x0,%edx
 8049103:	eb c9                	jmp    80490ce <strings_not_equal+0x27>
 8049105:	ba 01 00 00 00       	mov    $0x1,%edx
 804910a:	eb c2                	jmp    80490ce <strings_not_equal+0x27>

0804910c <initialize_bomb>:
 804910c:	83 ec 14             	sub    $0x14,%esp
 804910f:	68 0f 90 04 08       	push   $0x804900f
 8049114:	6a 02                	push   $0x2
 8049116:	e8 45 f6 ff ff       	call   8048760 <signal@plt>
 804911b:	83 c4 1c             	add    $0x1c,%esp
 804911e:	c3                   	ret    

0804911f <initialize_bomb_solve>:
 804911f:	f3 c3                	repz ret 

08049121 <blank_line>:
 8049121:	56                   	push   %esi
 8049122:	53                   	push   %ebx
 8049123:	83 ec 04             	sub    $0x4,%esp
 8049126:	8b 74 24 10          	mov    0x10(%esp),%esi
 804912a:	0f b6 1e             	movzbl (%esi),%ebx
 804912d:	84 db                	test   %bl,%bl
 804912f:	74 1b                	je     804914c <blank_line+0x2b>
 8049131:	e8 7a f7 ff ff       	call   80488b0 <__ctype_b_loc@plt>
 8049136:	83 c6 01             	add    $0x1,%esi
 8049139:	0f be db             	movsbl %bl,%ebx
 804913c:	8b 00                	mov    (%eax),%eax
 804913e:	f6 44 58 01 20       	testb  $0x20,0x1(%eax,%ebx,2)
 8049143:	75 e5                	jne    804912a <blank_line+0x9>
 8049145:	b8 00 00 00 00       	mov    $0x0,%eax
 804914a:	eb 05                	jmp    8049151 <blank_line+0x30>
 804914c:	b8 01 00 00 00       	mov    $0x1,%eax
 8049151:	83 c4 04             	add    $0x4,%esp
 8049154:	5b                   	pop    %ebx
 8049155:	5e                   	pop    %esi
 8049156:	c3                   	ret    

08049157 <skip>:
 8049157:	53                   	push   %ebx
 8049158:	83 ec 08             	sub    $0x8,%esp
 804915b:	83 ec 04             	sub    $0x4,%esp
 804915e:	ff 35 d0 c3 04 08    	pushl  0x804c3d0
 8049164:	6a 50                	push   $0x50
 8049166:	a1 cc c3 04 08       	mov    0x804c3cc,%eax
 804916b:	8d 04 80             	lea    (%eax,%eax,4),%eax
 804916e:	c1 e0 04             	shl    $0x4,%eax
 8049171:	05 e0 c3 04 08       	add    $0x804c3e0,%eax
 8049176:	50                   	push   %eax
 8049177:	e8 d4 f5 ff ff       	call   8048750 <fgets@plt>
 804917c:	89 c3                	mov    %eax,%ebx
 804917e:	83 c4 10             	add    $0x10,%esp
 8049181:	85 c0                	test   %eax,%eax
 8049183:	74 10                	je     8049195 <skip+0x3e>
 8049185:	83 ec 0c             	sub    $0xc,%esp
 8049188:	50                   	push   %eax
 8049189:	e8 93 ff ff ff       	call   8049121 <blank_line>
 804918e:	83 c4 10             	add    $0x10,%esp
 8049191:	85 c0                	test   %eax,%eax
 8049193:	75 c6                	jne    804915b <skip+0x4>
 8049195:	89 d8                	mov    %ebx,%eax
 8049197:	83 c4 08             	add    $0x8,%esp
 804919a:	5b                   	pop    %ebx
 804919b:	c3                   	ret    

0804919c <explode_bomb>:
 804919c:	83 ec 18             	sub    $0x18,%esp
 804919f:	68 23 a2 04 08       	push   $0x804a223
 80491a4:	e8 17 f6 ff ff       	call   80487c0 <puts@plt>
 80491a9:	c7 04 24 2c a2 04 08 	movl   $0x804a22c,(%esp)
 80491b0:	e8 0b f6 ff ff       	call   80487c0 <puts@plt>
 80491b5:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 80491bc:	e8 1f f6 ff ff       	call   80487e0 <exit@plt>

080491c1 <read_six_numbers>:
 80491c1:	83 ec 0c             	sub    $0xc,%esp
 80491c4:	8b 44 24 14          	mov    0x14(%esp),%eax
 80491c8:	8d 50 14             	lea    0x14(%eax),%edx
 80491cb:	52                   	push   %edx
 80491cc:	8d 50 10             	lea    0x10(%eax),%edx
 80491cf:	52                   	push   %edx
 80491d0:	8d 50 0c             	lea    0xc(%eax),%edx
 80491d3:	52                   	push   %edx
 80491d4:	8d 50 08             	lea    0x8(%eax),%edx
 80491d7:	52                   	push   %edx
 80491d8:	8d 50 04             	lea    0x4(%eax),%edx
 80491db:	52                   	push   %edx
 80491dc:	50                   	push   %eax
 80491dd:	68 43 a2 04 08       	push   $0x804a243
 80491e2:	ff 74 24 2c          	pushl  0x2c(%esp)
 80491e6:	e8 25 f6 ff ff       	call   8048810 <__isoc99_sscanf@plt>
 80491eb:	83 c4 20             	add    $0x20,%esp
 80491ee:	83 f8 05             	cmp    $0x5,%eax
 80491f1:	7e 04                	jle    80491f7 <read_six_numbers+0x36>
 80491f3:	83 c4 0c             	add    $0xc,%esp
 80491f6:	c3                   	ret    
 80491f7:	e8 a0 ff ff ff       	call   804919c <explode_bomb>

080491fc <read_line>:
 80491fc:	57                   	push   %edi
 80491fd:	56                   	push   %esi
 80491fe:	53                   	push   %ebx
 80491ff:	e8 53 ff ff ff       	call   8049157 <skip>
 8049204:	85 c0                	test   %eax,%eax
 8049206:	74 4b                	je     8049253 <read_line+0x57>
 8049208:	8b 15 cc c3 04 08    	mov    0x804c3cc,%edx
 804920e:	8d 1c 92             	lea    (%edx,%edx,4),%ebx
 8049211:	c1 e3 04             	shl    $0x4,%ebx
 8049214:	81 c3 e0 c3 04 08    	add    $0x804c3e0,%ebx
 804921a:	b8 00 00 00 00       	mov    $0x0,%eax
 804921f:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049224:	89 df                	mov    %ebx,%edi
 8049226:	f2 ae                	repnz scas %es:(%edi),%al
 8049228:	f7 d1                	not    %ecx
 804922a:	83 e9 01             	sub    $0x1,%ecx
 804922d:	83 f9 4e             	cmp    $0x4e,%ecx
 8049230:	0f 8f 8d 00 00 00    	jg     80492c3 <read_line+0xc7>
 8049236:	8d 04 92             	lea    (%edx,%edx,4),%eax
 8049239:	c1 e0 04             	shl    $0x4,%eax
 804923c:	c6 84 01 df c3 04 08 	movb   $0x0,0x804c3df(%ecx,%eax,1)
 8049243:	00 
 8049244:	83 c2 01             	add    $0x1,%edx
 8049247:	89 15 cc c3 04 08    	mov    %edx,0x804c3cc
 804924d:	89 d8                	mov    %ebx,%eax
 804924f:	5b                   	pop    %ebx
 8049250:	5e                   	pop    %esi
 8049251:	5f                   	pop    %edi
 8049252:	c3                   	ret    
 8049253:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 8049258:	39 05 d0 c3 04 08    	cmp    %eax,0x804c3d0
 804925e:	74 40                	je     80492a0 <read_line+0xa4>
 8049260:	83 ec 0c             	sub    $0xc,%esp
 8049263:	68 73 a2 04 08       	push   $0x804a273
 8049268:	e8 43 f5 ff ff       	call   80487b0 <getenv@plt>
 804926d:	83 c4 10             	add    $0x10,%esp
 8049270:	85 c0                	test   %eax,%eax
 8049272:	75 45                	jne    80492b9 <read_line+0xbd>
 8049274:	a1 c0 c3 04 08       	mov    0x804c3c0,%eax
 8049279:	a3 d0 c3 04 08       	mov    %eax,0x804c3d0
 804927e:	e8 d4 fe ff ff       	call   8049157 <skip>
 8049283:	85 c0                	test   %eax,%eax
 8049285:	75 81                	jne    8049208 <read_line+0xc>
 8049287:	83 ec 0c             	sub    $0xc,%esp
 804928a:	68 55 a2 04 08       	push   $0x804a255
 804928f:	e8 2c f5 ff ff       	call   80487c0 <puts@plt>
 8049294:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 804929b:	e8 40 f5 ff ff       	call   80487e0 <exit@plt>
 80492a0:	83 ec 0c             	sub    $0xc,%esp
 80492a3:	68 55 a2 04 08       	push   $0x804a255
 80492a8:	e8 13 f5 ff ff       	call   80487c0 <puts@plt>
 80492ad:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 80492b4:	e8 27 f5 ff ff       	call   80487e0 <exit@plt>
 80492b9:	83 ec 0c             	sub    $0xc,%esp
 80492bc:	6a 00                	push   $0x0
 80492be:	e8 1d f5 ff ff       	call   80487e0 <exit@plt>
 80492c3:	83 ec 0c             	sub    $0xc,%esp
 80492c6:	68 7e a2 04 08       	push   $0x804a27e
 80492cb:	e8 f0 f4 ff ff       	call   80487c0 <puts@plt>
 80492d0:	a1 cc c3 04 08       	mov    0x804c3cc,%eax
 80492d5:	8d 50 01             	lea    0x1(%eax),%edx
 80492d8:	89 15 cc c3 04 08    	mov    %edx,0x804c3cc
 80492de:	6b c0 50             	imul   $0x50,%eax,%eax
 80492e1:	05 e0 c3 04 08       	add    $0x804c3e0,%eax
 80492e6:	ba 99 a2 04 08       	mov    $0x804a299,%edx
 80492eb:	b9 04 00 00 00       	mov    $0x4,%ecx
 80492f0:	89 c7                	mov    %eax,%edi
 80492f2:	89 d6                	mov    %edx,%esi
 80492f4:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 80492f6:	e8 a1 fe ff ff       	call   804919c <explode_bomb>

080492fb <phase_defused>:
 80492fb:	83 ec 6c             	sub    $0x6c,%esp
 80492fe:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8049304:	89 44 24 5c          	mov    %eax,0x5c(%esp)
 8049308:	31 c0                	xor    %eax,%eax
 804930a:	83 3d cc c3 04 08 06 	cmpl   $0x6,0x804c3cc
 8049311:	74 11                	je     8049324 <phase_defused+0x29>
 8049313:	8b 44 24 5c          	mov    0x5c(%esp),%eax
 8049317:	65 33 05 14 00 00 00 	xor    %gs:0x14,%eax
 804931e:	75 7b                	jne    804939b <phase_defused+0xa0>
 8049320:	83 c4 6c             	add    $0x6c,%esp
 8049323:	c3                   	ret    
 8049324:	83 ec 0c             	sub    $0xc,%esp
 8049327:	8d 44 24 18          	lea    0x18(%esp),%eax
 804932b:	50                   	push   %eax
 804932c:	8d 44 24 18          	lea    0x18(%esp),%eax
 8049330:	50                   	push   %eax
 8049331:	8d 44 24 18          	lea    0x18(%esp),%eax
 8049335:	50                   	push   %eax
 8049336:	68 a9 a2 04 08       	push   $0x804a2a9
 804933b:	68 d0 c4 04 08       	push   $0x804c4d0
 8049340:	e8 cb f4 ff ff       	call   8048810 <__isoc99_sscanf@plt>
 8049345:	83 c4 20             	add    $0x20,%esp
 8049348:	83 f8 03             	cmp    $0x3,%eax
 804934b:	74 12                	je     804935f <phase_defused+0x64>
 804934d:	83 ec 0c             	sub    $0xc,%esp
 8049350:	68 d8 a1 04 08       	push   $0x804a1d8
 8049355:	e8 66 f4 ff ff       	call   80487c0 <puts@plt>
 804935a:	83 c4 10             	add    $0x10,%esp
 804935d:	eb b4                	jmp    8049313 <phase_defused+0x18>
 804935f:	83 ec 08             	sub    $0x8,%esp
 8049362:	68 b2 a2 04 08       	push   $0x804a2b2
 8049367:	8d 44 24 18          	lea    0x18(%esp),%eax
 804936b:	50                   	push   %eax
 804936c:	e8 36 fd ff ff       	call   80490a7 <strings_not_equal>
 8049371:	83 c4 10             	add    $0x10,%esp
 8049374:	85 c0                	test   %eax,%eax
 8049376:	75 d5                	jne    804934d <phase_defused+0x52>
 8049378:	83 ec 0c             	sub    $0xc,%esp
 804937b:	68 78 a1 04 08       	push   $0x804a178
 8049380:	e8 3b f4 ff ff       	call   80487c0 <puts@plt>
 8049385:	c7 04 24 a0 a1 04 08 	movl   $0x804a1a0,(%esp)
 804938c:	e8 2f f4 ff ff       	call   80487c0 <puts@plt>
 8049391:	e8 1b fc ff ff       	call   8048fb1 <secret_phase>
 8049396:	83 c4 10             	add    $0x10,%esp
 8049399:	eb b2                	jmp    804934d <phase_defused+0x52>
 804939b:	e8 f0 f3 ff ff       	call   8048790 <__stack_chk_fail@plt>

080493a0 <sigalrm_handler>:
 80493a0:	83 ec 0c             	sub    $0xc,%esp
 80493a3:	6a 00                	push   $0x0
 80493a5:	68 08 a3 04 08       	push   $0x804a308
 80493aa:	6a 01                	push   $0x1
 80493ac:	ff 35 a0 c3 04 08    	pushl  0x804c3a0
 80493b2:	e8 a9 f4 ff ff       	call   8048860 <__fprintf_chk@plt>
 80493b7:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 80493be:	e8 1d f4 ff ff       	call   80487e0 <exit@plt>

080493c3 <rio_readlineb>:
 80493c3:	55                   	push   %ebp
 80493c4:	57                   	push   %edi
 80493c5:	56                   	push   %esi
 80493c6:	53                   	push   %ebx
 80493c7:	83 ec 1c             	sub    $0x1c,%esp
 80493ca:	83 f9 01             	cmp    $0x1,%ecx
 80493cd:	76 79                	jbe    8049448 <rio_readlineb+0x85>
 80493cf:	89 d7                	mov    %edx,%edi
 80493d1:	89 c3                	mov    %eax,%ebx
 80493d3:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 80493d7:	bd 01 00 00 00       	mov    $0x1,%ebp
 80493dc:	8d 70 0c             	lea    0xc(%eax),%esi
 80493df:	eb 0a                	jmp    80493eb <rio_readlineb+0x28>
 80493e1:	e8 4a f4 ff ff       	call   8048830 <__errno_location@plt>
 80493e6:	83 38 04             	cmpl   $0x4,(%eax)
 80493e9:	75 66                	jne    8049451 <rio_readlineb+0x8e>
 80493eb:	8b 43 04             	mov    0x4(%ebx),%eax
 80493ee:	85 c0                	test   %eax,%eax
 80493f0:	7f 23                	jg     8049415 <rio_readlineb+0x52>
 80493f2:	83 ec 04             	sub    $0x4,%esp
 80493f5:	68 00 20 00 00       	push   $0x2000
 80493fa:	56                   	push   %esi
 80493fb:	ff 33                	pushl  (%ebx)
 80493fd:	e8 2e f3 ff ff       	call   8048730 <read@plt>
 8049402:	89 43 04             	mov    %eax,0x4(%ebx)
 8049405:	83 c4 10             	add    $0x10,%esp
 8049408:	85 c0                	test   %eax,%eax
 804940a:	78 d5                	js     80493e1 <rio_readlineb+0x1e>
 804940c:	85 c0                	test   %eax,%eax
 804940e:	74 48                	je     8049458 <rio_readlineb+0x95>
 8049410:	89 73 08             	mov    %esi,0x8(%ebx)
 8049413:	eb d6                	jmp    80493eb <rio_readlineb+0x28>
 8049415:	8b 4b 08             	mov    0x8(%ebx),%ecx
 8049418:	0f b6 11             	movzbl (%ecx),%edx
 804941b:	83 c1 01             	add    $0x1,%ecx
 804941e:	89 4b 08             	mov    %ecx,0x8(%ebx)
 8049421:	83 e8 01             	sub    $0x1,%eax
 8049424:	89 43 04             	mov    %eax,0x4(%ebx)
 8049427:	83 c7 01             	add    $0x1,%edi
 804942a:	88 57 ff             	mov    %dl,-0x1(%edi)
 804942d:	80 fa 0a             	cmp    $0xa,%dl
 8049430:	74 09                	je     804943b <rio_readlineb+0x78>
 8049432:	83 c5 01             	add    $0x1,%ebp
 8049435:	3b 6c 24 0c          	cmp    0xc(%esp),%ebp
 8049439:	75 b0                	jne    80493eb <rio_readlineb+0x28>
 804943b:	c6 07 00             	movb   $0x0,(%edi)
 804943e:	89 e8                	mov    %ebp,%eax
 8049440:	83 c4 1c             	add    $0x1c,%esp
 8049443:	5b                   	pop    %ebx
 8049444:	5e                   	pop    %esi
 8049445:	5f                   	pop    %edi
 8049446:	5d                   	pop    %ebp
 8049447:	c3                   	ret    
 8049448:	89 d7                	mov    %edx,%edi
 804944a:	bd 01 00 00 00       	mov    $0x1,%ebp
 804944f:	eb ea                	jmp    804943b <rio_readlineb+0x78>
 8049451:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049456:	eb 05                	jmp    804945d <rio_readlineb+0x9a>
 8049458:	b8 00 00 00 00       	mov    $0x0,%eax
 804945d:	85 c0                	test   %eax,%eax
 804945f:	75 0c                	jne    804946d <rio_readlineb+0xaa>
 8049461:	83 fd 01             	cmp    $0x1,%ebp
 8049464:	75 d5                	jne    804943b <rio_readlineb+0x78>
 8049466:	bd 00 00 00 00       	mov    $0x0,%ebp
 804946b:	eb d1                	jmp    804943e <rio_readlineb+0x7b>
 804946d:	bd ff ff ff ff       	mov    $0xffffffff,%ebp
 8049472:	eb ca                	jmp    804943e <rio_readlineb+0x7b>

08049474 <submitr>:
 8049474:	55                   	push   %ebp
 8049475:	57                   	push   %edi
 8049476:	56                   	push   %esi
 8049477:	53                   	push   %ebx
 8049478:	81 ec 60 a0 00 00    	sub    $0xa060,%esp
 804947e:	8b 9c 24 74 a0 00 00 	mov    0xa074(%esp),%ebx
 8049485:	8b 84 24 7c a0 00 00 	mov    0xa07c(%esp),%eax
 804948c:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8049490:	8b 84 24 80 a0 00 00 	mov    0xa080(%esp),%eax
 8049497:	89 44 24 10          	mov    %eax,0x10(%esp)
 804949b:	8b 84 24 84 a0 00 00 	mov    0xa084(%esp),%eax
 80494a2:	89 44 24 14          	mov    %eax,0x14(%esp)
 80494a6:	8b b4 24 88 a0 00 00 	mov    0xa088(%esp),%esi
 80494ad:	8b 84 24 8c a0 00 00 	mov    0xa08c(%esp),%eax
 80494b4:	89 44 24 18          	mov    %eax,0x18(%esp)
 80494b8:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 80494be:	89 84 24 50 a0 00 00 	mov    %eax,0xa050(%esp)
 80494c5:	31 c0                	xor    %eax,%eax
 80494c7:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%esp)
 80494ce:	00 
 80494cf:	6a 00                	push   $0x0
 80494d1:	6a 01                	push   $0x1
 80494d3:	6a 02                	push   $0x2
 80494d5:	e8 76 f3 ff ff       	call   8048850 <socket@plt>
 80494da:	83 c4 10             	add    $0x10,%esp
 80494dd:	85 c0                	test   %eax,%eax
 80494df:	0f 88 04 01 00 00    	js     80495e9 <submitr+0x175>
 80494e5:	89 c5                	mov    %eax,%ebp
 80494e7:	83 ec 0c             	sub    $0xc,%esp
 80494ea:	53                   	push   %ebx
 80494eb:	e8 80 f3 ff ff       	call   8048870 <gethostbyname@plt>
 80494f0:	83 c4 10             	add    $0x10,%esp
 80494f3:	85 c0                	test   %eax,%eax
 80494f5:	0f 84 40 01 00 00    	je     804963b <submitr+0x1c7>
 80494fb:	8d 5c 24 30          	lea    0x30(%esp),%ebx
 80494ff:	c7 44 24 30 00 00 00 	movl   $0x0,0x30(%esp)
 8049506:	00 
 8049507:	c7 44 24 34 00 00 00 	movl   $0x0,0x34(%esp)
 804950e:	00 
 804950f:	c7 44 24 38 00 00 00 	movl   $0x0,0x38(%esp)
 8049516:	00 
 8049517:	c7 44 24 3c 00 00 00 	movl   $0x0,0x3c(%esp)
 804951e:	00 
 804951f:	66 c7 44 24 30 02 00 	movw   $0x2,0x30(%esp)
 8049526:	6a 0c                	push   $0xc
 8049528:	ff 70 0c             	pushl  0xc(%eax)
 804952b:	8b 40 10             	mov    0x10(%eax),%eax
 804952e:	ff 30                	pushl  (%eax)
 8049530:	8d 44 24 40          	lea    0x40(%esp),%eax
 8049534:	50                   	push   %eax
 8049535:	e8 96 f2 ff ff       	call   80487d0 <__memmove_chk@plt>
 804953a:	0f b7 84 24 84 a0 00 	movzwl 0xa084(%esp),%eax
 8049541:	00 
 8049542:	66 c1 c8 08          	ror    $0x8,%ax
 8049546:	66 89 44 24 42       	mov    %ax,0x42(%esp)
 804954b:	83 c4 0c             	add    $0xc,%esp
 804954e:	6a 10                	push   $0x10
 8049550:	53                   	push   %ebx
 8049551:	55                   	push   %ebp
 8049552:	e8 39 f3 ff ff       	call   8048890 <connect@plt>
 8049557:	83 c4 10             	add    $0x10,%esp
 804955a:	85 c0                	test   %eax,%eax
 804955c:	0f 88 49 01 00 00    	js     80496ab <submitr+0x237>
 8049562:	ba ff ff ff ff       	mov    $0xffffffff,%edx
 8049567:	b8 00 00 00 00       	mov    $0x0,%eax
 804956c:	89 d1                	mov    %edx,%ecx
 804956e:	89 f7                	mov    %esi,%edi
 8049570:	f2 ae                	repnz scas %es:(%edi),%al
 8049572:	89 cb                	mov    %ecx,%ebx
 8049574:	f7 d3                	not    %ebx
 8049576:	89 d1                	mov    %edx,%ecx
 8049578:	8b 7c 24 08          	mov    0x8(%esp),%edi
 804957c:	f2 ae                	repnz scas %es:(%edi),%al
 804957e:	89 4c 24 18          	mov    %ecx,0x18(%esp)
 8049582:	89 d1                	mov    %edx,%ecx
 8049584:	8b 7c 24 0c          	mov    0xc(%esp),%edi
 8049588:	f2 ae                	repnz scas %es:(%edi),%al
 804958a:	89 cf                	mov    %ecx,%edi
 804958c:	f7 d7                	not    %edi
 804958e:	89 7c 24 1c          	mov    %edi,0x1c(%esp)
 8049592:	89 d1                	mov    %edx,%ecx
 8049594:	8b 7c 24 10          	mov    0x10(%esp),%edi
 8049598:	f2 ae                	repnz scas %es:(%edi),%al
 804959a:	8b 54 24 1c          	mov    0x1c(%esp),%edx
 804959e:	2b 54 24 18          	sub    0x18(%esp),%edx
 80495a2:	29 ca                	sub    %ecx,%edx
 80495a4:	8d 44 5b fd          	lea    -0x3(%ebx,%ebx,2),%eax
 80495a8:	8d 44 02 7b          	lea    0x7b(%edx,%eax,1),%eax
 80495ac:	3d 00 20 00 00       	cmp    $0x2000,%eax
 80495b1:	0f 87 56 01 00 00    	ja     804970d <submitr+0x299>
 80495b7:	8d 94 24 4c 40 00 00 	lea    0x404c(%esp),%edx
 80495be:	b9 00 08 00 00       	mov    $0x800,%ecx
 80495c3:	b8 00 00 00 00       	mov    $0x0,%eax
 80495c8:	89 d7                	mov    %edx,%edi
 80495ca:	f3 ab                	rep stos %eax,%es:(%edi)
 80495cc:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 80495d1:	89 f7                	mov    %esi,%edi
 80495d3:	f2 ae                	repnz scas %es:(%edi),%al
 80495d5:	f7 d1                	not    %ecx
 80495d7:	89 cb                	mov    %ecx,%ebx
 80495d9:	83 eb 01             	sub    $0x1,%ebx
 80495dc:	0f 84 07 06 00 00    	je     8049be9 <submitr+0x775>
 80495e2:	89 d7                	mov    %edx,%edi
 80495e4:	e9 b0 01 00 00       	jmp    8049799 <submitr+0x325>
 80495e9:	8b 44 24 14          	mov    0x14(%esp),%eax
 80495ed:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80495f3:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 80495fa:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049601:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049608:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 804960f:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049616:	c7 40 18 63 72 65 61 	movl   $0x61657263,0x18(%eax)
 804961d:	c7 40 1c 74 65 20 73 	movl   $0x73206574,0x1c(%eax)
 8049624:	c7 40 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%eax)
 804962b:	66 c7 40 24 74 00    	movw   $0x74,0x24(%eax)
 8049631:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049636:	e9 d0 04 00 00       	jmp    8049b0b <submitr+0x697>
 804963b:	8b 44 24 14          	mov    0x14(%esp),%eax
 804963f:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049645:	c7 40 04 72 3a 20 44 	movl   $0x44203a72,0x4(%eax)
 804964c:	c7 40 08 4e 53 20 69 	movl   $0x6920534e,0x8(%eax)
 8049653:	c7 40 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%eax)
 804965a:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049661:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049668:	c7 40 18 72 65 73 6f 	movl   $0x6f736572,0x18(%eax)
 804966f:	c7 40 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%eax)
 8049676:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 804967d:	c7 40 24 65 72 20 61 	movl   $0x61207265,0x24(%eax)
 8049684:	c7 40 28 64 64 72 65 	movl   $0x65726464,0x28(%eax)
 804968b:	66 c7 40 2c 73 73    	movw   $0x7373,0x2c(%eax)
 8049691:	c6 40 2e 00          	movb   $0x0,0x2e(%eax)
 8049695:	83 ec 0c             	sub    $0xc,%esp
 8049698:	55                   	push   %ebp
 8049699:	e8 02 f2 ff ff       	call   80488a0 <close@plt>
 804969e:	83 c4 10             	add    $0x10,%esp
 80496a1:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80496a6:	e9 60 04 00 00       	jmp    8049b0b <submitr+0x697>
 80496ab:	8b 44 24 14          	mov    0x14(%esp),%eax
 80496af:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80496b5:	c7 40 04 72 3a 20 55 	movl   $0x55203a72,0x4(%eax)
 80496bc:	c7 40 08 6e 61 62 6c 	movl   $0x6c62616e,0x8(%eax)
 80496c3:	c7 40 0c 65 20 74 6f 	movl   $0x6f742065,0xc(%eax)
 80496ca:	c7 40 10 20 63 6f 6e 	movl   $0x6e6f6320,0x10(%eax)
 80496d1:	c7 40 14 6e 65 63 74 	movl   $0x7463656e,0x14(%eax)
 80496d8:	c7 40 18 20 74 6f 20 	movl   $0x206f7420,0x18(%eax)
 80496df:	c7 40 1c 74 68 65 20 	movl   $0x20656874,0x1c(%eax)
 80496e6:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 80496ed:	66 c7 40 24 65 72    	movw   $0x7265,0x24(%eax)
 80496f3:	c6 40 26 00          	movb   $0x0,0x26(%eax)
 80496f7:	83 ec 0c             	sub    $0xc,%esp
 80496fa:	55                   	push   %ebp
 80496fb:	e8 a0 f1 ff ff       	call   80488a0 <close@plt>
 8049700:	83 c4 10             	add    $0x10,%esp
 8049703:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049708:	e9 fe 03 00 00       	jmp    8049b0b <submitr+0x697>
 804970d:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049711:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049717:	c7 40 04 72 3a 20 52 	movl   $0x52203a72,0x4(%eax)
 804971e:	c7 40 08 65 73 75 6c 	movl   $0x6c757365,0x8(%eax)
 8049725:	c7 40 0c 74 20 73 74 	movl   $0x74732074,0xc(%eax)
 804972c:	c7 40 10 72 69 6e 67 	movl   $0x676e6972,0x10(%eax)
 8049733:	c7 40 14 20 74 6f 6f 	movl   $0x6f6f7420,0x14(%eax)
 804973a:	c7 40 18 20 6c 61 72 	movl   $0x72616c20,0x18(%eax)
 8049741:	c7 40 1c 67 65 2e 20 	movl   $0x202e6567,0x1c(%eax)
 8049748:	c7 40 20 49 6e 63 72 	movl   $0x72636e49,0x20(%eax)
 804974f:	c7 40 24 65 61 73 65 	movl   $0x65736165,0x24(%eax)
 8049756:	c7 40 28 20 53 55 42 	movl   $0x42555320,0x28(%eax)
 804975d:	c7 40 2c 4d 49 54 52 	movl   $0x5254494d,0x2c(%eax)
 8049764:	c7 40 30 5f 4d 41 58 	movl   $0x58414d5f,0x30(%eax)
 804976b:	c7 40 34 42 55 46 00 	movl   $0x465542,0x34(%eax)
 8049772:	83 ec 0c             	sub    $0xc,%esp
 8049775:	55                   	push   %ebp
 8049776:	e8 25 f1 ff ff       	call   80488a0 <close@plt>
 804977b:	83 c4 10             	add    $0x10,%esp
 804977e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049783:	e9 83 03 00 00       	jmp    8049b0b <submitr+0x697>
 8049788:	88 17                	mov    %dl,(%edi)
 804978a:	8d 7f 01             	lea    0x1(%edi),%edi
 804978d:	83 c6 01             	add    $0x1,%esi
 8049790:	83 eb 01             	sub    $0x1,%ebx
 8049793:	0f 84 50 04 00 00    	je     8049be9 <submitr+0x775>
 8049799:	0f b6 16             	movzbl (%esi),%edx
 804979c:	8d 4a d6             	lea    -0x2a(%edx),%ecx
 804979f:	b8 01 00 00 00       	mov    $0x1,%eax
 80497a4:	80 f9 0f             	cmp    $0xf,%cl
 80497a7:	77 0d                	ja     80497b6 <submitr+0x342>
 80497a9:	b8 d9 ff 00 00       	mov    $0xffd9,%eax
 80497ae:	d3 e8                	shr    %cl,%eax
 80497b0:	83 f0 01             	xor    $0x1,%eax
 80497b3:	83 e0 01             	and    $0x1,%eax
 80497b6:	80 fa 5f             	cmp    $0x5f,%dl
 80497b9:	74 cd                	je     8049788 <submitr+0x314>
 80497bb:	84 c0                	test   %al,%al
 80497bd:	74 c9                	je     8049788 <submitr+0x314>
 80497bf:	89 d0                	mov    %edx,%eax
 80497c1:	83 e0 df             	and    $0xffffffdf,%eax
 80497c4:	83 e8 41             	sub    $0x41,%eax
 80497c7:	3c 19                	cmp    $0x19,%al
 80497c9:	76 bd                	jbe    8049788 <submitr+0x314>
 80497cb:	80 fa 20             	cmp    $0x20,%dl
 80497ce:	74 58                	je     8049828 <submitr+0x3b4>
 80497d0:	8d 42 e0             	lea    -0x20(%edx),%eax
 80497d3:	3c 5f                	cmp    $0x5f,%al
 80497d5:	76 09                	jbe    80497e0 <submitr+0x36c>
 80497d7:	80 fa 09             	cmp    $0x9,%dl
 80497da:	0f 85 c5 03 00 00    	jne    8049ba5 <submitr+0x731>
 80497e0:	83 ec 0c             	sub    $0xc,%esp
 80497e3:	0f b6 d2             	movzbl %dl,%edx
 80497e6:	52                   	push   %edx
 80497e7:	68 14 a4 04 08       	push   $0x804a414
 80497ec:	6a 08                	push   $0x8
 80497ee:	6a 01                	push   $0x1
 80497f0:	8d 84 24 68 80 00 00 	lea    0x8068(%esp),%eax
 80497f7:	50                   	push   %eax
 80497f8:	e8 c3 f0 ff ff       	call   80488c0 <__sprintf_chk@plt>
 80497fd:	0f b6 84 24 6c 80 00 	movzbl 0x806c(%esp),%eax
 8049804:	00 
 8049805:	88 07                	mov    %al,(%edi)
 8049807:	0f b6 84 24 6d 80 00 	movzbl 0x806d(%esp),%eax
 804980e:	00 
 804980f:	88 47 01             	mov    %al,0x1(%edi)
 8049812:	0f b6 84 24 6e 80 00 	movzbl 0x806e(%esp),%eax
 8049819:	00 
 804981a:	88 47 02             	mov    %al,0x2(%edi)
 804981d:	83 c4 20             	add    $0x20,%esp
 8049820:	8d 7f 03             	lea    0x3(%edi),%edi
 8049823:	e9 65 ff ff ff       	jmp    804978d <submitr+0x319>
 8049828:	c6 07 2b             	movb   $0x2b,(%edi)
 804982b:	8d 7f 01             	lea    0x1(%edi),%edi
 804982e:	e9 5a ff ff ff       	jmp    804978d <submitr+0x319>
 8049833:	01 c6                	add    %eax,%esi
 8049835:	29 c3                	sub    %eax,%ebx
 8049837:	74 24                	je     804985d <submitr+0x3e9>
 8049839:	83 ec 04             	sub    $0x4,%esp
 804983c:	53                   	push   %ebx
 804983d:	56                   	push   %esi
 804983e:	55                   	push   %ebp
 804983f:	e8 bc ef ff ff       	call   8048800 <write@plt>
 8049844:	83 c4 10             	add    $0x10,%esp
 8049847:	85 c0                	test   %eax,%eax
 8049849:	7f e8                	jg     8049833 <submitr+0x3bf>
 804984b:	e8 e0 ef ff ff       	call   8048830 <__errno_location@plt>
 8049850:	83 38 04             	cmpl   $0x4,(%eax)
 8049853:	0f 85 b0 00 00 00    	jne    8049909 <submitr+0x495>
 8049859:	89 f8                	mov    %edi,%eax
 804985b:	eb d6                	jmp    8049833 <submitr+0x3bf>
 804985d:	83 7c 24 08 00       	cmpl   $0x0,0x8(%esp)
 8049862:	0f 88 a1 00 00 00    	js     8049909 <submitr+0x495>
 8049868:	89 6c 24 40          	mov    %ebp,0x40(%esp)
 804986c:	c7 44 24 44 00 00 00 	movl   $0x0,0x44(%esp)
 8049873:	00 
 8049874:	8d 44 24 4c          	lea    0x4c(%esp),%eax
 8049878:	89 44 24 48          	mov    %eax,0x48(%esp)
 804987c:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049881:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049888:	8d 44 24 40          	lea    0x40(%esp),%eax
 804988c:	e8 32 fb ff ff       	call   80493c3 <rio_readlineb>
 8049891:	85 c0                	test   %eax,%eax
 8049893:	0f 8e d6 00 00 00    	jle    804996f <submitr+0x4fb>
 8049899:	83 ec 0c             	sub    $0xc,%esp
 804989c:	8d 84 24 58 80 00 00 	lea    0x8058(%esp),%eax
 80498a3:	50                   	push   %eax
 80498a4:	8d 44 24 3c          	lea    0x3c(%esp),%eax
 80498a8:	50                   	push   %eax
 80498a9:	8d 84 24 60 60 00 00 	lea    0x6060(%esp),%eax
 80498b0:	50                   	push   %eax
 80498b1:	68 1b a4 04 08       	push   $0x804a41b
 80498b6:	8d 84 24 68 20 00 00 	lea    0x2068(%esp),%eax
 80498bd:	50                   	push   %eax
 80498be:	e8 4d ef ff ff       	call   8048810 <__isoc99_sscanf@plt>
 80498c3:	8b 44 24 4c          	mov    0x4c(%esp),%eax
 80498c7:	83 c4 20             	add    $0x20,%esp
 80498ca:	3d c8 00 00 00       	cmp    $0xc8,%eax
 80498cf:	0f 84 a6 01 00 00    	je     8049a7b <submitr+0x607>
 80498d5:	83 ec 08             	sub    $0x8,%esp
 80498d8:	8d 94 24 54 80 00 00 	lea    0x8054(%esp),%edx
 80498df:	52                   	push   %edx
 80498e0:	50                   	push   %eax
 80498e1:	68 2c a3 04 08       	push   $0x804a32c
 80498e6:	6a ff                	push   $0xffffffff
 80498e8:	6a 01                	push   $0x1
 80498ea:	ff 74 24 30          	pushl  0x30(%esp)
 80498ee:	e8 cd ef ff ff       	call   80488c0 <__sprintf_chk@plt>
 80498f3:	83 c4 14             	add    $0x14,%esp
 80498f6:	55                   	push   %ebp
 80498f7:	e8 a4 ef ff ff       	call   80488a0 <close@plt>
 80498fc:	83 c4 10             	add    $0x10,%esp
 80498ff:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049904:	e9 02 02 00 00       	jmp    8049b0b <submitr+0x697>
 8049909:	8b 44 24 14          	mov    0x14(%esp),%eax
 804990d:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049913:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 804991a:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049921:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049928:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 804992f:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049936:	c7 40 18 77 72 69 74 	movl   $0x74697277,0x18(%eax)
 804993d:	c7 40 1c 65 20 74 6f 	movl   $0x6f742065,0x1c(%eax)
 8049944:	c7 40 20 20 74 68 65 	movl   $0x65687420,0x20(%eax)
 804994b:	c7 40 24 20 73 65 72 	movl   $0x72657320,0x24(%eax)
 8049952:	c7 40 28 76 65 72 00 	movl   $0x726576,0x28(%eax)
 8049959:	83 ec 0c             	sub    $0xc,%esp
 804995c:	55                   	push   %ebp
 804995d:	e8 3e ef ff ff       	call   80488a0 <close@plt>
 8049962:	83 c4 10             	add    $0x10,%esp
 8049965:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804996a:	e9 9c 01 00 00       	jmp    8049b0b <submitr+0x697>
 804996f:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049973:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049979:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049980:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049987:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 804998e:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049995:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 804999c:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 80499a3:	c7 40 1c 20 66 69 72 	movl   $0x72696620,0x1c(%eax)
 80499aa:	c7 40 20 73 74 20 68 	movl   $0x68207473,0x20(%eax)
 80499b1:	c7 40 24 65 61 64 65 	movl   $0x65646165,0x24(%eax)
 80499b8:	c7 40 28 72 20 66 72 	movl   $0x72662072,0x28(%eax)
 80499bf:	c7 40 2c 6f 6d 20 73 	movl   $0x73206d6f,0x2c(%eax)
 80499c6:	c7 40 30 65 72 76 65 	movl   $0x65767265,0x30(%eax)
 80499cd:	66 c7 40 34 72 00    	movw   $0x72,0x34(%eax)
 80499d3:	83 ec 0c             	sub    $0xc,%esp
 80499d6:	55                   	push   %ebp
 80499d7:	e8 c4 ee ff ff       	call   80488a0 <close@plt>
 80499dc:	83 c4 10             	add    $0x10,%esp
 80499df:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80499e4:	e9 22 01 00 00       	jmp    8049b0b <submitr+0x697>
 80499e9:	8b 44 24 14          	mov    0x14(%esp),%eax
 80499ed:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80499f3:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 80499fa:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049a01:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049a08:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049a0f:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049a16:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049a1d:	c7 40 1c 20 68 65 61 	movl   $0x61656820,0x1c(%eax)
 8049a24:	c7 40 20 64 65 72 73 	movl   $0x73726564,0x20(%eax)
 8049a2b:	c7 40 24 20 66 72 6f 	movl   $0x6f726620,0x24(%eax)
 8049a32:	c7 40 28 6d 20 73 65 	movl   $0x6573206d,0x28(%eax)
 8049a39:	c7 40 2c 72 76 65 72 	movl   $0x72657672,0x2c(%eax)
 8049a40:	c6 40 30 00          	movb   $0x0,0x30(%eax)
 8049a44:	83 ec 0c             	sub    $0xc,%esp
 8049a47:	55                   	push   %ebp
 8049a48:	e8 53 ee ff ff       	call   80488a0 <close@plt>
 8049a4d:	83 c4 10             	add    $0x10,%esp
 8049a50:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049a55:	e9 b1 00 00 00       	jmp    8049b0b <submitr+0x697>
 8049a5a:	85 c0                	test   %eax,%eax
 8049a5c:	74 4b                	je     8049aa9 <submitr+0x635>
 8049a5e:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049a63:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049a6a:	8d 44 24 40          	lea    0x40(%esp),%eax
 8049a6e:	e8 50 f9 ff ff       	call   80493c3 <rio_readlineb>
 8049a73:	85 c0                	test   %eax,%eax
 8049a75:	0f 8e 6e ff ff ff    	jle    80499e9 <submitr+0x575>
 8049a7b:	0f b6 94 24 4c 20 00 	movzbl 0x204c(%esp),%edx
 8049a82:	00 
 8049a83:	b8 0d 00 00 00       	mov    $0xd,%eax
 8049a88:	29 d0                	sub    %edx,%eax
 8049a8a:	75 ce                	jne    8049a5a <submitr+0x5e6>
 8049a8c:	0f b6 94 24 4d 20 00 	movzbl 0x204d(%esp),%edx
 8049a93:	00 
 8049a94:	b8 0a 00 00 00       	mov    $0xa,%eax
 8049a99:	29 d0                	sub    %edx,%eax
 8049a9b:	75 bd                	jne    8049a5a <submitr+0x5e6>
 8049a9d:	0f b6 84 24 4e 20 00 	movzbl 0x204e(%esp),%eax
 8049aa4:	00 
 8049aa5:	f7 d8                	neg    %eax
 8049aa7:	eb b1                	jmp    8049a5a <submitr+0x5e6>
 8049aa9:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049aae:	8d 94 24 4c 20 00 00 	lea    0x204c(%esp),%edx
 8049ab5:	8d 44 24 40          	lea    0x40(%esp),%eax
 8049ab9:	e8 05 f9 ff ff       	call   80493c3 <rio_readlineb>
 8049abe:	85 c0                	test   %eax,%eax
 8049ac0:	7e 68                	jle    8049b2a <submitr+0x6b6>
 8049ac2:	83 ec 08             	sub    $0x8,%esp
 8049ac5:	8d 84 24 54 20 00 00 	lea    0x2054(%esp),%eax
 8049acc:	50                   	push   %eax
 8049acd:	8b 7c 24 20          	mov    0x20(%esp),%edi
 8049ad1:	57                   	push   %edi
 8049ad2:	e8 c9 ec ff ff       	call   80487a0 <strcpy@plt>
 8049ad7:	89 2c 24             	mov    %ebp,(%esp)
 8049ada:	e8 c1 ed ff ff       	call   80488a0 <close@plt>
 8049adf:	0f b6 17             	movzbl (%edi),%edx
 8049ae2:	b8 4f 00 00 00       	mov    $0x4f,%eax
 8049ae7:	83 c4 10             	add    $0x10,%esp
 8049aea:	29 d0                	sub    %edx,%eax
 8049aec:	75 13                	jne    8049b01 <submitr+0x68d>
 8049aee:	0f b6 57 01          	movzbl 0x1(%edi),%edx
 8049af2:	b8 4b 00 00 00       	mov    $0x4b,%eax
 8049af7:	29 d0                	sub    %edx,%eax
 8049af9:	75 06                	jne    8049b01 <submitr+0x68d>
 8049afb:	0f b6 47 02          	movzbl 0x2(%edi),%eax
 8049aff:	f7 d8                	neg    %eax
 8049b01:	85 c0                	test   %eax,%eax
 8049b03:	0f 95 c0             	setne  %al
 8049b06:	0f b6 c0             	movzbl %al,%eax
 8049b09:	f7 d8                	neg    %eax
 8049b0b:	8b bc 24 4c a0 00 00 	mov    0xa04c(%esp),%edi
 8049b12:	65 33 3d 14 00 00 00 	xor    %gs:0x14,%edi
 8049b19:	0f 85 2a 01 00 00    	jne    8049c49 <submitr+0x7d5>
 8049b1f:	81 c4 5c a0 00 00    	add    $0xa05c,%esp
 8049b25:	5b                   	pop    %ebx
 8049b26:	5e                   	pop    %esi
 8049b27:	5f                   	pop    %edi
 8049b28:	5d                   	pop    %ebp
 8049b29:	c3                   	ret    
 8049b2a:	8b 44 24 14          	mov    0x14(%esp),%eax
 8049b2e:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049b34:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049b3b:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049b42:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049b49:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049b50:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049b57:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049b5e:	c7 40 1c 20 73 74 61 	movl   $0x61747320,0x1c(%eax)
 8049b65:	c7 40 20 74 75 73 20 	movl   $0x20737574,0x20(%eax)
 8049b6c:	c7 40 24 6d 65 73 73 	movl   $0x7373656d,0x24(%eax)
 8049b73:	c7 40 28 61 67 65 20 	movl   $0x20656761,0x28(%eax)
 8049b7a:	c7 40 2c 66 72 6f 6d 	movl   $0x6d6f7266,0x2c(%eax)
 8049b81:	c7 40 30 20 73 65 72 	movl   $0x72657320,0x30(%eax)
 8049b88:	c7 40 34 76 65 72 00 	movl   $0x726576,0x34(%eax)
 8049b8f:	83 ec 0c             	sub    $0xc,%esp
 8049b92:	55                   	push   %ebp
 8049b93:	e8 08 ed ff ff       	call   80488a0 <close@plt>
 8049b98:	83 c4 10             	add    $0x10,%esp
 8049b9b:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049ba0:	e9 66 ff ff ff       	jmp    8049b0b <submitr+0x697>
 8049ba5:	a1 5c a3 04 08       	mov    0x804a35c,%eax
 8049baa:	8b 5c 24 14          	mov    0x14(%esp),%ebx
 8049bae:	89 03                	mov    %eax,(%ebx)
 8049bb0:	a1 9b a3 04 08       	mov    0x804a39b,%eax
 8049bb5:	89 43 3f             	mov    %eax,0x3f(%ebx)
 8049bb8:	8d 7b 04             	lea    0x4(%ebx),%edi
 8049bbb:	83 e7 fc             	and    $0xfffffffc,%edi
 8049bbe:	29 fb                	sub    %edi,%ebx
 8049bc0:	89 d8                	mov    %ebx,%eax
 8049bc2:	be 5c a3 04 08       	mov    $0x804a35c,%esi
 8049bc7:	29 de                	sub    %ebx,%esi
 8049bc9:	83 c0 43             	add    $0x43,%eax
 8049bcc:	c1 e8 02             	shr    $0x2,%eax
 8049bcf:	89 c1                	mov    %eax,%ecx
 8049bd1:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049bd3:	83 ec 0c             	sub    $0xc,%esp
 8049bd6:	55                   	push   %ebp
 8049bd7:	e8 c4 ec ff ff       	call   80488a0 <close@plt>
 8049bdc:	83 c4 10             	add    $0x10,%esp
 8049bdf:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049be4:	e9 22 ff ff ff       	jmp    8049b0b <submitr+0x697>
 8049be9:	8d 84 24 4c 40 00 00 	lea    0x404c(%esp),%eax
 8049bf0:	50                   	push   %eax
 8049bf1:	ff 74 24 14          	pushl  0x14(%esp)
 8049bf5:	ff 74 24 14          	pushl  0x14(%esp)
 8049bf9:	ff 74 24 14          	pushl  0x14(%esp)
 8049bfd:	68 a0 a3 04 08       	push   $0x804a3a0
 8049c02:	68 00 20 00 00       	push   $0x2000
 8049c07:	6a 01                	push   $0x1
 8049c09:	8d bc 24 68 20 00 00 	lea    0x2068(%esp),%edi
 8049c10:	57                   	push   %edi
 8049c11:	e8 aa ec ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049c16:	b8 00 00 00 00       	mov    $0x0,%eax
 8049c1b:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049c20:	f2 ae                	repnz scas %es:(%edi),%al
 8049c22:	f7 d1                	not    %ecx
 8049c24:	8d 41 ff             	lea    -0x1(%ecx),%eax
 8049c27:	89 44 24 28          	mov    %eax,0x28(%esp)
 8049c2b:	83 c4 20             	add    $0x20,%esp
 8049c2e:	89 c3                	mov    %eax,%ebx
 8049c30:	8d b4 24 4c 20 00 00 	lea    0x204c(%esp),%esi
 8049c37:	bf 00 00 00 00       	mov    $0x0,%edi
 8049c3c:	85 c0                	test   %eax,%eax
 8049c3e:	0f 85 f5 fb ff ff    	jne    8049839 <submitr+0x3c5>
 8049c44:	e9 1f fc ff ff       	jmp    8049868 <submitr+0x3f4>
 8049c49:	e8 42 eb ff ff       	call   8048790 <__stack_chk_fail@plt>

08049c4e <init_timeout>:
 8049c4e:	53                   	push   %ebx
 8049c4f:	83 ec 08             	sub    $0x8,%esp
 8049c52:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8049c56:	85 db                	test   %ebx,%ebx
 8049c58:	74 24                	je     8049c7e <init_timeout+0x30>
 8049c5a:	83 ec 08             	sub    $0x8,%esp
 8049c5d:	68 a0 93 04 08       	push   $0x80493a0
 8049c62:	6a 0e                	push   $0xe
 8049c64:	e8 f7 ea ff ff       	call   8048760 <signal@plt>
 8049c69:	85 db                	test   %ebx,%ebx
 8049c6b:	b8 00 00 00 00       	mov    $0x0,%eax
 8049c70:	0f 48 d8             	cmovs  %eax,%ebx
 8049c73:	89 1c 24             	mov    %ebx,(%esp)
 8049c76:	e8 05 eb ff ff       	call   8048780 <alarm@plt>
 8049c7b:	83 c4 10             	add    $0x10,%esp
 8049c7e:	83 c4 08             	add    $0x8,%esp
 8049c81:	5b                   	pop    %ebx
 8049c82:	c3                   	ret    

08049c83 <init_driver>:
 8049c83:	57                   	push   %edi
 8049c84:	56                   	push   %esi
 8049c85:	53                   	push   %ebx
 8049c86:	83 ec 28             	sub    $0x28,%esp
 8049c89:	8b 74 24 38          	mov    0x38(%esp),%esi
 8049c8d:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 8049c93:	89 44 24 24          	mov    %eax,0x24(%esp)
 8049c97:	31 c0                	xor    %eax,%eax
 8049c99:	6a 01                	push   $0x1
 8049c9b:	6a 0d                	push   $0xd
 8049c9d:	e8 be ea ff ff       	call   8048760 <signal@plt>
 8049ca2:	83 c4 08             	add    $0x8,%esp
 8049ca5:	6a 01                	push   $0x1
 8049ca7:	6a 1d                	push   $0x1d
 8049ca9:	e8 b2 ea ff ff       	call   8048760 <signal@plt>
 8049cae:	83 c4 08             	add    $0x8,%esp
 8049cb1:	6a 01                	push   $0x1
 8049cb3:	6a 1d                	push   $0x1d
 8049cb5:	e8 a6 ea ff ff       	call   8048760 <signal@plt>
 8049cba:	83 c4 0c             	add    $0xc,%esp
 8049cbd:	6a 00                	push   $0x0
 8049cbf:	6a 01                	push   $0x1
 8049cc1:	6a 02                	push   $0x2
 8049cc3:	e8 88 eb ff ff       	call   8048850 <socket@plt>
 8049cc8:	83 c4 10             	add    $0x10,%esp
 8049ccb:	85 c0                	test   %eax,%eax
 8049ccd:	0f 88 a9 00 00 00    	js     8049d7c <init_driver+0xf9>
 8049cd3:	89 c3                	mov    %eax,%ebx
 8049cd5:	83 ec 0c             	sub    $0xc,%esp
 8049cd8:	68 2c a4 04 08       	push   $0x804a42c
 8049cdd:	e8 8e eb ff ff       	call   8048870 <gethostbyname@plt>
 8049ce2:	83 c4 10             	add    $0x10,%esp
 8049ce5:	85 c0                	test   %eax,%eax
 8049ce7:	0f 84 da 00 00 00    	je     8049dc7 <init_driver+0x144>
 8049ced:	8d 7c 24 0c          	lea    0xc(%esp),%edi
 8049cf1:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
 8049cf8:	00 
 8049cf9:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 8049d00:	00 
 8049d01:	c7 44 24 14 00 00 00 	movl   $0x0,0x14(%esp)
 8049d08:	00 
 8049d09:	c7 44 24 18 00 00 00 	movl   $0x0,0x18(%esp)
 8049d10:	00 
 8049d11:	66 c7 44 24 0c 02 00 	movw   $0x2,0xc(%esp)
 8049d18:	6a 0c                	push   $0xc
 8049d1a:	ff 70 0c             	pushl  0xc(%eax)
 8049d1d:	8b 40 10             	mov    0x10(%eax),%eax
 8049d20:	ff 30                	pushl  (%eax)
 8049d22:	8d 44 24 1c          	lea    0x1c(%esp),%eax
 8049d26:	50                   	push   %eax
 8049d27:	e8 a4 ea ff ff       	call   80487d0 <__memmove_chk@plt>
 8049d2c:	66 c7 44 24 1e 3b 6e 	movw   $0x6e3b,0x1e(%esp)
 8049d33:	83 c4 0c             	add    $0xc,%esp
 8049d36:	6a 10                	push   $0x10
 8049d38:	57                   	push   %edi
 8049d39:	53                   	push   %ebx
 8049d3a:	e8 51 eb ff ff       	call   8048890 <connect@plt>
 8049d3f:	83 c4 10             	add    $0x10,%esp
 8049d42:	85 c0                	test   %eax,%eax
 8049d44:	0f 88 e9 00 00 00    	js     8049e33 <init_driver+0x1b0>
 8049d4a:	83 ec 0c             	sub    $0xc,%esp
 8049d4d:	53                   	push   %ebx
 8049d4e:	e8 4d eb ff ff       	call   80488a0 <close@plt>
 8049d53:	66 c7 06 4f 4b       	movw   $0x4b4f,(%esi)
 8049d58:	c6 46 02 00          	movb   $0x0,0x2(%esi)
 8049d5c:	83 c4 10             	add    $0x10,%esp
 8049d5f:	b8 00 00 00 00       	mov    $0x0,%eax
 8049d64:	8b 54 24 1c          	mov    0x1c(%esp),%edx
 8049d68:	65 33 15 14 00 00 00 	xor    %gs:0x14,%edx
 8049d6f:	0f 85 eb 00 00 00    	jne    8049e60 <init_driver+0x1dd>
 8049d75:	83 c4 20             	add    $0x20,%esp
 8049d78:	5b                   	pop    %ebx
 8049d79:	5e                   	pop    %esi
 8049d7a:	5f                   	pop    %edi
 8049d7b:	c3                   	ret    
 8049d7c:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049d82:	c7 46 04 72 3a 20 43 	movl   $0x43203a72,0x4(%esi)
 8049d89:	c7 46 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%esi)
 8049d90:	c7 46 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%esi)
 8049d97:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049d9e:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049da5:	c7 46 18 63 72 65 61 	movl   $0x61657263,0x18(%esi)
 8049dac:	c7 46 1c 74 65 20 73 	movl   $0x73206574,0x1c(%esi)
 8049db3:	c7 46 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%esi)
 8049dba:	66 c7 46 24 74 00    	movw   $0x74,0x24(%esi)
 8049dc0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049dc5:	eb 9d                	jmp    8049d64 <init_driver+0xe1>
 8049dc7:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049dcd:	c7 46 04 72 3a 20 44 	movl   $0x44203a72,0x4(%esi)
 8049dd4:	c7 46 08 4e 53 20 69 	movl   $0x6920534e,0x8(%esi)
 8049ddb:	c7 46 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%esi)
 8049de2:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049de9:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049df0:	c7 46 18 72 65 73 6f 	movl   $0x6f736572,0x18(%esi)
 8049df7:	c7 46 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%esi)
 8049dfe:	c7 46 20 73 65 72 76 	movl   $0x76726573,0x20(%esi)
 8049e05:	c7 46 24 65 72 20 61 	movl   $0x61207265,0x24(%esi)
 8049e0c:	c7 46 28 64 64 72 65 	movl   $0x65726464,0x28(%esi)
 8049e13:	66 c7 46 2c 73 73    	movw   $0x7373,0x2c(%esi)
 8049e19:	c6 46 2e 00          	movb   $0x0,0x2e(%esi)
 8049e1d:	83 ec 0c             	sub    $0xc,%esp
 8049e20:	53                   	push   %ebx
 8049e21:	e8 7a ea ff ff       	call   80488a0 <close@plt>
 8049e26:	83 c4 10             	add    $0x10,%esp
 8049e29:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049e2e:	e9 31 ff ff ff       	jmp    8049d64 <init_driver+0xe1>
 8049e33:	83 ec 0c             	sub    $0xc,%esp
 8049e36:	68 2c a4 04 08       	push   $0x804a42c
 8049e3b:	68 ec a3 04 08       	push   $0x804a3ec
 8049e40:	6a ff                	push   $0xffffffff
 8049e42:	6a 01                	push   $0x1
 8049e44:	56                   	push   %esi
 8049e45:	e8 76 ea ff ff       	call   80488c0 <__sprintf_chk@plt>
 8049e4a:	83 c4 14             	add    $0x14,%esp
 8049e4d:	53                   	push   %ebx
 8049e4e:	e8 4d ea ff ff       	call   80488a0 <close@plt>
 8049e53:	83 c4 10             	add    $0x10,%esp
 8049e56:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049e5b:	e9 04 ff ff ff       	jmp    8049d64 <init_driver+0xe1>
 8049e60:	e8 2b e9 ff ff       	call   8048790 <__stack_chk_fail@plt>

08049e65 <driver_post>:
 8049e65:	53                   	push   %ebx
 8049e66:	83 ec 08             	sub    $0x8,%esp
 8049e69:	8b 54 24 10          	mov    0x10(%esp),%edx
 8049e6d:	8b 44 24 18          	mov    0x18(%esp),%eax
 8049e71:	8b 5c 24 1c          	mov    0x1c(%esp),%ebx
 8049e75:	85 c0                	test   %eax,%eax
 8049e77:	75 17                	jne    8049e90 <driver_post+0x2b>
 8049e79:	85 d2                	test   %edx,%edx
 8049e7b:	74 05                	je     8049e82 <driver_post+0x1d>
 8049e7d:	80 3a 00             	cmpb   $0x0,(%edx)
 8049e80:	75 34                	jne    8049eb6 <driver_post+0x51>
 8049e82:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049e87:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049e8b:	83 c4 08             	add    $0x8,%esp
 8049e8e:	5b                   	pop    %ebx
 8049e8f:	c3                   	ret    
 8049e90:	83 ec 04             	sub    $0x4,%esp
 8049e93:	ff 74 24 18          	pushl  0x18(%esp)
 8049e97:	68 3a a4 04 08       	push   $0x804a43a
 8049e9c:	6a 01                	push   $0x1
 8049e9e:	e8 9d e9 ff ff       	call   8048840 <__printf_chk@plt>
 8049ea3:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049ea8:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049eac:	83 c4 10             	add    $0x10,%esp
 8049eaf:	b8 00 00 00 00       	mov    $0x0,%eax
 8049eb4:	eb d5                	jmp    8049e8b <driver_post+0x26>
 8049eb6:	83 ec 04             	sub    $0x4,%esp
 8049eb9:	53                   	push   %ebx
 8049eba:	ff 74 24 1c          	pushl  0x1c(%esp)
 8049ebe:	68 51 a4 04 08       	push   $0x804a451
 8049ec3:	52                   	push   %edx
 8049ec4:	68 59 a4 04 08       	push   $0x804a459
 8049ec9:	68 6e 3b 00 00       	push   $0x3b6e
 8049ece:	68 2c a4 04 08       	push   $0x804a42c
 8049ed3:	e8 9c f5 ff ff       	call   8049474 <submitr>
 8049ed8:	83 c4 20             	add    $0x20,%esp
 8049edb:	eb ae                	jmp    8049e8b <driver_post+0x26>
 8049edd:	66 90                	xchg   %ax,%ax
 8049edf:	90                   	nop

08049ee0 <__libc_csu_init>:
 8049ee0:	55                   	push   %ebp
 8049ee1:	57                   	push   %edi
 8049ee2:	56                   	push   %esi
 8049ee3:	53                   	push   %ebx
 8049ee4:	e8 27 ea ff ff       	call   8048910 <__x86.get_pc_thunk.bx>
 8049ee9:	81 c3 17 21 00 00    	add    $0x2117,%ebx
 8049eef:	83 ec 0c             	sub    $0xc,%esp
 8049ef2:	8b 6c 24 20          	mov    0x20(%esp),%ebp
 8049ef6:	8d b3 0c ff ff ff    	lea    -0xf4(%ebx),%esi
 8049efc:	e8 f3 e7 ff ff       	call   80486f4 <_init>
 8049f01:	8d 83 08 ff ff ff    	lea    -0xf8(%ebx),%eax
 8049f07:	29 c6                	sub    %eax,%esi
 8049f09:	c1 fe 02             	sar    $0x2,%esi
 8049f0c:	85 f6                	test   %esi,%esi
 8049f0e:	74 25                	je     8049f35 <__libc_csu_init+0x55>
 8049f10:	31 ff                	xor    %edi,%edi
 8049f12:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8049f18:	83 ec 04             	sub    $0x4,%esp
 8049f1b:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049f1f:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049f23:	55                   	push   %ebp
 8049f24:	ff 94 bb 08 ff ff ff 	call   *-0xf8(%ebx,%edi,4)
 8049f2b:	83 c7 01             	add    $0x1,%edi
 8049f2e:	83 c4 10             	add    $0x10,%esp
 8049f31:	39 fe                	cmp    %edi,%esi
 8049f33:	75 e3                	jne    8049f18 <__libc_csu_init+0x38>
 8049f35:	83 c4 0c             	add    $0xc,%esp
 8049f38:	5b                   	pop    %ebx
 8049f39:	5e                   	pop    %esi
 8049f3a:	5f                   	pop    %edi
 8049f3b:	5d                   	pop    %ebp
 8049f3c:	c3                   	ret    
 8049f3d:	8d 76 00             	lea    0x0(%esi),%esi

08049f40 <__libc_csu_fini>:
 8049f40:	f3 c3                	repz ret 

Disassembly of section .fini:

08049f44 <_fini>:
 8049f44:	53                   	push   %ebx
 8049f45:	83 ec 08             	sub    $0x8,%esp
 8049f48:	e8 c3 e9 ff ff       	call   8048910 <__x86.get_pc_thunk.bx>
 8049f4d:	81 c3 b3 20 00 00    	add    $0x20b3,%ebx
 8049f53:	83 c4 08             	add    $0x8,%esp
 8049f56:	5b                   	pop    %ebx
 8049f57:	c3                   	ret    
