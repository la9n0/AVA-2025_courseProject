#include <iostream>
#include <iomanip>
#include <sstream>
#include "LT.h"
#include "Error.h"
#include "Log.h"


namespace LT
{
	Entry::Entry()
	{
		lexema = NULL;
		sn = NULL;
		idxTI = NULLDX_TI;
	}

	Entry::Entry(char lexema, int snn, int idxti)
	{
		this->lexema = lexema;
		this->sn = snn;
		this->idxTI = idxti;
	}

	LexTable Create(int size)
	{
		if (size > MAXSIZE_LT)
			throw ERROR_THROW(202);
		LexTable lextable;
		lextable.table = new Entry[lextable.maxsize = size];
		lextable.size = NULL;
		return  lextable;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size >= lextable.maxsize)
			throw ERROR_THROW(202);
		lextable.table[lextable.size++] = entry;
	}

	void writeLexTable(std::ostream* stream, LT::LexTable& lextable)
	{
		std::ostringstream oss;
		oss << "------------------------------ Таблица лексем ------------------------\n" << std::endl;
		oss << "|  N | Лексема | Строка | Индекс в ТИ |" << std::endl;
		for (int i = 0; i < lextable.size; i++)
		{
			oss << "|" << std::setw(3) << i << " | " << std::setw(4) << lextable.table[i].lexema << "    |  " << std::setw(3)
				<< lextable.table[i].sn << "   |";
			if (lextable.table[i].idxTI == -1)
				oss << "             |" << std::endl;
			else
				oss << std::setw(8) << lextable.table[i].idxTI << "     |" << std::endl;
		}
		std::string str = oss.str();
		if (stream == &std::cout)
			Log::printConsoleUtf8(str.c_str());
		else
			*stream << str;
	}

	void writeLexemsOnLines(std::ostream* stream, LT::LexTable& lextable)
	{
		std::ostringstream oss;
		oss << "\n-----------------  Лексемы идентификаторов по строкам ---------------------\n" << std::endl;
		for (int i = 0; i < lextable.size; )
		{
			int line = lextable.table[i].sn;
			oss << std::setw(3) << line << " | ";
			while (lextable.table[i].sn == line)
			{
				oss << lextable.table[i].lexema;
				if (lextable.table[i].idxTI != NULLDX_TI)
					oss << "[" << lextable.table[i].idxTI << "]";
				i++;
			}
			oss << std::endl;
		}
		oss << "-------------------------------------------------------------------------\n\n";
		std::string str = oss.str();
		if (stream == &std::cout)
			Log::printConsoleUtf8(str.c_str());
		else
			*stream << str;
	}
}
