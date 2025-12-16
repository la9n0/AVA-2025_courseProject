#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include "Header.h"

int wmain(int argc, wchar_t* argv[])
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	char LEXERROR[] = "Лексическая ошибка при открытии файла";
	char SYNTERROR[] = "Синтаксический анализ завершился с ошибками";
	char SEMERROR[] = "Произошла семантическая ошибка";
	char POLISHERROR[] = "Ошибка при генерации польской записи";
	char LEXGOOD[] = "Лексическая проверка пройдена без ошибок";
	char SYNTGOOD[] = "Синтаксическая проверка пройдена без ошибок";
	char SEMGOOD[] = "Семантическая проверка пройдена без ошибок";
	char POLISHGOOD[] = "Генерация польской записи прошла без ошибок";
	char MESSAGE[] = "--------------------Повторный вывод таблиц и идентификаторов-------------------";
	char STOP[] = "\nРабота программы завершена";
	char ALLGOOD[] = "Сборка завершена успешно!";
	setlocale(LC_ALL, ".UTF-8");
	Log::LOG log;

	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getstream(parm.log);
		Log::writeLog(log);
		Log::writeParm(log, parm);
		In::IN in = In::getin(parm.in, log.stream);
		Log::writeIn(log.stream, in);

		in.words = In::getWordsTable(log.stream, in.text, in.code, in.size);
		Lexer::LEX tables;
		bool lex_ok = Lexer::analyze(tables, in, log, parm);
		LT::writeLexTable(log.stream, tables.lextable);
		IT::writeIdTable(log.stream, tables.idtable);
		LT::writeLexemsOnLines(log.stream, tables.lextable);
		if (!lex_ok)
		{
			Log::writeLine(log.stream, LEXERROR, "");
			Log::writeLine(&std::cout, LEXERROR, STOP, "");
			return 0;
		}
		else
		{
			Log::writeLine(&std::cout, LEXGOOD, "");
		}
		MFST_TRACE_START(log.stream);
		MFST::Mfst mfst(tables, GRB::getGreibach());
		bool synt_ok = mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);
		if (!synt_ok)
		{
			Log::writeLine(log.stream, SYNTERROR, "");
			Log::writeLine(&std::cout, SYNTERROR, STOP, "");
			return 0;
		}
		else Log::writeLine(&std::cout, SYNTGOOD, "");
		bool sem_ok = Semantic::semanticsCheck(tables, log);
		if (!sem_ok)
		{
			Log::writeLine(log.stream, SEMERROR, "");
			Log::writeLine(&std::cout, SEMERROR, STOP, "");
			return 0;
		}
		else Log::writeLine(&std::cout, SEMGOOD, "");
		bool polish_ok = Polish::PolishNotation(tables, log);
		if (!polish_ok)
		{
			Log::writeLine(log.stream, POLISHERROR, "");
			Log::writeLine(&std::cout, POLISHERROR, STOP, "");
			return 0;
		}
		else Log::writeLine(&std::cout, POLISHGOOD, "");
		Log::writeLine(log.stream, MESSAGE, "");
		LT::writeLexTable(log.stream, tables.lextable);
		IT::writeIdTable(log.stream, tables.idtable);
		LT::writeLexemsOnLines(log.stream, tables.lextable);

		Gener::CodeGeneration(tables, parm, log);
	}
	catch (Error::ERROR e)
	{
		std::ostringstream oss;
		oss << "Ошибка " << e.id << ": " << e.message
			<< ", строка " << e.position.line
			<< ", столбец " << e.position.col;
		Log::printConsoleUtf8(oss.str().c_str());
		Log::printConsoleUtf8("\n");
		system("pause");
	}
	return 0;
}
