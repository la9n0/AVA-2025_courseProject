#include "CodeGeneration.h"
#include <stack>
#include <cstring>
#include <vector>
#include <string>
#include "IT.h"
#include "LT.h"

namespace CodeGeneration {

	static int fors = 1;

	void Head(Out::OUT out) {
		*out.stream << ".586P\n";
		*out.stream << ".model flat, stdcall\n";
		*out.stream << "includelib libucrt.lib\n";
		*out.stream << "includelib kernel32.lib\n";
		*out.stream << "includelib ../Debug/AVA-2025Lib.lib\n";
		*out.stream << "ExitProcess PROTO : DWORD\n\n";
		*out.stream << "SetConsoleCP PROTO : DWORD\n\n";
		*out.stream << "SetConsoleOutputCP PROTO : DWORD\n\n";
		*out.stream << "Pow PROTO : WORD, : WORD \n\n";
		*out.stream << "Sum PROTO : WORD, : WORD \n\n";
		*out.stream << "StrCmp PROTO : DWORD, : DWORD \n\n";
		*out.stream << "writestr PROTO : DWORD \n\n";
		*out.stream << "writeint PROTO : WORD \n\n";
		*out.stream << "writebool PROTO : BYTE \n\n";
		*out.stream << "writechar PROTO : BYTE \n\n";
		*out.stream << ".stack 4096\n\n";
	}

	void Const(Out::OUT out, MFST::LEX lex) {
		*out.stream << ".const\n";

		for (int i = 0; i < lex.idtable.size; i++) {
			if (lex.idtable.table[i].idtype == IT::LITERAL) {
				*out.stream << lex.idtable.table[i].id;

				//     
				switch (lex.idtable.table[i].iddatatype) {
				case IT::INT: {
					*out.stream << " WORD " << lex.idtable.table[i].value.vint << " ; int (2)";
					break;
				}
				case IT::SYMBOL: {
					//      (int)
					*out.stream << " BYTE " << (int)lex.idtable.table[i].value.vsymbol << " ; symbol";
					break;
				}
				}
				*out.stream << "\n";
			}
		}
		*out.stream << "\n";
	}


	void Data(Out::OUT out, MFST::LEX lex) {
		*out.stream << ".data\n";
		for (int i = 0; i < lex.idtable.size; i++) {
			if (lex.idtable.table[i].idtype == IT::VARIABLE) {
				*out.stream << lex.idtable.table[i].id;
				switch (lex.idtable.table[i].iddatatype) {
				case IT::INT: {
					*out.stream << " WORD 0 ; int (2)";
					break;
				}
				case IT::SYMBOL: {
					*out.stream << " BYTE 0 ; symbol";
					break;
				}
				}
				*out.stream << "\n";
			}
		}
		*out.stream << "\n";
	}

	bool compareVectorToCString(const std::vector<char>& vec, const char* cstr) {
		if (vec.size() != std::strlen(cstr)) {
			return false;
		}

		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] != cstr[i]) {
				return false;
			}
		}

		return true;
	}

	void Expression(Out::OUT out, MFST::LEX lex, int startPos, int endPos) {
		for (int i = startPos; i < endPos; i++) {
			if (lex.lextable.table[i].lexema == LEX_ASSIGNMENT) {
				*out.stream << "\n" << "; string #" << lex.lextable.table[i].sn << " : ";
				for (int j = -1; lex.lextable.table[i + j].lexema != LEX_SEMICOLON; j++) {
					*out.stream << lex.lextable.table[i + j].lexema;
				}
				*out.stream << "\n";
				bool isArgs = false;
				IT::Entry* func, * save = nullptr;
				IT::Entry* recipent = &lex.idtable.table[lex.lextable.table[i - 1].idxTI];
				IT::Entry* sender = &lex.idtable.table[lex.lextable.table[i + 1].idxTI];
				if (sender->idtype != IT::FUNCTION && sender->idtype != IT::STATIC_FUNCTION) {
					switch (recipent->iddatatype) {
					case IT::INT: {
						if (sender->idtype == IT::LITERAL) {
							*out.stream << "mov ax, " << sender->id << "\n";
						}
						else {
							*out.stream << "mov ax, " << sender->id << "\n";
						}
						*out.stream << "mov " << recipent->id << ", ax \n";
						break;
					}
					case IT::SYMBOL: {
						if (sender->idtype == IT::LITERAL) {
							*out.stream << "mov al, " << sender->id << "\n";
						}
						else {
							*out.stream << "mov al, " << sender->id << "\n";
						}
						*out.stream << "mov " << recipent->id << ", al \n";
						break;
					}
					}
				}
				else {
					//  -
					stack<IT::Entry> stackForParams;
					int iterator = 2;
					while (lex.lextable.table[i + iterator].lexema != '@') {
						stackForParams.push(lex.idtable.table[lex.lextable.table[i + iterator].idxTI]);
						iterator += 1;
					}
					while (!stackForParams.empty()) {
						switch (stackForParams.top().iddatatype) {
						case IT::SYMBOL: {
							*out.stream << "movsx ax, " << stackForParams.top().id << "\n";
							*out.stream << "push ax\n";
							break;
						}
						case IT::INT: {
							*out.stream << "push " << stackForParams.top().id << "\n";
							break;
						}
						}
						stackForParams.pop();
					}
					if (sender->idtype == IT::FUNCTION) {
						*out.stream << "CALL F" << sender->id << "\n";
					}
					else {
						if (strcmp(sender->id, "Pow") == 0) {
							*out.stream << "CALL Pow" << "\n";
						}
						if (strcmp(sender->id, "Sum") == 0) {
							*out.stream << "CALL Sum" << "\n";
						}
						if (strcmp(sender->id, "StrCmp") == 0) {
							*out.stream << "CALL StrCmp" << "\n";
						}
					}
					if (sender->iddatatype == IT::SYMBOL) {
						*out.stream << "mov " << recipent->id << ", al\n";
					}
					else {
						*out.stream << "mov " << recipent->id << ", ax\n";
					}
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_FOR) {
				int cur = 1;
				int startPos;
				bool isEnd = false;
				bool isFirstFunc = false;
				bool isFirstFuncA = false;
				bool isSecondFunc = false;
				bool isSecondFuncA = false;
				IT::Entry* firstParams[16];
				int firstCounter = 0;
				IT::Entry* secondParams[16];
				int secondCounter = 0;
				IT::Entry* first = nullptr, * second = nullptr;
				std::string op = "";
				int currentFor = fors; //   fors
				fors++; //    if
				*out.stream << "\nFor_Begin" << currentFor << ": \n";
				while (true) {
					switch (lex.lextable.table[i + cur].lexema) {
					case '@': {
						if (isFirstFunc) {
							isFirstFunc = false;
							break;
						}
						if (isSecondFunc) {
							isSecondFunc = false;
							break;
						}
					}
					case LEX_RIGHTTHESIS: {
						startPos = i + 1;
						break;
					}
					case LEX_ID: {
						if (isFirstFunc) {
							firstParams[firstCounter++] = &lex.idtable.table[lex.lextable.table[i + cur].idxTI];
							break;
						}
						if (isSecondFunc) {
							secondParams[secondCounter++] = &lex.idtable.table[lex.lextable.table[i + cur].idxTI];
							break;
						}
						if (first == nullptr) {
							first = &lex.idtable.table[lex.lextable.table[i + cur].idxTI];
							if (first->idtype == IT::FUNCTION || first->idtype == IT::STATIC_FUNCTION) {
								isFirstFunc = true;
								isFirstFuncA = true;
							}
						}
						else {
							second = &lex.idtable.table[lex.lextable.table[i + cur].idxTI];
							if (second->idtype == IT::FUNCTION || second->idtype == IT::STATIC_FUNCTION) {
								isSecondFunc = true;
								isSecondFuncA = true;
							}
						}
						break;
					}
					case LEX_LITERAL: {
						if (isFirstFunc) {
							firstParams[firstCounter++] = &lex.idtable.table[lex.lextable.table[i + cur].idxTI];
							break;
						}
						if (isSecondFunc) {
							secondParams[secondCounter++] = &lex.idtable.table[lex.lextable.table[i + cur].idxTI];
							break;
						}
						if (first == nullptr) {
							first = &lex.idtable.table[lex.lextable.table[i + cur].idxTI];
						}
						else {
							second = &lex.idtable.table[lex.lextable.table[i + cur].idxTI];
						}
						break;
					}
				    //   
					case LEX_ASSIGNMENT: {
						break;
					}
					case LEX_LEFTBRACE: {
						break;

					}
					case LEX_BRACELET: {
						isEnd = true;
						break;
					}
					}
					if (isEnd) {
						*out.stream << "For_End" << currentFor << ":\n"; //  For_End
						//  
						Expression(out, lex, startPos, i + cur);
						i = i + cur;
						break;
					}
					cur++;
				}
				*out.stream << "For_End" << currentFor + 1 << ":\n"; //    if
			}

			else if (lex.lextable.table[i].lexema == LEX_INCREMENT || 
					 lex.lextable.table[i].lexema == LEX_DECREMENT || 
					 lex.lextable.table[i].lexema == LEX_INVERSION) {
				// Обработка унарных операций (в польской записи операнд идет перед оператором)
				if (i > 0 && (lex.lextable.table[i - 1].lexema == LEX_ID || lex.lextable.table[i - 1].lexema == LEX_LITERAL)) {
					IT::Entry* operand = &lex.idtable.table[lex.lextable.table[i - 1].idxTI];
					if (operand->iddatatype == IT::INT) {
						*out.stream << "\n; unary operation\n";
						*out.stream << "mov ax, " << operand->id << "\n";
						if (lex.lextable.table[i].lexema == LEX_INCREMENT) {
							*out.stream << "inc ax\n";
						}
						else if (lex.lextable.table[i].lexema == LEX_DECREMENT) {
							*out.stream << "dec ax\n";
						}
						else if (lex.lextable.table[i].lexema == LEX_INVERSION) {
							*out.stream << "not ax\n";
						}
						*out.stream << "mov " << operand->id << ", ax\n";
					}
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_RETURN) {
				*out.stream << "\n;return\n";
				if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].iddatatype == IT::INT) { 
						*out.stream << "mov ax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\n";
				}
				else {
					*out.stream << "movzx ax, " << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << "\n";
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_DISPLAY) {
				switch (lex.idtable.table[lex.lextable.table[i + 2].idxTI].iddatatype)
				{
				case (IT::SYMBOL): {
					*out.stream << "push eax\n";
					*out.stream << "movzx eax, " << lex.idtable.table[lex.lextable.table[i + 2].idxTI].id << '\n';
					*out.stream << "push eax\n";
					*out.stream << "CALL writechar" << '\n';
					*out.stream << "pop eax\n" << '\n';
					break;
				}
				case (IT::INT): {
					*out.stream << "\nmov ax, " << lex.idtable.table[lex.lextable.table[i + 2].idxTI].id << "\n";
					*out.stream << "push ax\n";
					*out.stream << "CALL writeint" << '\n';
					break;
				}
				}
			}
			else if (lex.lextable.table[i].lexema == LEX_ID &&
				(lex.lextable.table[i - 1].lexema == ';' || lex.lextable.table[i - 1].lexema == '}' || lex.lextable.table[i - 1].lexema == '{') &&
				lex.lextable.table[i + 1].lexema != ':') {
				stack<IT::Entry> stackForParams;
				IT::Entry* function = &lex.idtable.table[lex.lextable.table[i].idxTI];
				int iterator = 1;
				while (lex.lextable.table[i + iterator].lexema != '@') {
					stackForParams.push(lex.idtable.table[lex.lextable.table[i + iterator].idxTI]);
					iterator += 1;
				}
				while (!stackForParams.empty()) {
					switch (stackForParams.top().iddatatype) {
					case IT::SYMBOL: {
						*out.stream << "movsx ax, " << stackForParams.top().id << "\n";
						*out.stream << "push ax\n";
						break;
					}
					case IT::INT: {
						*out.stream << "mov ax, " << stackForParams.top().id << "\n";
						*out.stream << "push ax\n";
						break;
					}
					}
					stackForParams.pop();
				}
				*out.stream << "CALL F" << function->id << "\n";

			}
		}
	}

	void Functions(Out::OUT out, MFST::LEX lex) {
		for (int i = 0; i < lex.idtable.size; i++) {
			if (lex.idtable.table[i].idtype == IT::FUNCTION) {
				*out.stream << "\nF" << lex.idtable.table[i].id << " PROC uses ebx ecx edi esi";
				int cur = 1;
				while (lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].lexema != LEX_RIGHTTHESIS) {
					if (lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].lexema == LEX_ID
						&& lex.idtable.table[lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].idxTI].idtype == IT::PARAMETER) {
						*out.stream << ", " << lex.idtable.table[lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].idxTI].id;
						switch (lex.idtable.table[lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].idxTI].iddatatype)
						{
						case IT::INT: {
							*out.stream << " : WORD";
							break;
						}
						case IT::SYMBOL: {
							*out.stream << " : BYTE";
							break;
						}
						}
					}
					cur++;
				}
				*out.stream << "\n";
				int startPos = lex.idtable.table[i].idxfirstLE + cur;
				cout << lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].lexema;
				if (lex.idtable.table[i].iddatatype == IT::INT || lex.idtable.table[i].iddatatype == IT::SYMBOL) {
					while (lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].lexema != LEX_RETURN) {
						cur++;
					}
					cur += 4;
				}
				else {
					cur += 1;
					stack<char>expectedBrace;
					expectedBrace.push(lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].lexema);
					while (!expectedBrace.empty()) {
						cur++;
						if (lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].lexema == '{') {
							expectedBrace.push(lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].lexema);
						}
						if (lex.lextable.table[lex.idtable.table[i].idxfirstLE + cur].lexema == '}') {
							expectedBrace.pop();
						}
					}
					cur += 1;
				}
				int endPos = lex.idtable.table[i].idxfirstLE + cur;
				Expression(out, lex, startPos, endPos);
				*out.stream << "ret\n";
				*out.stream << "F" << lex.idtable.table[i].id << " ENDP\n\n";
			}
		}
	}

	void Code(Out::OUT out, MFST::LEX lex) {
		*out.stream << ".code\n";
		Functions(out, lex);
		*out.stream << "main PROC\n";
		*out.stream << "Invoke SetConsoleCP, 1251\n";
		*out.stream << "Invoke SetConsoleOutputCP, 1251\n";
		int mainPos = 0;
		int endPos = 0;
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].lexema == LEX_MAIN) {
				mainPos = i;
				break;
			}
		}
		endPos = lex.lextable.size ;
		Expression(out, lex, mainPos, endPos);
		*out.stream << "push -1\n";
		*out.stream << "call ExitProcess\n";
		*out.stream << "main ENDP\n";
		*out.stream << "end main\n";

	}

	void GenerateCode(MFST::LEX lex, Out::OUT out) {
		Head(out);
		Const(out, lex);
		Data(out, lex);
		Code(out, lex);
	}

}
