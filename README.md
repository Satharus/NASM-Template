# NASM-Template

##### This is a template for writing assembly using NASM.

It has a template "main" file, makefile, and a few helper functions to help with I/O without having to use Linux syscalls explicitly.

I wrote these functions for the [AES Encryption](https://github.com/Satharus/AES-Encryption) project, so that's why some functions are oddly specific.

## Function Guide:

|    Function    |                        Parameters                       |          Returns          |                            Description                           |
|:--------------:|:-------------------------------------------------------:|:-------------------------:|:----------------------------------------------------------------:|
| ReadChar       |                           N/A                           | al: Character read        | Reads a character from STDIN and saves it in al.                 |
| WriteChar      | al: Character                                           |            N/A            | Writes the specified ASCII character to STDOUT.                  |
| ReadString     | ecx: String max length esi: Address of storage location | eax: Number of bytes read | Reads a string from STDIN and saves it at the specified address. |
| WriteString    | ecx: Length of the string esi: Address of the string    |            N/A            | Writes the specified string to STDOUT.                           |
| WriteLine      |                           N/A                           |            N/A            | Writes a new line ('\n') to STDOUT.                              |
| WriteDec       | eax: Value to be written                                |            N/A            | Writes the specified value in base-10 (Decimal) to STDOUT.       |
| ReadHexByte    |                           N/A                           | al: Value read            | Reads a hex byte from STDIN, without 0x or h. Ex: 3A or F5       |
| WriteHex       | eax: Value to be written                                |            N/A            | Writes the specified hex value to STDOUT.                        |
| Print4x4Matrix | esi: byte array of length 16                            |            N/A            | Write the array as a 4x4 hex grid.                               |
