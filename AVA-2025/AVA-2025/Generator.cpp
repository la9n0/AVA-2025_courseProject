#include "Generator.h"
#include "Parm.h"
#include "Lexer.h"
#include "IT.h"
#include "LT.h"
#include <sstream>
#include <cstring>
#include <iosfwd>
#include <fstream>
#include <stack>
#include <vector>
#include <locale>
#include <codecvt>

#ifndef LEX_INC
#define LEX_INC 'u'
#endif
#ifndef LEX_DEC
#define LEX_DEC 'v'
#endif
#ifndef LEX_INV
#define LEX_INV 'x'
#endif

using namespace std;


namespace Gener
{
	static int conditionnum = 0;
	string numberOfPoints = "k";
	string itoS(int x) { stringstream r;  r << x;  return r.str(); }

	string genCallFuncCode(Lexer::LEX& tables, Log::LOG& log, int i)
	{
		string str;
		IT::Entry e = ITENTRY(i);
		stack <IT::Entry> temp;
		bool stnd = (e.idtype == IT::IDTYPE::S);

		for (int j = i + 1; LEXEMA(j) != LEX_RIGHTTHESIS; j++)
		{
			if (LEXEMA(j) == LEX_ID || LEXEMA(j) == LEX_LITERAL)
				temp.push(ITENTRY(j));
		}
		str += "\n";
		while (!temp.empty())
		{
			IT::Entry entry = temp.top();
			if (entry.idtype == IT::IDTYPE::L && (entry.iddatatype == IT::IDDATATYPE::STR || entry.iddatatype == IT::IDDATATYPE::SYMBOL))
				str = str + "push offset " + string(entry.id) + "\n";
			else if (entry.iddatatype == IT::IDDATATYPE::INT)
			{
				if (entry.idtype == IT::IDTYPE::L)
					str = str + "movzx eax, word ptr " + string(entry.id) + "\npush eax\n";
				else
					str = str + "movzx eax, word ptr " + string(entry.id) + "\npush eax\n";
			}
			else
				str = str + "push " + string(entry.id) + "\n";
			temp.pop();
		}
		if (stnd)
			str += "push offset buffer\n";
		str = str + "call " + string(e.id) + IN_CODE_ENDL;
		return str;
	}

	string genEqualCode(Lexer::LEX& tables, Log::LOG& log, int i)
	{
		string str;
		IT::Entry e1 = ITENTRY(i - 1);
		switch (e1.iddatatype)
		{
		case IT::IDDATATYPE::INT:
		{
			bool first = true;
			for (int j = i + 1; LEXEMA(j) != LEX_SEPARATOR; j++)
			{
				switch (LEXEMA(j))
				{
				case LEX_LITERAL:
				case LEX_ID:
				{
					if (ITENTRY(j).idtype == IT::IDTYPE::F || ITENTRY(j).idtype == IT::IDTYPE::S)
					{
						str = str + genCallFuncCode(tables, log, j);
						str = str + "push eax\n";
						while (LEXEMA(j) != LEX_RIGHTTHESIS) j++;
						break;
					}
					else
					{
						IT::Entry entry = ITENTRY(j);
						if (entry.iddatatype == IT::IDDATATYPE::INT)
							str = str + "movzx eax, word ptr " + string(entry.id) + "\npush eax\n";
						else
							str = str + "push " + string(entry.id) + "\n";
					}
					break;
				}
				case LEX_PLUS:
					str = str + "pop ebx\npop eax\nadd eax, ebx\npush eax\n"; break;
				case LEX_MINUS:
					str = str + "pop ebx\npop eax\nsub eax, ebx\njnc b" + numberOfPoints + "\n" + "neg eax\n" + "b" + numberOfPoints + ": \n" + "push eax\n"; numberOfPoints = numberOfPoints + "m"; break;
				case LEX_STAR:
					str = str + "pop ebx\npop eax\nimul eax, ebx\npush eax\n"; break;
				case LEX_DIRSLASH:
					str = str + "pop ebx\npop eax\ncdq\nidiv ebx\npush eax\n"; break;
				case LEX_PERSENT:
					str = str + "pop ebx\npop eax\ncdq\nmov edx,0\nidiv ebx\npush edx\n"; break;
				case LEX_RIGHT:
					str = str + "pop ebx \npop eax \nmov cl, bl \nshr eax, cl\npush eax\n"; break;
				case LEX_LEFT:
					str = str + "pop ebx \npop eax \nmov cl, bl \nshl eax, cl\npush eax\n"; break;
				}
			}

			str = str + "\npop eax\nmov word ptr " + e1.id + ", ax\n";
			break;
		}
		case IT::IDDATATYPE::STR:
		{
			char lex = LEXEMA(i + 1);
			IT::Entry e2 = ITENTRY(i + 1);
			if (lex == LEX_ID && (e2.idtype == IT::IDTYPE::F || e2.idtype == IT::IDTYPE::S))
			{
				str += genCallFuncCode(tables, log, i + 1);
				str = str + "mov " + e1.id + ", eax";
			}
			else if (lex == LEX_LITERAL)
			{
				str = str + "mov " + e1.id + ", offset " + e2.id;
			}
			else
			{
				str = str + "mov ecx, " + e2.id + "\nmov " + e1.id + ", ecx";
			}
			break;
		}
		case IT::IDDATATYPE::SYMBOL:
		{
			char lex = LEXEMA(i + 1);
			IT::Entry e2 = ITENTRY(i + 1);
			if (lex == LEX_ID && (e2.idtype == IT::IDTYPE::F || e2.idtype == IT::IDTYPE::S))
			{
				str += genCallFuncCode(tables, log, i + 1);
				str = str + "mov " + e1.id + ", eax";
			}
			else if (lex == LEX_LITERAL)
			{
				str = str + "mov " + e1.id + ", offset " + e2.id;
			}
			else
			{
				str = str + "mov ecx, " + e2.id + "\nmov " + e1.id + ", ecx";
			}
			break;
		}
		}
		return str;
	}

	string genFunctionCode(Lexer::LEX& tables, int i, string funcname, int pcount)
	{
		string str;
		IT::Entry e = ITENTRY(i + 1);
		IT::IDDATATYPE type = e.iddatatype;
		str = SEPSTR(funcname) + string(e.id) + string(" PROC,\n\t");
		int j = i + 3;
		while (LEXEMA(j) != LEX_RIGHTTHESIS)
		{
			if (LEXEMA(j) == LEX_ID)
			{
				IT::Entry param = ITENTRY(j);
				if (param.iddatatype == IT::IDDATATYPE::INT)
					str = str + string(param.id) + " : word, ";
				else
					str = str + string(param.id) + " : dword, ";
			}
			j++;
		}
		int f = str.rfind(',');
		if (f > 0)
			str[f] = IN_CODE_SPACE;
		str += "\n; --- save registers ---\npush ebx\npush edx\npush ecx\n; ----------------------";
		return str;
	}

	string genExitCode(Lexer::LEX& tables, int i, string funcname, int pcount)
	{
		string str = "; --- restore registers ---\npop ecx\npop edx\npop ebx\n; -------------------------\n";
		if (LEXEMA(i + 1) != LEX_SEPARATOR)
		{
			IT::Entry entry = ITENTRY(i + 1);
			if (entry.iddatatype == IT::IDDATATYPE::INT)
				str = str + "movzx eax, word ptr " + string(entry.id) + "\n";
			else
				str = str + "mov eax, " + string(entry.id) + "\n";
		}
		str += "ret\n";
		str += funcname + " ENDP" + SEPSTREMP;
		return str;
	}

	vector <string> startFillVector(Lexer::LEX& tables)
	{
		vector <string> v;
		v.push_back(BEGIN);
		v.push_back(EXTERN);
		vector <string> vlt;  vlt.push_back(CONST);
		vector <string> vid;  vid.push_back(DATA);
		for (int i = 0; i < tables.idtable.size; i++)
		{
			IT::Entry e = tables.idtable.table[i];
			string str = "\t\t" + string(e.id);

			if (tables.idtable.table[i].idtype == IT::IDTYPE::L)
			{
				switch (e.iddatatype)
				{
				case IT::IDDATATYPE::INT:  str = str + " word " + itoS(e.value.vint);  break;
				case IT::IDDATATYPE::STR:  str = str + " byte '" + string(e.value.vstr.str) + "', 0";  break;
				case IT::IDDATATYPE::SYMBOL:  str = str + " byte '" + string(e.value.vstr.str) + "', 0";  break;
				}
				vlt.push_back(str);
			}
			else if (tables.idtable.table[i].idtype == IT::IDTYPE::V)
			{
				switch (e.iddatatype)
				{
				case IT::IDDATATYPE::INT: str = str + " word 0";  break;
				case IT::IDDATATYPE::STR: str = str + " dword ?";  break;
				case IT::IDDATATYPE::SYMBOL: str = str + " dword ?";  break;
				}
				vid.push_back(str);
			}
		}
		v.insert(v.end(), vlt.begin(), vlt.end());
		v.insert(v.end(), vid.begin(), vid.end());
		v.push_back(CODE);
		return v;
	}

	void CodeGeneration(Lexer::LEX& tables, Parm::PARM& parm, Log::LOG& log)
	{
		vector <string> v = startFillVector(tables);
		ofstream ofile;
		ofile.open(parm.out, std::ios::out);
		string funcname;
		int pcount;
		string str;
		std::stack<bool> braceIsLoop;
		std::stack<std::pair<string, string>> loopLabels;
		bool pendingLoop = false;

		for (int i = 0; i < tables.lextable.size; i++)
		{
			switch (LEXEMA(i))
			{
			case LEX_MAIN:
			{
				str = str + SEPSTR("MAIN") + "main PROC\n";
				// Инициализация стека для main
				str = str + "push ebp\nmov ebp, esp\n";
				break;
			}
			case LEX_FUNCTION:
			{
				funcname = ITENTRY(i + 1).id;
				pcount = ITENTRY(i + 1).value.params.count;
				str = genFunctionCode(tables, i, funcname, pcount);
				break;
			}
			case LEX_RETURN:
			{
				str = genExitCode(tables, i, funcname, pcount);
				break;
			}
			case LEX_ID:
			{
				if (LEXEMA(i + 1) == LEX_LEFTHESIS && LEXEMA(i - 1) != LEX_FUNCTION)
					str = genCallFuncCode(tables, log, i);
				break;
			}
			case LEX_CYCLE:
			{
				conditionnum++;
				string start = "cycle" + itoS(conditionnum);
				string finish = "cycle_end" + itoS(conditionnum);
				loopLabels.push({ start, finish });
				pendingLoop = true;
				IT::Entry cnt = ITENTRY(i + 1);
				string src = cnt.idtype == IT::IDTYPE::L ? ("word ptr " + string(cnt.id)) : string(cnt.id);
				str = "movzx ecx, " + src + "\ncmp ecx, 0\njz " + finish + "\n" + start + ":\n";
				break;
			}
			case LEX_BRACELET:
			{
				bool isLoopBrace = false;
				if (!braceIsLoop.empty())
				{
					isLoopBrace = braceIsLoop.top();
					braceIsLoop.pop();
				}
				if (isLoopBrace && !loopLabels.empty())
				{
					auto lb = loopLabels.top(); loopLabels.pop();
					str = str + "dec ecx\ncmp ecx, 0\njnz " + lb.first + "\n" + lb.second + ":\n";
					pendingLoop = false;
				}
				break;
			}
			case LEX_EQUAL:
			{
				str = genEqualCode(tables, log, i);
				while (LEXEMA(++i) != LEX_SEPARATOR);
				break;
			}
			case LEX_NEWLINE:
			{
				if (pendingLoop || !loopLabels.empty())
					str = str + "mov saveecx, ecx\npush offset newline\ncall outrad\nmov ecx, saveecx\n";
				else
					str = str + "push offset newline\ncall outrad\n";
				break;
			}
			case LEX_WRITE:
			{
				IT::Entry e = ITENTRY(i + 1);
				bool inLoop = (pendingLoop || !loopLabels.empty());
				switch (e.iddatatype)
				{
				case IT::IDDATATYPE::INT:
					if (inLoop)
						str = str + "mov saveecx, ecx\nmovzx eax, word ptr " + string(e.id) + "\npush eax\ncall outlich\nmov ecx, saveecx\n";
					else
						str = str + "\nmovzx eax, word ptr " + string(e.id) + "\npush eax\ncall outlich\n";
					break;
				case IT::IDDATATYPE::STR:
					if (inLoop)
					{
						if (e.idtype == IT::IDTYPE::L)  str = str + "mov saveecx, ecx\npush offset " + e.id + "\ncall outrad\nmov ecx, saveecx\n";
						else  str = str + "mov saveecx, ecx\npush " + e.id + "\ncall outrad\nmov ecx, saveecx\n";
					}
					else
					{
						if (e.idtype == IT::IDTYPE::L)  str = str + "\npush offset " + e.id + "\ncall outrad\n";
						else  str = str + "\npush " + e.id + "\ncall outrad\n";
					}
					break;
				case IT::IDDATATYPE::SYMBOL:
					if (inLoop)
					{
						if (e.idtype == IT::IDTYPE::L)  str = str + "mov saveecx, ecx\npush offset " + e.id + "\ncall outrad\nmov ecx, saveecx\n";
						else  str = str + "mov saveecx, ecx\npush " + e.id + "\ncall outrad\nmov ecx, saveecx\n";
					}
					else
					{
						if (e.idtype == IT::IDTYPE::L)  str = str + "\npush offset " + e.id + "\ncall outrad\n";
						else  str = str + "\npush " + e.id + "\ncall outrad\n";
					}
					break;
				}
				break;
			}
			case LEX_INC:
			{
				IT::Entry e = ITENTRY(i + 1);
				str = str + "inc word ptr " + string(e.id) + "\n";
				break;
			}
			case LEX_DEC:
			{
				IT::Entry e = ITENTRY(i + 1);
				str = str + "dec word ptr " + string(e.id) + "\n";
				break;
			}
			case LEX_INV:
			{
				IT::Entry e = ITENTRY(i + 1);
				str = str + "neg word ptr " + string(e.id) + "\n";
				break;
			}
			case LEX_LEFTBRACE:
			{
				braceIsLoop.push(pendingLoop);
				break;
			}
			}
			if (!str.empty())
				v.push_back(str);
			str.clear();
		}
		v.push_back(END);
		for (auto x : v)
			ofile << x << endl;
		ofile.flush();
		ofile.close();
	}
}
