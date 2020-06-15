Template: Template.asm IO.inc
	nasm -f elf Template.asm
	ld -m elf_i386 Template.o -o Template
	rm Template.o
