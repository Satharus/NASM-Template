; Assembly with  nasm -f elf Template.asm
; Link with ld -m elf_i386 Template.o -o Template
;
; Or just run make like a chad

%include "IO.inc"
global _start

section .data

startUpString db "NASM Template!", 0xA
strLength equ $-startUpString

section .text
_start:
    
    mov esi, startUpString    
    mov ecx, strLength

    call WriteString

    ;Return zero
    mov eax, 0x1
    mov ebx, 0
    int 0x80
