#pragma once
#include "LT.h"
#include "IT.h"
#include "In.h"
#include "Log.h"
#include "FST.h"

#define TYPE_DIGIT		"number"
#define TYPE_STRING		"line"
#define TYPE_CHAR		"char"
#define TYPE_VOID		"proc"
#define CONCAT			"concat"
#define POW				"poww"
#define COMPARE			"compare"
#define RANDOM			"rnd"
#define ATOII			"atoii"
#define MAIN			"main"
#define LENGHT			"slength"
#define COPY			"copystr"


#define ISTYPE(str) ( !strcmp(str, TYPE_DIGIT) || !strcmp(str, TYPE_STRING)|| !strcmp(str, TYPE_CHAR) )

namespace Lexer
{
	struct LEX
	{
		LT::LexTable lextable;
		IT::IdTable	idtable;
		LEX() {}
	};
	struct Graph
	{
		char lexema;
		FST::FST graph;
	};

	IT::Entry* getEntry		// формирует и возвращает строку ТИ
	(
		Lexer::LEX& tables,						// ТЛ + ТИ
		char lex,								// лексема
		char* id,								// идентификатор
		char* idtype,							// предыдущая (тип)
		bool isParam,							// признак параметра функции
		bool isFunc,							// признак функции
		Log::LOG log,							// протокол
		int line,								// строка в исходном тексте
		bool& rc_err							// флаг ошибки(по ссылке)
	);

	struct ERROR_S									// тип исключения для throw ERROR_THROW | ERROR_THROW_IN
	{
		int id;
		char message[ERROR_MAXSIZE_MESSAGE];			// сообщение			
		struct
		{
			short line = -1;						//номер строки (0, 1, 2, ...)
			short col = -1;						//номер позиции в строке(0, 1, 2, ...)
		} position;
	};
	bool analyze(LEX& tables, In::IN& in, Log::LOG& log, Parm::PARM& parm);
	int	getIndexInLT(LT::LexTable& lextable, int itTableIndex);					// индекс первой встречи в таблице лексем
};

