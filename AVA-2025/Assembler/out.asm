.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib msvcrt.lib
includelib "D:\university\3_sem\kpo\courseProject\AVA-2025\AVA-2025\Debug\StaticLibrary.lib"
ExitProcess PROTO:DWORD 
.stack 4096


 outlich PROTO : DWORD

 outrad PROTO : DWORD

 compare PROTO : DWORD, : DWORD, : DWORD

 slength PROTO : DWORD, : DWORD

 rnd PROTO : DWORD, : DWORD, : DWORD

 copystr PROTO : DWORD, : DWORD

 Sleep PROTO : DWORD

.const
		LTRL1 word 1
		LTRL2 word 10
		LTRL3 word 5
		LTRL4 word -3
		LTRL5 byte 'A', 0
		LTRL6 byte 'Hello', 0
		LTRL7 byte 'World', 0
		LTRL8 byte 'Test', 0
		LTRL9 byte 'Initial values:', 0
		LTRL10 byte 'x=', 0
		LTRL11 byte 'y=', 0
		LTRL12 byte 'z=', 0
		LTRL13 byte 'ch=', 0
		LTRL14 byte 'firststr=', 0
		LTRL15 byte 'secondstr=', 0
		LTRL16 byte 'Checking unary operations:', 0
		LTRL17 byte 'After inc x: x=', 0
		LTRL18 byte 'After dec y: y=', 0
		LTRL19 byte 'After inv z: z=', 0
		LTRL20 byte 'Arithmetic operations:', 0
		LTRL21 byte 'z=x+y: z=', 0
		LTRL22 byte 'z=x-y: z=', 0
		LTRL23 byte 'z=x*y: z=', 0
		LTRL24 byte 'z=x/y: z=', 0
		LTRL25 byte 'z=x%y: z=', 0
		LTRL26 word 2
		LTRL27 byte 'z=x+y*2: z=', 0
		LTRL28 byte 'z=(x+y)*2: z=', 0
		LTRL29 byte 'Results of the functions:', 0
		LTRL30 byte 'factorial(5)=', 0
		LTRL31 word 8
		LTRL32 byte 'power(2,8)=', 0
		LTRL33 word 20
		LTRL34 word 4
		LTRL35 byte 'calculate(20,4)=', 0
		LTRL36 byte 'Static library output:', 0
		LTRL37 byte 'slength(firststr)=', 0
		LTRL38 byte 'compare(firststr,secondstr)=', 0
		LTRL39 word 100
		LTRL40 byte 'rnd(1,100)=', 0
		LTRL41 byte 'copystr(firststr)=', 0
		LTRL42 byte 'Result of the work of cycles:', 0
		LTRL43 word 3
.data
		newline byte 13, 10, 0
		temp sdword ?
		buffer byte 256 dup(0)
		saveecx dword ?
		factorialresult word 0
		powerres word 0
		calculatesum word 0
		calculatediff word 0
		calculateprod word 0
		calculatequot word 0
		calculatemod word 0
		calculateresult word 0
		mainx word 0
		mainy word 0
		mainz word 0
		mainresult word 0
		mainch dword ?
		mainfirststr dword ?
		mainsecondstr dword ?
		mainthirdstr dword ?
		mainlen word 0
		maincmp word 0
		mainrandom word 0
		calculatex word 0
.code

;----------- factorial ------------
factorial PROC,
	factorialn : word  
; --- save registers ---
push ebx
push edx
push ecx
; ----------------------
movzx eax, word ptr LTRL1
push eax

pop eax
mov word ptr factorialresult, ax

movzx ecx, factorialn
cmp ecx, 0
jz cycle_end1
cycle1:

movzx eax, word ptr factorialresult
push eax
movzx eax, word ptr factorialn
push eax
pop ebx
pop eax
imul eax, ebx
push eax

pop eax
mov word ptr factorialresult, ax

dec word ptr factorialn

dec ecx
cmp ecx, 0
jnz cycle1
cycle_end1:

; --- restore registers ---
pop ecx
pop edx
pop ebx
; -------------------------
movzx eax, word ptr factorialresult
ret
factorial ENDP
;------------------------------


;----------- power ------------
power PROC,
	powerbase : word, powerexp : word  
; --- save registers ---
push ebx
push edx
push ecx
; ----------------------
movzx eax, word ptr LTRL1
push eax

pop eax
mov word ptr powerres, ax

movzx ecx, powerexp
cmp ecx, 0
jz cycle_end2
cycle2:

movzx eax, word ptr powerres
push eax
movzx eax, word ptr powerbase
push eax
pop ebx
pop eax
imul eax, ebx
push eax

pop eax
mov word ptr powerres, ax

dec word ptr powerexp

dec ecx
cmp ecx, 0
jnz cycle2
cycle_end2:

; --- restore registers ---
pop ecx
pop edx
pop ebx
; -------------------------
movzx eax, word ptr powerres
ret
power ENDP
;------------------------------


;----------- calculate ------------
calculate PROC,
	calculatea : word, calculateb : word  
; --- save registers ---
push ebx
push edx
push ecx
; ----------------------
movzx eax, word ptr calculatea
push eax
movzx eax, word ptr calculateb
push eax
pop ebx
pop eax
add eax, ebx
push eax

pop eax
mov word ptr calculatesum, ax

movzx eax, word ptr calculatea
push eax
movzx eax, word ptr calculateb
push eax
pop ebx
pop eax
sub eax, ebx
jnc bk
neg eax
bk: 
push eax

pop eax
mov word ptr calculatediff, ax

movzx eax, word ptr calculatea
push eax
movzx eax, word ptr calculateb
push eax
pop ebx
pop eax
imul eax, ebx
push eax

pop eax
mov word ptr calculateprod, ax

movzx eax, word ptr calculatea
push eax
movzx eax, word ptr calculateb
push eax
pop ebx
pop eax
cdq
idiv ebx
push eax

pop eax
mov word ptr calculatequot, ax

movzx eax, word ptr calculatea
push eax
movzx eax, word ptr calculateb
push eax
pop ebx
pop eax
cdq
mov edx,0
idiv ebx
push edx

pop eax
mov word ptr calculatemod, ax

movzx eax, word ptr calculatesum
push eax
movzx eax, word ptr calculatediff
push eax
pop ebx
pop eax
add eax, ebx
push eax
movzx eax, word ptr calculateprod
push eax
pop ebx
pop eax
add eax, ebx
push eax
movzx eax, word ptr calculatequot
push eax
pop ebx
pop eax
add eax, ebx
push eax
movzx eax, word ptr calculatemod
push eax
pop ebx
pop eax
add eax, ebx
push eax

pop eax
mov word ptr calculateresult, ax

; --- restore registers ---
pop ecx
pop edx
pop ebx
; -------------------------
movzx eax, word ptr calculateresult
ret
calculate ENDP
;------------------------------


;----------- MAIN ------------
main PROC
push ebp
mov ebp, esp

movzx eax, word ptr LTRL2
push eax

pop eax
mov word ptr mainx, ax

movzx eax, word ptr LTRL3
push eax

pop eax
mov word ptr mainy, ax

movzx eax, word ptr LTRL4
push eax

pop eax
mov word ptr mainz, ax

mov mainch, offset LTRL5
mov mainfirststr, offset LTRL6
mov mainsecondstr, offset LTRL7
mov mainthirdstr, offset LTRL8

push offset LTRL9
call outrad

push offset newline
call outrad


push offset LTRL10
call outrad


movzx eax, word ptr mainx
push eax
call outlich

push offset newline
call outrad


push offset LTRL11
call outrad


movzx eax, word ptr mainy
push eax
call outlich

push offset newline
call outrad


push offset LTRL12
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad


push offset LTRL13
call outrad


push mainch
call outrad

push offset newline
call outrad


push offset LTRL14
call outrad


push mainfirststr
call outrad

push offset newline
call outrad


push offset LTRL15
call outrad


push mainsecondstr
call outrad

push offset newline
call outrad

inc word ptr mainx

dec word ptr mainy

neg word ptr mainz

push offset newline
call outrad


push offset LTRL16
call outrad

push offset newline
call outrad


push offset LTRL17
call outrad


movzx eax, word ptr mainx
push eax
call outlich

push offset newline
call outrad


push offset LTRL18
call outrad


movzx eax, word ptr mainy
push eax
call outlich

push offset newline
call outrad


push offset LTRL19
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad

push offset newline
call outrad


push offset LTRL20
call outrad

push offset newline
call outrad

movzx eax, word ptr mainx
push eax
movzx eax, word ptr mainy
push eax
pop ebx
pop eax
add eax, ebx
push eax

pop eax
mov word ptr mainz, ax


push offset LTRL21
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad

movzx eax, word ptr mainx
push eax
movzx eax, word ptr mainy
push eax
pop ebx
pop eax
sub eax, ebx
jnc bkm
neg eax
bkm: 
push eax

pop eax
mov word ptr mainz, ax


push offset LTRL22
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad

movzx eax, word ptr mainx
push eax
movzx eax, word ptr mainy
push eax
pop ebx
pop eax
imul eax, ebx
push eax

pop eax
mov word ptr mainz, ax


push offset LTRL23
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad

movzx eax, word ptr mainx
push eax
movzx eax, word ptr mainy
push eax
pop ebx
pop eax
cdq
idiv ebx
push eax

pop eax
mov word ptr mainz, ax


push offset LTRL24
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad

movzx eax, word ptr mainx
push eax
movzx eax, word ptr mainy
push eax
pop ebx
pop eax
cdq
mov edx,0
idiv ebx
push edx

pop eax
mov word ptr mainz, ax


push offset LTRL25
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad

movzx eax, word ptr mainx
push eax
movzx eax, word ptr mainy
push eax
movzx eax, word ptr LTRL26
push eax
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
add eax, ebx
push eax

pop eax
mov word ptr mainz, ax


push offset LTRL27
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad

movzx eax, word ptr mainx
push eax
movzx eax, word ptr mainy
push eax
pop ebx
pop eax
add eax, ebx
push eax
movzx eax, word ptr LTRL26
push eax
pop ebx
pop eax
imul eax, ebx
push eax

pop eax
mov word ptr mainz, ax


push offset LTRL28
call outrad


movzx eax, word ptr mainz
push eax
call outlich

push offset newline
call outrad

push offset newline
call outrad


push offset LTRL29
call outrad

push offset newline
call outrad


movzx eax, word ptr LTRL3
push eax
call factorial
push eax

pop eax
mov word ptr mainresult, ax


push offset LTRL30
call outrad


movzx eax, word ptr mainresult
push eax
call outlich

push offset newline
call outrad


movzx eax, word ptr LTRL31
push eax
movzx eax, word ptr LTRL26
push eax
call power
push eax

pop eax
mov word ptr mainresult, ax


push offset LTRL32
call outrad


movzx eax, word ptr mainresult
push eax
call outlich

push offset newline
call outrad


movzx eax, word ptr LTRL34
push eax
movzx eax, word ptr LTRL33
push eax
call calculate
push eax

pop eax
mov word ptr mainresult, ax


push offset LTRL35
call outrad


movzx eax, word ptr mainresult
push eax
call outlich

push offset newline
call outrad

push offset newline
call outrad


push offset LTRL36
call outrad

push offset newline
call outrad


push mainfirststr
push offset buffer
call slength
push eax

pop eax
mov word ptr mainlen, ax


push offset LTRL37
call outrad


movzx eax, word ptr mainlen
push eax
call outlich

push offset newline
call outrad


push mainsecondstr
push mainfirststr
push offset buffer
call compare
push eax

pop eax
mov word ptr maincmp, ax


push offset LTRL38
call outrad


movzx eax, word ptr maincmp
push eax
call outlich

push offset newline
call outrad


movzx eax, word ptr LTRL39
push eax
movzx eax, word ptr LTRL1
push eax
push offset buffer
call rnd
push eax

pop eax
mov word ptr mainrandom, ax


push offset LTRL40
call outrad


movzx eax, word ptr mainrandom
push eax
call outlich

push offset newline
call outrad


push mainfirststr
push offset buffer
call copystr
mov mainthirdstr, eax

push offset LTRL41
call outrad


push mainthirdstr
call outrad

push offset newline
call outrad

push offset newline
call outrad


push offset LTRL42
call outrad

push offset newline
call outrad

movzx ecx, word ptr LTRL43
cmp ecx, 0
jz cycle_end3
cycle3:

inc word ptr calculatex

mov saveecx, ecx
push offset LTRL10
call outrad
mov ecx, saveecx

mov saveecx, ecx
movzx eax, word ptr calculatex
push eax
call outlich
mov ecx, saveecx

mov saveecx, ecx
push offset newline
call outrad
mov ecx, saveecx

dec ecx
cmp ecx, 0
jnz cycle3
cycle_end3:

movzx eax, word ptr LTRL3
push eax

pop eax
mov word ptr calculatex, ax

movzx ecx, calculatex
cmp ecx, 0
jz cycle_end4
cycle4:

dec word ptr calculatex

mov saveecx, ecx
push offset LTRL10
call outrad
mov ecx, saveecx

mov saveecx, ecx
movzx eax, word ptr calculatex
push eax
call outlich
mov ecx, saveecx

mov saveecx, ecx
push offset newline
call outrad
mov ecx, saveecx

dec ecx
cmp ecx, 0
jnz cycle4
cycle_end4:

push 30000
call Sleep
mov esp, ebp
pop ebp
push 0
call ExitProcess
main ENDP
end main

