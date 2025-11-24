.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
includelib StaticLib.lib

ExitProcess PROTO: dword

EXTRN lenght: proc
EXTRN write_int: proc
EXTRN write_str : proc
EXTRN copy: proc
EXTRN getLocalTimeAndDate: proc
EXTRN random: proc
EXTRN squareOfNumber: proc
EXTRN factorialOfNumber: proc
EXTRN powNumber: proc

.stack 4096

.const
nulError byte 'error divided by zero', 0
nul sdword 0, 0

.data
	a_main sdword 0
.code

main PROC

jmp goodExit
errorExit:
push offset nulError
call write_str
goodExit:
push 0
call ExitProcess
main ENDP
end main
