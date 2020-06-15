section .text
; Takes:
;	al: char
; Writes the specified value as an ASCII character to STDOUT.
WriteChar:
    push ecx
    push edx
    push ebx
    
    push eax       	;Store parameter on the stack
    mov ecx, esp	;Get address of the parameter
    mov eax, 0x4	;Specifying the write syscall
    mov ebx, 0x1	;STDOUT file descriptor
    mov edx, 1		;Printing one byte
    int 0x80		;Invoke the syscall
    pop eax		;Clean up the stack
    
    pop ebx
    pop edx
    pop ecx
	ret

; Returns:
;	al: value of the char
; Reads a character from STDIN, saves it in al.
ReadChar:
    sub esp, 4		;allocate a dword on the stack
    mov eax, 3		;sys_read systemcall
    mov ebx, 0		;STDIN file descriptor
    mov ecx, esp	;move the allocated dword address to ecx
    mov edx, 2		;Reading one byte
    int 80h		;Invoke the syscall

    mov al, BYTE [esp] 	;Move the read value into al
    add esp, 4		;Clean up the stack
    ret

; Takes:
;	ecx: String maximum length
;	esi: address of where to store the string
; Returns:
;	eax: number of bytes read, i.e. string length
ReadString:
    push esi
    push ecx

    mov eax, 3		;sys_read systemcall
    mov ebx, 0		;STDIN file descriptor
    mov edx, ecx	;Reading n bytes
    mov ecx, esi	;move the allocated dword address to ecx
    int 80h		;Invoke the syscall
    pop ecx
    pop esi

    mov eax, 0
    .count:
        inc eax
        inc esi
    cmp eax, ecx
    je .equal

    cmp BYTE [esi], 0xA
    je .done
    jmp .count
    .equal:
        mov eax, ecx
    .done:
    ret

; No parameters, prints a new line.
WriteLine:
    push eax

    mov al, 0xA
    call WriteChar
    
    pop eax
    ret

; Takes:
;	esi: address of the string to be written
;	ecx: length of the string 
WriteString:
    .print:
    mov eax, [esi]
    call WriteChar
    inc esi
    loop .print
    ret

; Takes:
;	eax: value
; Prints the value in decimal (base-10)
WriteDec:
    push 0xf1a9
    .next:
        mov ecx, 10
        mov edx, 0
        div ecx
        add dl, 0x30
        mov edi, eax
        xor eax, eax
        mov al, dl
        push eax
        mov eax, edi
    cmp eax, 0
    jne .next
    .print:
        pop eax
        cmp eax, 0xf1a9
        je .done
        call WriteChar
        jmp .print
    .done:
    ret

; Returns:
;	al: value of the hex byte
; Reads a byte in hex, without the leading 0x
ReadHexByte:
    push ecx
    push esi
    push ebx
    push edx

    sub esp, 4		;allocate a dword on the stack
    mov eax, 3		;sys_read systemcall
    mov ebx, 0		;STDIN file descriptor
    mov ecx, esp	;move the allocated dword address to ecx
    mov edx, 3		;Reading 2 bytes
    int 80h			;Invoke the syscall
    mov esi, esp

    mov ecx, 2
    .nextbyte:
    cmp BYTE[esi], '9'
    jle  .zeroto9
        sub BYTE[esi], 0x27
    .zeroto9:
    sub BYTE[esi], 0x30
    inc esi
    loop .nextbyte
    
    movzx ax, BYTE [esp] 	;Move the read value into ax
    shl	ax, 8
    mov	al, BYTE [esp+1]
    shl al, 4
    shr ax, 4 
    add esp, 4			;Clean up the stack


    pop edx
    pop ebx
    pop esi
    pop ecx
    ret
; Takes:
;	eax: value
; Prints the value in hexa (base-16)
WriteHex:
    push edx
    push ecx
    push edi
    
    push eax	
    mov al, '0'
    call WriteChar
    mov al, 'x'
    call WriteChar
    pop eax
    
    push 0xf1a9
    .next:
        mov ecx, 16
        mov edx, 0
        div ecx
    cmp dl, 10
    jl  .zeroto9
        add dl, 0x7
    .zeroto9:
        add dl, 0x30
        mov edi, eax
        xor eax, eax
        mov al, dl
        push eax
        mov eax, edi
    cmp eax, 0
    jne .next
    .print:
        pop eax
        cmp eax, 0xf1a9
        je .done
        call WriteChar
        jmp .print
    .done:

    pop edi
    pop ecx
    pop edx
	ret

; Takes:
;	esi: address of a byte array of length 16
; Prints the array as a 4x4 grid
Print4x4Matrix:
    mov bl, 0
    mov ecx, 16
    .print:
            xor eax, eax
            mov al, [esi]
            call WriteHex
            inc esi
            inc bl
        cmp bl, 4
        jne .next
        mov al, 0xA
        call WriteChar
        mov bl, 0
        jmp .done
        .next:
        mov al, ' '
        call WriteChar
        .done:
    loop .print
    ret
