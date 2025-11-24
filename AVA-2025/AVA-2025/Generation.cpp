#include "stdafx.h"
#include <vector>
#include <stack>
#include <sstream>
#include "Generation.h"

using namespace std;

namespace GN
{
	void GenerationASM(std::ostream* stream, LT::LexTable& lextable, IT::IdTable& idtable)
	{
		ostream* file = stream;
		*file << BEGIN;
		*file << EXTERN;
		*file << STACK(4096);
		GenConstAndData(idtable, file);
		*file << CODE;
		GenCode(lextable, idtable, file);
		*file << END;
	}

	void GenConstAndData(IT::IdTable& idtable, ostream* file)
	{
		vector <string> result;
		vector <string> con;  con.push_back(CONST);
		vector <string> data;  data.push_back(DATA);

		for (int i = 0; i < idtable.current_size; i++)
		{
			string str = "\t" + idtable.table[i]->FullName;

			if (idtable.table[i]->idtype == IT::IDTYPE::L)
			{
			switch (idtable.table[i]->iddatatype)
			{
			case IT::IDDATATYPE::UINT:  str += " dword " + itoS(idtable.table[i]->value.vuint);  break;
			case IT::IDDATATYPE::SHORT:  str += " word " + itoS(idtable.table[i]->value.vshort);  break;
			case IT::IDDATATYPE::CHAR:  str += " byte " + itoS((int)idtable.table[i]->value.vchar);  break;
			case IT::IDDATATYPE::BOOL:  str += " byte " + itoS(idtable.table[i]->value.vbool ? 1 : 0);  break;
			case IT::IDDATATYPE::STR:  str += " byte " + string(idtable.table[i]->value.vstr.str) + ", 0";  break;
			}
				con.push_back(str);
			}
			else if (idtable.table[i]->idtype == IT::IDTYPE::V)
			{
				switch (idtable.table[i]->iddatatype)
				{
				case IT::IDDATATYPE::UINT: str += " dword 0";  break;
				case IT::IDDATATYPE::SHORT: str += " word 0";  break;
				case IT::IDDATATYPE::CHAR: str += " byte 0";  break;
				case IT::IDDATATYPE::BOOL: str += " byte 0";  break;
				case IT::IDDATATYPE::STR: str += " dword ?";  break;
				}
				data.push_back(str);
			}
		}
		result.insert(result.end(), con.begin(), con.end());
		result.insert(result.end(), data.begin(), data.end());
		for (auto r : result)
			*file << r << endl;
	}

	void GenCode(LT::LexTable& lextable, IT::IdTable& idtable, ostream* file)
	{
		string str;
		string funcName;
		int branchingnNum = -1, open = 0;
		stack<A> kol;

		for (int i = 0; i < lextable.current_size; i++)
		{
			switch (LT_ENTRY(i)->lexema)
			{
			case LEX_MAIN:
			{
				str = SEPSTR("MAIN") + "main PROC\n";
				break;
			}
			case LEX_FUNCTION:
			{
				funcName = IT_ENTRY(i + 1)->FullName;
				str = GenFunctionCode(lextable, idtable, i);
				break;
			}
			case LEX_RETURN:
			{
				str = GenExitCode(lextable, idtable, i, funcName);
				break;
			}
			case LEX_ID:
			{
				if (LT_ENTRY(i + 1)->lexema == LEX_LEFTHESIS && LT_ENTRY(i + 1)->lexema != LEX_FUNCTION)
					str = GenCallFuncCode(lextable, idtable, i);
				break;
			}
			case LEX_IF:
			{
				branchingnNum++;
				str = GenBranchingCode(lextable, idtable, i, branchingnNum);
				break;
			}
			case LEX_LEFTBRACE:
			{
				open++;
				break;
			}
			case LEX_RIGHTBRACE:
			{
				open--;
				if (LT_ENTRY(i + 1)->lexema == LEX_ELSE)
				{
					kol.pop();
					kol.push(A(open, branchingnNum, IfEnum::thenOrElse));
					str += "jmp next" + itoS(kol.top().branchingnNum) + '\n';
				}
				else
					if (!kol.empty())
						if (kol.top().openRightbrace == open)
						{
							if (kol.top().ifEnum == IfEnum::repeat)
							{
								str += "jmp cyclenext" + itoS(kol.top().branchingnNum) + '\n';
								str += "cycle" + itoS(kol.top().branchingnNum) + ":\n";
								kol.pop();
							}
							else
							{
								str += "next" + itoS(kol.top().branchingnNum) + ":\n";
								kol.pop();
							}
						}
				break;
			}
			case LEX_THEN:
			{
				kol.push(A(open, branchingnNum, IfEnum::thenOrElse));
				str += "true" + itoS(branchingnNum) + ":";
				break;
			}
			case LEX_ELSE:
			{
				str += "false" + itoS(branchingnNum) + ":";
				break;
			}
			case LEX_FOR:
			{
				branchingnNum++;
				kol.push(A(open, branchingnNum, IfEnum::repeat));
				str += "cyclenext" + itoS(kol.top().branchingnNum) + ":\n";
				str += GenBranchingCode(lextable, idtable, i, kol.top().branchingnNum);

				break;
			}
			case LEX_EQUAL:
			{
				PN::polishNotation(i, lextable, idtable);
				str = GenEqualCode(lextable, idtable, i);
				break;
			}
			case LEX_WRITE:
			{
				IT::Entry* e = IT_ENTRY(i + 1);
				switch (e->iddatatype)
				{
				case IT::IDDATATYPE::UINT:
					str += "push " + string(e->FullName) + "\ncall write_uint\n";
					break;
				case IT::IDDATATYPE::SHORT:
					str += "push " + string(e->FullName) + "\ncall write_short\n";
					break;
				case IT::IDDATATYPE::CHAR:
					str += "push " + string(e->FullName) + "\ncall write_char\n";
					break;
				case IT::IDDATATYPE::BOOL:
					str += "push " + string(e->FullName) + "\ncall write_bool\n";
					break;
				case IT::IDDATATYPE::STR:
					if (e->idtype == IT::IDTYPE::L)  str += "\npush offset " + string(e->FullName) + "\ncall write_str\n";
					else  str += "push " + string(e->FullName) + "\ncall write_str\n";
					break;
				}
				break;
			}

			}

			if (!str.empty())
			{
				*file << str << endl;
				str.clear();
			}
		}
	}

	string GenEqualCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i)
	{
		string str;
		IT::Entry* e1 = IT_ENTRY(i - 1);
		i++;
		switch (e1->iddatatype)
		{
		case IT::IDDATATYPE::UINT:
		case IT::IDDATATYPE::SHORT:
		case IT::IDDATATYPE::CHAR:
		case IT::IDDATATYPE::BOOL:
		{
			for (; LT_ENTRY(i)->lexema != LEX_SEMICOLON; i++)
			{
				switch (LT_ENTRY(i)->lexema)
				{
				case LEX_LITERAL:
				case LEX_ID:
				{
					if (IT_ENTRY(i)->idtype == IT::IDTYPE::F)
					{
						str = str + GenCallFuncCode(lextable, idtable, i);
						str = str + "push eax\n";
						break;
					}
					else
						str = str + "push " + IT_ENTRY(i)->FullName + "\n";
					break;
				}
				case LEX_INCREMENT:
					str += "pop eax\ninc eax\npush eax\n"; break;
				case LEX_DECREMENT:
					str += "pop eax\ndec eax\npush eax\n"; break;
				case LEX_INVERSION:
					str += "pop eax\nnot eax\npush eax\n"; break;
				}
			}

			str += "pop " + string(e1->FullName) + '\n';
			break;
		}
		case IT::IDDATATYPE::STR:
		{
			char lex = LT_ENTRY(i)->lexema;
			IT::Entry* e2 = IT_ENTRY(i);
			if (lex == LEX_ID && (e2->idtype == IT::IDTYPE::F))
			{
				str += GenCallFuncCode(lextable, idtable, i);
				str += "mov " + string(e1->FullName) + ", eax";
			}
			else if (lex == LEX_LITERAL)
			{
				str = +"mov " + string(e1->FullName) + ", offset " + string(e2->FullName);
			}
			else
			{
				str += "mov ecx, " + string(e2->FullName) + "\nmov " + string(e1->FullName) + ", ecx";
			}
		}
		}
		return str;
	}

	string GenFunctionCode (LT::LexTable& lextable, IT::IdTable& idtable, int& i)
	{
		string str = "";

		str += SEPSTR(IT_ENTRY(i + 1)->FullName) + string(IT_ENTRY(i + 1)->FullName) + string(" PROC,\t");
		i += 3;

		while (LT_ENTRY(i)->lexema != LEX_RIGHTHESIS)
		{
			if (LT_ENTRY(i)->lexema == LEX_ID)
			{
				IT::IDDATATYPE dtype = IT_ENTRY(i)->iddatatype;
				if (dtype == IT::IDDATATYPE::UINT)
					str += string(IT_ENTRY(i)->FullName) + " : dword, ";
				else if (dtype == IT::IDDATATYPE::SHORT)
					str += string(IT_ENTRY(i)->FullName) + " : word, ";
				else if (dtype == IT::IDDATATYPE::CHAR || dtype == IT::IDDATATYPE::BOOL)
					str += string(IT_ENTRY(i)->FullName) + " : byte, ";
				else
					str += string(IT_ENTRY(i)->FullName) + " : dword, ";
			}
			i++;
		}
		int f = str.rfind(',');
		if (f > 0)
			str[f] = ' ';

		str += "\npush ebx\npush edx\n";

		return str;
	}

	string GenExitCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i, string funcname)
	{
		string str = "\npop edx\npop ebx\n";
		if (LT_ENTRY(i + 1)->lexema != LEX_SEMICOLON)
		{
			str += "mov eax, " + string(IT_ENTRY(i + 1)->FullName) + "\n";
		}
		str += "ret\n";
		str += funcname + " ENDP" + SEPSTREMP;
		return str;
	}

	string GenCallFuncCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i)
	{
		string str;

		IT::Entry* e = IT_ENTRY(i);
		stack <IT::Entry*> temp;

		for (i++; LT_ENTRY(i)->lexema != '@'; i++)
		{
			if (LT_ENTRY(i)->lexema == LEX_ID || LT_ENTRY(i)->lexema == LEX_LITERAL)
				temp.push(IT_ENTRY(i));
		}

		while (!temp.empty())
		{
			if (temp.top()->idtype == IT::IDTYPE::L && temp.top()->iddatatype == IT::IDDATATYPE::STR)
				str += "push offset " + string(temp.top()->FullName) + "\n";
			else   str += "push " + string(temp.top()->FullName) + "\n";
			temp.pop();
		}

		str += "call " + string(e->FullName) + '\n';
		i++;

		return str;
	}

	string GenBranchingCode(LT::LexTable& lextable, IT::IdTable& idtable, int& i, int branchingnNum)
	{
		string str;
		IT::Entry* lft = IT_ENTRY(i + 2);
		IT::Entry* rgt = IT_ENTRY(i + 4);
		bool f = false, t = false;
		string fstr, tstr;

		str += "mov edx, " + lft->FullName + "\ncmp edx, " + rgt->FullName + "\n";
		switch (LT_ENTRY(i + 3)->lexema)
		{
		case LEX_MORE:  tstr = "jg";  fstr = "jl";  break;
		case LEX_LESS:   tstr = "jl";  fstr = "jg";  break;
		case LEX_COMPARE: tstr = "jz";  fstr = "jnz";  break;
		case LEX_NOTEQUALS:   tstr = "jnz";  fstr = "jz";  break;
		}

		if (LT_ENTRY(i)->lexema != LEX_FOR)
		{
			for (int j = i + 6; LT_ENTRY(j - 2)->lexema != LEX_RIGHTBRACE; j++)
			{
				if (LT_ENTRY(j)->lexema == LEX_THEN)
					t = true;
				if (LT_ENTRY(j)->lexema == LEX_ELSE)
					f = true;
			}
			if (t) str += "\n" + tstr + " true" + itoS(branchingnNum);
			if (f) str += "\n" + fstr + " false" + itoS(branchingnNum);
			if (!t || !f)  str = str + "\njmp next" + itoS(branchingnNum);
		}
		else
		{
			str += fstr + " cycle" + itoS(branchingnNum);
		}

		return str;
	}

	string itoS(int x)
	{
		stringstream r;  r << x;  return r.str();
	}
}

