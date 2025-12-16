#pragma once

#include "IT.h"
#include "LexAnalysis.h"
#include "LT.h"

#define SEPSTREMP "\n;------------------------------\n"
#define SEPSTR(x) "\n;----------- " + string(x) + " ------------\n"

#define BEGIN ".586\n"\
".model flat, stdcall\n"\
"includelib libucrt.lib\n"\
"includelib kernel32.lib\n"\
"includelib msvcrt.lib\n"\
"includelib \"D:\\university\\3_sem\\kpo\\courseProject\\AVA-2025\\AVA-2025\\Debug\\StaticLibrary.lib\"\n"\
"ExitProcess PROTO:DWORD \n"\
".stack 4096\n"

#define END "push 30000\ncall Sleep\nmov esp, ebp\npop ebp\npush 0\ncall ExitProcess\nmain ENDP\nend main\n"

#define EXTERN "\n outlich PROTO : DWORD\n"\
"\n outrad PROTO : DWORD\n"\
"\n compare PROTO : DWORD, : DWORD, : DWORD\n"\
"\n slength PROTO : DWORD, : DWORD\n"\
"\n rnd PROTO : DWORD, : DWORD, : DWORD\n"\
"\n copystr PROTO : DWORD, : DWORD\n"\
"\n Sleep PROTO : DWORD\n"

#define ITENTRY(x) tables.idtable.table[tables.lextable.table[x].idxTI]
#define LEXEMA(x) tables.lextable.table[x].lexema

#define CONST ".const"
#define DATA ".data\n\t\tnewline byte 13, 10, 0\n\t\ttemp sdword ?\n\t\tbuffer byte 256 dup(0)\n\t\tsaveecx dword ?"
#define CODE ".code"

namespace Gener {
    void CodeGeneration(Lexer::LEX& tables, Parm::PARM& parm, Log::LOG& log);
}
