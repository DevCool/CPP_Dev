%ifndef __STDIO_INC_INCLUDED__
%define __STDIO_INC_INCLUDED__


;==========================================================
;
;	 16 Bit Real Mode Routines
;==========================================================



;************************************************;
;	Puts16 ()
;		-Prints a null terminated string
;	DS=>SI: 0 terminated string
;************************************************;

bits	16

puts:
	pusha				; save registers

.loop:
	lodsb				; load next byte from string from SI to AL
	or	al, al			; Does AL=0?
	jz	.done		; Yep, null terminator found-bail out
	mov	ah, 0eh			; Nope-Print the character
	int	10h			; invoke BIOS

	jmp	.loop			; Repeat until null terminator found

.done:
	popa				; restore registers
	ret				; we are done, so return


change_mode:	
	mov ah, 00h
	int 10h

	ret


print_string:
	lodsb        ; grab a byte from SI
	or al, al  ; logical or AL by itself
	jz .done   ; if the result is zero, get out

	mov ah, 0Eh
	mov bx, 000Ah
	int 10h      ; otherwise, print out the character!

	jmp print_string

.done:
	ret



get_string:
	xor cl, cl

	.loop:
		mov ah, 0
		int 0x16   ; wait for keypress

		cmp al, 0x08    ; backspace pressed?
		je .backspace   ; yes, handle it

		cmp al, 0x0D  ; enter pressed?
		je .done      ; yes, we're done

		cmp cl, 0x3F  ; 63 chars inputted?
		je .loop      ; yes, only let in backspace and enter

		mov ah, 0x0E
		int 0x10      ; print out character

		stosb  ; put character in buffer
		inc cl

		jmp .loop

	.backspace:
		cmp cl, 0	; beginning of string?
		je .loop	; yes, ignore the key

		dec di
		mov byte [di], 0	; delete character
		dec cl		; decrement counter as well

		mov ah, 0x0E
		mov al, 0x08
		int 10h		; backspace on the screen

		mov al, ' '
		int 10h		; blank character out

		mov al, 0x08
		int 10h		; backspace again

		jmp .loop	; go to the main loop

	.done:
		mov al, 0	; null terminator
		stosb

		mov ah, 0x0E
		mov al, 0x0D
		int 0x10
		mov al, 0x0A
		int 0x10		; newline

		ret



strcmp:
	.loop:
		mov al, [si]   ; grab a byte from SI
		mov bl, [di]   ; grab a byte from DI
		cmp al, bl     ; are they equal?
		jne .notequal  ; nope, we're done.

		cmp al, 0  ; are both bytes (they were equal before) null?
		je .done   ; yes, we're done.

		inc di     ; increment DI
		inc si     ; increment SI
		jmp .loop  ; loop!

	.notequal:
		clc  ; not equal, clear the carry flag
		ret

	.done: 	
		stc  ; equal, set the carry flag
		ret


strcmp2:
	.loop:
		mov al, [si]   ; grab a byte from SI
		mov bl, [di]   ; grab a byte from DI
		cmp al, bl     ; are they equal?
		jne .notequal  ; nope, we're done.

		cmp byte [si], 20h
		je .space

		cmp al, 0  ; are both bytes (they were equal before) null?
		je .done   ; yes, we're done.

		inc di     ; increment DI
		inc si     ; increment SI
		jmp .loop  ; loop!

	.space:
		stc
		ret

	.notequal:
		clc  ; not equal, clear the carry flag
		ret

	.done: 	
		stc  ; equal, set the carry flag
		ret


intToString:
    push  dx
    push  cx
    push  di
    push  bp
    mov   bp, sp
    mov   cx, 10

	.pushDigits:
		xor   dx, dx        ; zero-extend eax
		div   cx             ; divide by 10; now edx = next digit
		add   dx, 30h        ; decimal value + 30h => ascii digit
		push  dx             ; push the whole dword, cause that's how x86 rolls
		test  ax, ax        ; leading zeros suck
		jnz   .pushDigits

	.popDigits:
		pop   ax
		stosb                 ; don't write the whole dword, just the low byte
		cmp   sp, bp        ; if sp==bp, we've popped all the digits
		jne   .popDigits

		xor   ax, ax        ; add trailing nul
		stosb

		mov   ax, di
		pop   bp
		pop   di
		pop   cx
		pop   dx
		sub   ax, di        ; return number of bytes written
		ret


%endif ;__STDIO_INC_INCLUDED__
