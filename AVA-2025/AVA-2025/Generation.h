#pragma once
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"

#define IT_ENTRY(x)		idtable.table[lextable.table[x]->idxTI]
#define LT_ENTRY(x)		lextable.table[x]

#define SEPSTREMP  "\n"
#define SEPSTR(x)  "\n"

#define BEGIN			".586\n"											\
					   << ".model flat, stdcall\n"										\
					   << "includelib kernel32.lib\n"																					\
					   << "includelib libucrt.lib\n"																					\
					   << "includelib StaticLib.lib\n\n"																				\
					   << "ExitProcess PROTO: dword\n\n"

#define EXTERN			 "EXTRN strcmp: proc\n"																						\
					   << "EXTRN write_uint: proc\n"																						\
					   << "EXTRN write_short: proc\n"																						\
					   << "EXTRN write_char: proc\n"																						\
					   << "EXTRN write_bool: proc\n"																						\
					   << "EXTRN write_str: proc\n\n"

#define STACK(value)	".stack " << value << "\n\n"

#define CONST			".const\nnulError byte 'error divided by zero', 0\nnul sdword 0, 0\n"

#define DATA			".data"

#define CODE			".code\n"

#define END				"jmp goodExit\nerrorExit:\npush offset nulError\ncall write_str\ngoodExit:\npush 0\ncall ExitProcess\nmain ENDP\nend main"


namespace GN
{
	enum class IfEnum { thenOrElse, repeat };
	struct A
	{
		int openRightbrace;
		int branchingnNum;
		IfEnum ifEnum;
		A(int open, int branch, IfEnum ifE)
		{
			openRightbrace = open;
			branchingnNum = branch;
			ifEnum = ifE;
		}
	};

	void GenerationASM(std::ostream* stream, LT::LexTable& lextable, IT::IdTable& idtable);
	void GenConstAndData(IT::IdTable& idtable, ostream* file);
	void GenCode(LT::LexTable& lextable, IT::IdTable& idtable, ostream* file);

	string GenEqualCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i);
	string GenFunctionCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i);
	string GenExitCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i, string funcname);
	string GenCallFuncCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i);
	string GenBranchingCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i, int branchingnNum);

	string itoS(int x);
}
