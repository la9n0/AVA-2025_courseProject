.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "../Debug/StaticLibrary.lib
ExitProcess PROTO:DWORD 
.stack 4096


 outlich PROTO : DWORD

 outrad PROTO : DWORD

 compare PROTO : DWORD, : DWORD, : DWORD

.const
		newline byte 13, 10, 0
		LTRL1 word 5
		LTRL2 word 3
		LTRL3 word -2
		LTRL4 byte 'b', 0
		LTRL5 byte 'hello', 0
		LTRL6 byte 'world', 0
		LTRL7 word 0
		LTRL8 word 2
.data
		temp sdword ?
		buffer byte 256 dup(0)
		powloopres word 0
		mainx word 0
		mainy word 0
		mainz word 0
		mainc dword ?
		mainsone dword ?
		mainstwo dword ?
		mainacc word 0
		mainpwr word 0
.code

;----------- powloop ------------
powloop PROC,
	powloopstart : sdword  
; --- save registers ---
push ebx
push edx
; ----------------------
push powloopstart

pop ebx
mov word ptr powloopres, bx

mov cx, word ptr LTRL1
cmp cx, 0
jz cycle_end1
cycle1:

push powloopres
push powloopres
pop ebx
pop eax
imul eax, ebx
push eax

pop ebx
mov word ptr powloopres, bx

loop cycle1
cycle_end1:

; --- restore registers ---
pop edx
pop ebx
; -------------------------
mov eax, powloopres
ret
powloop ENDP
;------------------------------


;----------- MAIN ------------
main PROC
push LTRL1

pop ebx
mov word ptr mainx, bx

push LTRL2

pop ebx
mov word ptr mainy, bx

push LTRL3

pop ebx
mov word ptr mainz, bx

mov mainc, offset LTRL4
mov mainsone, offset LTRL5
mov mainstwo, offset LTRL6
inc word ptr mainx

dec word ptr mainy

not word ptr mainz

push LTRL7

pop ebx
mov word ptr mainacc, bx

push mainx
push mainy
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov word ptr mainz, bx


push mainz
call outlich

push offset newline
call outrad


push LTRL8
call powloop
push eax

pop ebx
mov word ptr mainpwr, bx


push mainpwr
call outlich

push offset newline
call outrad

push 0
call ExitProcess
main ENDP
end main
