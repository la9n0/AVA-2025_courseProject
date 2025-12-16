#include "Error.h"
#include "Parm.h"
#include "In.h"
#include "Log.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <windows.h>

#ifdef IN
#undef IN
#endif
#ifdef OUT
#undef OUT
#endif
#ifdef ERROR
#undef ERROR
#endif

#pragma warning(disable : 4996)

#define W(x, y)  << std::setw(x) << (y) <<
#define STR(n, line, type, id)\
	"|" W(4,n) " |  " W(5,line) "    |" W(17,type) " |  " W(SCOPED_ID_MAXSIZE, id) " |"


namespace Log
{
	std::wstring utf8ToWide(const char* text)
	{
		if (!text) return std::wstring();
		int wlen = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
		if (wlen <= 0) return std::wstring();
		std::wstring wstr(wlen - 1, L'\0');
		MultiByteToWideChar(CP_UTF8, 0, text, -1, &wstr[0], wlen);
		return wstr;
	}

	std::string wideToUtf8(const wchar_t* wstr)
	{
		if (!wstr) return std::string();
		int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
		if (len <= 0) return std::string();
		std::vector<char> buf(len, '\0');
		int written = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buf.data(), len, nullptr, nullptr);
		if (written <= 0) return std::string();
		return std::string(buf.data());
	}

	void printConsoleUtf8(const char* text)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		if (h == INVALID_HANDLE_VALUE || h == NULL) return;
		std::wstring wstr = utf8ToWide(text);
		if (wstr.empty()) return;
		DWORD written = 0;
		WriteConsoleW(h, wstr.c_str(), static_cast<DWORD>(wstr.size()), &written, NULL);
	}

	LOG getstream(wchar_t  logfile[])
	{
		LOG stream;
		stream.stream = new std::ofstream;
		stream.stream->open(logfile, std::ios::binary);
		if (!stream.stream->is_open())
			throw ERROR_THROW(103);
		const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
		stream.stream->write(reinterpret_cast<const char*>(bom), sizeof(bom));
		wcscpy_s(stream.logfile, logfile);
		return stream;
	}

	void writeLog(LOG& log)
	{
		char buffer[80];
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		const char* format = "%d.%m.%Y %H:%M:%S";
		strftime(buffer, 80, format, timeinfo);
		std::ostringstream oss;
		oss << "\n----------- Запуск ------------ Время: " << buffer << " ------------ \n\n";
		if (log.stream == &std::cout)
			printConsoleUtf8(oss.str().c_str());
		else
			*log.stream << oss.str();
	}

	void writeLine(std::ostream* stream, char* c, ...)
	{
		std::ostringstream oss;
		char** ptr = &c;
		while (strcmp(*ptr, "") != 0)
		{
			oss << *ptr;
			++ptr;
		}
		std::string line = oss.str();
		if (stream == &std::cout)
		{
			printConsoleUtf8(line.c_str());
			printConsoleUtf8("\n");
		}
		else
		{
			*stream << line << std::endl;
		}
	}

	void writeParm(LOG& log, Parm::PARM& parm)
	{
		std::string inTxt = wideToUtf8(parm.in);
		std::string outTxt = wideToUtf8(parm.out);
		std::string logTxt = wideToUtf8(parm.log);
		std::string s = "\n----- Параметры --------\n";
		s += "-in: ";
		s += inTxt.c_str();
		s += "\n-out: ";
		s += outTxt.c_str();
		s += "\n-log: ";
		s += logTxt.c_str();
		if (log.stream == &std::cout)
		{
			printConsoleUtf8(s.c_str());
			printConsoleUtf8("\n");
		}
		else
		{
			*log.stream << s;
		}
	}

	void writeIn(std::ostream* stream, In::IN& in)
	{
		std::ostringstream oss;
		oss << "\n---- Входные данные ------";
		oss << "\nКоличество символов: " << std::setw(3) << in.size
			<< "\nПропущено: " << std::setw(3) << in.ignor
			<< "\nКоличество строк: " << std::setw(3) << in.lines << "\n\n";
		if (stream == &std::cout)
		{
			printConsoleUtf8(oss.str().c_str());
		}
		else
		{
			*stream << oss.str();
		}
	}

	void writeError(std::ostream* stream, Error::ERROR e)
	{
		std::ostringstream oss;
		if (e.position.line == -1 && e.position.col == -1)
			oss << "Ошибка " << e.id << ": " << e.message;
		else if (e.position.col == 0 || e.position.col == -1)
			oss << "Ошибка " << e.id << ": " << e.message << ", строка " << e.position.line;
		else
			oss << "Ошибка " << e.id << ": " << e.message
				<< ", строка " << e.position.line
				<< ", столбец " << e.position.col;

		std::string msg = oss.str();
		if (stream == NULL)
		{
			printConsoleUtf8(msg.c_str());
			printConsoleUtf8("\n");
			system("pause");
		}
		else if (stream == &std::cout)
		{
			printConsoleUtf8(msg.c_str());
			printConsoleUtf8("\n");
		}
		else
		{
			*stream << std::endl << msg << std::endl;
		}
		throw ERROR_THROW_IN(e.id, e.position.line, e.position.col);
	}

	void writeWords(std::ostream* stream, In::InWord* words)
	{
		std::ostringstream oss;
		oss << " ------------------ Таблица слов: ------------------" << std::endl;
		for (int i = 0; i < words->size; i++)
			oss << std::setw(2) << i << std::setw(3) << words[i].line << " |  " << words[i].word << std::endl;
		oss << "\n-------------------------------------------------------------------------\n\n";
		if (stream == &std::cout)
			printConsoleUtf8(oss.str().c_str());
		else
			*stream << oss.str();
	}

	void Close(LOG& log)
	{
		(*log.stream).close();
	}
};