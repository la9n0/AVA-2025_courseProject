.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib
includelib StaticLib.lib

ExitProcess PROTO: dword

EXTRN lenght_str: proc
EXTRN write_int: proc
EXTRN write_str : proc

.stack 4096

.const
	L0 byte " : ", 0
	L1 sdword 10
	L2 sdword 100
	L3 sdword 2
	L4 sdword 0
	L5 sdword 1
.data
	i_main sdword 0
	result_repeat0 sdword 0
.code

main PROC


push offset L0
call write_str

push L1
pop i_main

cyclenext0:
mov edx, i_main
cmp edx, L2
jg cycle0
push i_main
push L3
pop ebx
pop eax
cdq
idiv ebx
push edx
pop result_repeat0

mov edx, result_repeat0
cmp edx, L4

jg true1
jmp next1
true1:
push i_main
call write_int

next1:

push i_main
push L5
pop ebx
pop eax
add eax, ebx
push eax
pop i_main

jmp cyclenext0
cycle0:

push 0
call ExitProcess
main ENDP
end main
