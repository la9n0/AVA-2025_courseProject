#pragma once

#define ERROR_MAXSIZE_MESSAGE 512	
#define ERROR_MAX_ENTRY 1000		

// Диапазоны ошибок по типам
#define ERROR_LEXICAL_START		200
#define ERROR_LEXICAL_END		299
#define ERROR_SYNTAX_START		300
#define ERROR_SYNTAX_END		399
#define ERROR_SEMANTIC_START		400
#define ERROR_SEMANTIC_END		499
#define ERROR_SYNTAX_GRAMMAR_START	600
#define ERROR_SYNTAX_GRAMMAR_END	699

#define ERROR_THROW(id) Error::GetError(id);				
#define ERROR_THROW_IN(id, line, cells) Error::GetError(id, line, cells);	
#define ERROR_ENTRY(id, message) {id, message}

#ifdef ERROR
#undef ERROR
#endif

#define ERROR_ENTRY_NODEF(id)		ERROR_ENTRY(-id, " ")

#define ERROR_ENTRY_NODEF10(id)		ERROR_ENTRY_NODEF(id + 0), ERROR_ENTRY_NODEF(id + 1), \
									ERROR_ENTRY_NODEF(id + 2), ERROR_ENTRY_NODEF(id + 3), \
									ERROR_ENTRY_NODEF(id + 4), ERROR_ENTRY_NODEF(id + 5), \
									ERROR_ENTRY_NODEF(id + 6), ERROR_ENTRY_NODEF(id + 7), \
									ERROR_ENTRY_NODEF(id + 8), ERROR_ENTRY_NODEF(id + 9)
#define ERROR_ENTRY_NODEF100(id)	ERROR_ENTRY_NODEF10(id + 0), ERROR_ENTRY_NODEF10(id + 10),  \
									ERROR_ENTRY_NODEF10(id + 20), ERROR_ENTRY_NODEF10(id + 30), \
									ERROR_ENTRY_NODEF10(id + 40), ERROR_ENTRY_NODEF10(id + 50), \
									ERROR_ENTRY_NODEF10(id + 60), ERROR_ENTRY_NODEF10(id + 70), \
									ERROR_ENTRY_NODEF10(id + 80), ERROR_ENTRY_NODEF10(id + 90)

namespace Error
{
	struct ERROR
	{
		int id;
		char message[ERROR_MAXSIZE_MESSAGE];

		struct IN
		{
			short line;
			short col;
		} position;
	};

	ERROR GetError(int id);
	ERROR GetError(int id, int line, int cells);
}