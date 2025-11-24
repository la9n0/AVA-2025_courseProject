#include "stdafx.h"
#include <stack>

#include "LexAnalysis.h"
#include "Error.h"
#include "FST.h"
#include "graphs.h"

using namespace std;

void LexAnalysis(In::IN& in, LT::LexTable& lex, IT::IdTable& id)
{
	IT::IDDATATYPE	iddatatype = IT::IDDATATYPE::DEF;
	IT::IDTYPE	idtype = IT::IDTYPE::D;
	IT::Entry* IT_ENTRY = NULL;

	IT::strcmp.params = IT::Entry::Param{ 2, vector<IT::IDDATATYPE>{IT::IDDATATYPE::STR, IT::IDDATATYPE::STR} };
	IT::Add(id, &IT::strcmp);
	ID_RESET

		char lexema[TI_STR_MAXSIZE];
	int currentRow = 1, currentLex = 0, indexIdTable = 7;
	bool lexID = true, lexComment = false; int main = 0;
	stack<string> areaOfVisibility;
	areaOfVisibility.push(GLOBAL);

	while (FindLexema(in, lexema))
	{
		currentLex++;
		lexID = true;

		switch (*lexema)
		{
		case LEX_NOTEQUALS:
		case LEX_COMPARE:
		case LEX_RIGHTBRACE:
		case LEX_SEMICOLON:
		case LEX_COMMA:
		case LEX_LEFTBRACE:
		case LEX_LEFTHESIS:
		case LEX_RIGHTHESIS:
		case LEX_EQUAL:
		case LEX_MORE:
		case LEX_LESS:
		{
			LT::Add(lex, new LT::Entry(*lexema, currentRow, currentLex));
			lexID = false;
			if (*lexema == LEX_RIGHTBRACE)
				areaOfVisibility.pop();
			break;
		}
		case IN_CODE_VERTICAL_LINE:
			currentRow++;
			currentLex = 0;
			lexID = false;
			if (lexComment)
			{
				lexComment = false;
			}
			break;

		case '#':
		{
			FST::FST fst_comment = FST_COMMENT(lexema);

			if (FST::execute(fst_comment))
			{
				lexComment = true;
			}
			break;
		}

		case 'f':
		{
			FST::FST fst_function = FST_FUNCTION(lexema);
			if (FST::execute(fst_function) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_FUNCTION, currentRow, currentLex));
				idtype = IT::IDTYPE::F;
				lexID = false;
			}
			break;
		}
		case 'u':
		{
			FST::FST fst_uint = FST_UINT(lexema);
			if (FST::execute(fst_uint) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_UINT, currentRow, currentLex));
				iddatatype = IT::IDDATATYPE::UINT;
				lexID = false;
			}
			break;
		}
		case 's':
		{
			FST::FST fst_short = FST_SHORT(lexema);
			if (FST::execute(fst_short) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_SHORT, currentRow, currentLex));
				iddatatype = IT::IDDATATYPE::SHORT;
				lexID = false;
			}
			if (lexID)
			{
				FST::FST fst_str = FST_STR(lexema);
				if (FST::execute(fst_str) && !lexComment)
				{
					LT::Add(lex, new LT::Entry(LEX_STR, currentRow, currentLex));
					iddatatype = IT::IDDATATYPE::STR;
					lexID = false;
				}
			}
			break;
		}
		case 'c':
		{
			FST::FST fst_char = FST_CHAR(lexema);
			if (FST::execute(fst_char) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_CHAR, currentRow, currentLex));
				iddatatype = IT::IDDATATYPE::CHAR;
				lexID = false;
			}
			break;
		}
		case 'b':
		{
			FST::FST fst_bool = FST_BOOL(lexema);
			if (FST::execute(fst_bool) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_BOOL, currentRow, currentLex));
				iddatatype = IT::IDDATATYPE::BOOL;
				lexID = false;
			}
			if (lexID)
			{
				FST::FST fst_literal_bool = FST_LITERAL_BOOL(lexema);
				if (FST::execute(fst_literal_bool) && !lexComment)
				{
					lexID = false;
					int IsLiteralBool = IT::IsLiteralBool(id, lexema);
					if (IsLiteralBool + 1)
						LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, IsLiteralBool));
					else
					{
						LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, indexIdTable++));
						LITERAL_BOOL
							IT::Add(id, new IT::Entry(lex.current_size - 1, iddatatype, idtype, lexema));
						ID_RESET
					}
				}
			}
			break;
		}
		case 'i':
		{

			if (lexID)
			{
				FST::FST fst_if = FST_IF(lexema);
				if (FST::execute(fst_if) && !lexComment)
				{
					LT::Add(lex, new LT::Entry(LEX_IF, currentRow, currentLex));
					lexID = false;
				}
			}
			break;
		}
		case 'm':
		{
			FST::FST fst_main = FST_MAIN(lexema);
			if (FST::execute(fst_main) && !lexComment)
			{
				main++;
				LT::Add(lex, new LT::Entry(LEX_MAIN, currentRow, currentLex));
				areaOfVisibility.push(lexema);
				lexID = false;
			}
			break;
		}
		case 'p':
		{
			FST::FST fst_param = FST_PARAM(lexema);
			if (FST::execute(fst_param) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_PARAM, currentRow, currentLex));
				idtype = IT::IDTYPE::P;

				if (IT_ENTRY)
				{
					IT_ENTRY->params.count++;
					IT_ENTRY->params.types.push_back(iddatatype);
				}

				lexID = false;
			}
			break;
		}

		case 'r':
		{
			FST::FST fst_return = FST_RETURN(lexema);
			if (FST::execute(fst_return) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_RETURN, currentRow, currentLex));
				lexID = false;
			}
			break;
		}
		case 'f':
		{
			FST::FST fst_function = FST_FUNCTION(lexema);
			if (FST::execute(fst_function) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_FUNCTION, currentRow, currentLex));
				idtype = IT::IDTYPE::F;
				lexID = false;
			}
			if (lexID)
			{
				FST::FST fst_for = FST_FOR(lexema);
				if (FST::execute(fst_for) && !lexComment)
				{
					char str[10];
					static int count = 0;
					sprintf(str, "%d", count++);
					LT::Add(lex, new LT::Entry(LEX_FOR, currentRow, currentLex));
					areaOfVisibility.push(strcat(lexema, str));
					lexID = false;
				}
			}
			break;
		}
		case 's':
		{
			FST::FST fst_string = FST_STR(lexema);
			if (FST::execute(fst_string) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_STR, currentRow, currentLex));
				iddatatype = IT::IDDATATYPE::STR;
				lexID = false;
			}
			break;
		}
		case 'v':
		{
			FST::FST fst_var = FST_VAR(lexema);
			if (FST::execute(fst_var) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_VAR, currentRow, currentLex));
				idtype = IT::IDTYPE::V;
				lexID = false;
			}
			break;
		}
		case 'w':
		{
			FST::FST fst_write = FST_WRITE(lexema);
			if (FST::execute(fst_write) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_WRITE, currentRow, currentLex));
				lexID = false;
			}
			break;
		}
		case 't':
		{
			FST::FST fst_write = FST_THEN(lexema);
			if (FST::execute(fst_write) && !lexComment)
			{
				char str[10];
				static int count = 0;
				sprintf(str, "%d", count++);
				LT::Add(lex, new LT::Entry(LEX_THEN, currentRow, currentLex));
				areaOfVisibility.push(strcat(lexema, str));
				lexID = false;
			}
			break;
		}
		case 'e':
		{
			FST::FST fst_write = FST_ELSE(lexema);
			if (FST::execute(fst_write) && !lexComment)
			{
				char str[10];
				static int count = 0;
				sprintf(str, "%d", count++);
				LT::Add(lex, new LT::Entry(LEX_ELSE, currentRow, currentLex));
				areaOfVisibility.push(strcat(lexema, str));
				lexID = false;
			}
			break;
		}
		case '+':
		{
			FST::FST fst_increment = FST_INCREMENT(lexema);
			if (FST::execute(fst_increment) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_INCREMENT, currentRow, currentLex));
				lexID = false;
			}
			break;
		}
		case '-':
		{
			FST::FST fst_decrement = FST_DECREMENT(lexema);
			if (FST::execute(fst_decrement) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_DECREMENT, currentRow, currentLex));
				lexID = false;
			}
			break;
		}
		case '~':
		{
			FST::FST fst_inversion = FST_INVERSION(lexema);
			if (FST::execute(fst_inversion) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_INVERSION, currentRow, currentLex));
				lexID = false;
			}
			break;
		}
		case IN_CODE_QUOTES:
		{
			FST::FST fst_literal_s = FST_LITERAL_S(lexema);
			if (FST::execute(fst_literal_s) && !lexComment)
			{
				lexID = false;
				int IsLiteralString = IT::IsLiteralString(id, lexema);
				if (IsLiteralString + 1)
					LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, IsLiteralString));
				else
				{
					LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, indexIdTable++));

					LITERAL_STR
						IT::Add(id, new IT::Entry(lex.current_size - 1, iddatatype, idtype, lexema));
					ID_RESET
				}
			}
			break;
		}
		case IN_CODE_SINGLE_QUOTE:
		{
			FST::FST fst_literal_c = FST_LITERAL_C(lexema);
			if (FST::execute(fst_literal_c) && !lexComment)
			{
				lexID = false;
				int IsLiteralChar = IT::IsLiteralChar(id, lexema);
				if (IsLiteralChar + 1)
					LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, IsLiteralChar));
				else
				{
					LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, indexIdTable++));

					LITERAL_CHAR
						IT::Add(id, new IT::Entry(lex.current_size - 1, iddatatype, idtype, lexema));
					ID_RESET
				}
			}
			break;
		}
		default:
		{
			break;
		}
		}

		if (lexID && !lexComment)
		{

			FST::FST fst_id = FST_ID(lexema);
			if (FST::execute(fst_id))
			{
				int isId = IT::IsId(id, lexema, areaOfVisibility);
				if (isId + 1)
				{
					if (idtype != IT::IDTYPE::D)
					{
						if (!strcmp(id.table[isId]->areaOfVisibility, areaOfVisibility.top().c_str()))
							throw ERROR_THROW_IN(131, currentRow, currentLex);
						if (iddatatype == IT::IDDATATYPE::DEF)
							throw ERROR_THROW_IN(121, currentRow, currentLex);

						LT::Add(lex, new LT::Entry(LEX_ID, currentRow, currentLex, indexIdTable++));
						IT::Add(id, new IT::Entry(lex.current_size - 1, areaOfVisibility.top(), lexema, iddatatype, idtype));

						ID_RESET
					}
					else
						LT::Add(lex, new LT::Entry(LEX_ID, currentRow, currentLex, isId));
				}
				else
				{
					if (iddatatype == IT::IDDATATYPE::DEF)
						throw ERROR_THROW_IN(121, currentRow, currentLex);
					if (idtype == IT::IDTYPE::D)
						throw ERROR_THROW_IN(132, currentRow, currentLex);

					LT::Add(lex, new LT::Entry(LEX_ID, currentRow, currentLex, indexIdTable++));
					IT::Add(id, new IT::Entry(lex.current_size - 1, areaOfVisibility.top(), lexema, iddatatype, idtype));

					if (idtype == IT::IDTYPE::F)
					{
						areaOfVisibility.push(lexema);
						IT_ENTRY = id.table[id.current_size - 1];
					}

					ID_RESET
				}
			}
			else
				throw ERROR_THROW_IN(120, currentRow, currentLex);
		}
	}

	if (main == 0)
		throw ERROR_THROW(133);
	if (main > 1)
		throw ERROR_THROW(134);
	LT::Add(lex, new LT::Entry('$', currentRow, currentLex));
}

bool FindLexema(In::IN& in, char* lexema)
{
	bool s_literal = false;
	static int i = 0; int indexLexema = 0;
	for (; i < in.size && in.text[i] != IN_CODE_SPACE || s_literal; i++)
	{
		if (indexLexema >= TI_STR_MAXSIZE - 1)
			throw ERROR_THROW(125)

			lexema[indexLexema++] = in.text[i];
		if (in.text[i] == IN_CODE_QUOTES || in.text[i] == IN_CODE_SINGLE_QUOTE)
			s_literal = !s_literal;
	}
	lexema[indexLexema] = TI_STR_DEFAULT;
	i++;

	return indexLexema;
}
