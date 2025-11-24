#pragma once

#define LEXEMA_FIXSIZE	1
#define	LT_MAXSIZE		4096
#define	LT_TI_NULLXDX	-1
#define	LT_V_NULL		'?'


#define	LEX_UINT		'u'
#define	LEX_SHORT		's'
#define	LEX_CHAR		'c'
#define	LEX_BOOL		'b'
#define	LEX_STR			't'
#define	LEX_ID			'i'
#define	LEX_LITERAL		'l'
#define	LEX_FUNCTION	'f'
#define	LEX_PARAM		'p'
#define	LEX_VAR			'v'
#define	LEX_FOR			'F'
#define	LEX_RETURN		'r'
#define	LEX_WRITE		'w'
#define	LEX_MAIN		'm'
#define	LEX_SEMICOLON	';'
#define	LEX_COMMA		','
#define	LEX_LEFTBRACE	'{'
#define	LEX_RIGHTBRACE	'}'
#define	LEX_LEFTHESIS	'('
#define	LEX_RIGHTHESIS	')'
#define	LEX_INCREMENT	'+'
#define	LEX_DECREMENT	'-'
#define	LEX_INVERSION	'~'
#define	LEX_EQUAL		'='
#define	LEX_MORE		'>'
#define	LEX_LESS		'<'
#define	LEX_COMPARE		'&'
#define	LEX_NOTEQUALS	'^'
#define	LEX_IF			'?'
#define LEX_THEN		':'
#define LEX_ELSE		'!'
#define LEX_COMMENT		'@'

#define PARM_LEX_DEFAULT_LOCATION	L"D:\\university\\3_sem\\kpo\\kurs_project\\AVA-2025\\Debug\\Files\\"
#define PARM_LEX_DEFAULT_EXT		L".lex.txt"

namespace LT
{
	struct Entry
	{
		char lexema;
		char sign;
		int sn;
		int tn;
		int idxTI;

		Entry(char lexema, int sn, int tn, int idxTI);
		Entry(char lexema, char sign, int sn, int tn);
		Entry(char lexema, int sn, int tn);
		Entry(char lexema);
	};

	struct LexTable
	{
		int maxsize;
		int current_size;
		Entry** table;

		LexTable();
		LexTable(int size);
	};
	void Add(LexTable& lextable, Entry* entry);
	Entry GetEntry(LexTable& lextable, int n);
	void PrintLexTable(LexTable& lextable, const wchar_t* in);
	void Delete(LexTable& lextable);
}
