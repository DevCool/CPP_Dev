bits 16


; Remember the memory map-- 0x500 through 0x7bff is unused above the BIOS data area.

; We are loaded at 0x500 (0x50:0)


org 0x500

jmp	main				; go to start



;*******************************************************

;	Preprocessor directives

;*******************************************************


%include "stdio.inc"			; basic i/o routines
%include "Gdt.inc"			; Gdt routines
%include "A20.inc"			; A20 enabling


;*******************************************************

;	Data Section

;*******************************************************



msg_loading 			db 0x0D, 0x0A, "Searching for System...", 0
welcome:			db 'Welcome to a Special Kernel!', 0x0D, 0x0A
				db 'Special Boot ( Coded by Philip R. Simonson )', 0x0D, 0x0A, 0x0D, 0x0A, 0
msg_helloworld			db 'Hello, ', 0
badcommand			db 'Bad command entered.', 0x0D, 0x0A, 0
prompt				db '[ CMD ] : ', 0
cmd_hi				db 'hi', 0
cmd_help			db 'help', 0
cmd_reboot			db 'reboot', 0
msg_help			db 'Special Kernel Commands:', 0x0D, 0x0A, '    hi, help, reboot', 0x0D, 0x0A, 0
hmaster				db 'Hello...', 0x0D, 0x0A, 'Master I am here to serve.', 0x0D, 0x0A, 0
master				db 'Philip R. Simonson', 0x00
msg_reboot			db 'Rebooting, please wait . . .', 0x0D, 0x0A, 0
msg_login			db 0x0D, 0x0A, 'Login: ', 0
msg_nameinput			db 'Input your name: ', 0
bad_login			db 'The master code is not that.', 0x0D, 0x0A, 'Try again!', 0x0D, 0x0A, 0
three_left			db 'Tries left: ', 0
tries				db 3
mstr_code			db 'Ruben', 0
buffer				times 64 db 0
tries_buffer			db 0, 0
crlf				db 0Dh, 0Ah, 0
x_crlf				db 21h, 0Dh, 0Ah, 0



;*******************************************************

;	STAGE 2 ENTRY POINT

;

;		-Store BIOS information

;		-Load Kernel

;		-Install GDT; go into protected mode (pmode)

;		-Jump to Stage 3

;*******************************************************



main:

	;-------------------------------;
	;   Setup segments and stack	;
	;-------------------------------;

	cli				; clear interrupts
	xor	ax, ax			; null segments
	mov	ds, ax
	mov	es, ax
	mov	ax, 0x9000		; stack begins at 0x9000-0xffff
	mov	ss, ax
	mov	sp, 0xFFFF
	sti				; enable interrupts

	;-------------------------------;
	;   Install our GDT		;
	;-------------------------------;

	call	InstallGDT		; install our GDT

	;-------------------------------;
	;   Enable A20			;
	;-------------------------------;

	call	EnableA20_KKbrd_Out

	mov al, 0Eh
	call change_mode


EnterStage3:
	mov	si, msg_loading
	call print_string

	mov si, crlf
	call print_string

	.login:

		mov si, msg_login
		call print_string

		mov di, buffer
		call get_string

		mov si, buffer
		cmp byte [si], 0 ; blank line?

		je .login		 ; yes, ignore it

		mov si, buffer
		mov di, mstr_code ; "Joshua" login code
		call strcmp

		jc the_beginning

		mov si, buffer
		mov di, cmd_reboot ; "reboot" command
		call strcmp

		jc mainloop.reboot		   ; reboot computer

		mov si, bad_login  ; "bad_login" message
		call print_string
		mov si, three_left
		call print_string

		xor ax, ax
		mov al, [tries]
		dec al
		mov [tries], al

		mov al, byte [tries]
		mov di, tries_buffer
		call intToString

		mov si, tries_buffer
		call print_string

		mov si, crlf
		call print_string

		cmp byte [tries], 0
		je .cold_reboot

		jmp .login

		.cold_reboot:
			mov si, crlf
			call print_string
			jmp mainloop.reboot

			

the_beginning:
	mov si, welcome
	call print_string

mainloop:
	mov si, prompt
	call print_string

	mov di, buffer
	call get_string

	mov si, buffer
	cmp byte [si], 0  ; blank line?
	je mainloop       ; yes, ignore it

	mov si, buffer
	mov di, cmd_hi  ; "hi" command
	call strcmp
	jc .helloworld

	mov si, buffer
	mov di, cmd_help  ; "help" command
	call strcmp
	jc .help

	mov si, buffer
	mov di, cmd_reboot ; "reboot" command
	call strcmp
	jc .reboot

	mov si,badcommand
	call print_string 
	jmp mainloop  


	.helloworld:

		mov si, msg_nameinput
		call print_string

		mov di, buffer
		call get_string

		mov si, buffer
		cmp byte [si], 0
		je .helloworld

		mov si, buffer
		mov di, master
		call strcmp
		jc .hmstr

		mov si, msg_helloworld
		call print_string

		mov si, buffer
		call print_string

		mov si, x_crlf
		call print_string

		jmp mainloop

		.hmstr:
		mov si, hmaster
		call print_string
		jmp mainloop

	.help:
		mov si, msg_help
		call print_string

		jmp mainloop

	.reboot:
		mov si, msg_reboot
		call print_string

		cli

		db 0EAh
		dw 0000h
		dw 0FFFFh

		ret

