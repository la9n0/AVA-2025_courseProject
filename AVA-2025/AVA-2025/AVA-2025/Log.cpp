#include "Log.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdarg>
#include <cstring>
#include <string>
#include "IT.h"
#include "LT.h"
#include "Parm.h"
#include "Error.h"

namespace Log {
	void WriteLine(LOG log, char* c, ...) {
		va_list args;
		va_start(args, c);
		char* arg = c;
		std::string consoleOutput;
		while (arg != nullptr) {
			if (log.stream != nullptr) {
				*log.stream << arg;
			}
			consoleOutput += arg;
			arg = va_arg(args, char*);
		}
		va_end(args);
		if (log.stream != nullptr) {
			*log.stream << "\n";
		}
		std::cout << consoleOutput << std::endl;
	}
	
	void WriteLine(LOG log, wchar_t* c, ...) {
		va_list args;
		va_start(args, c);
		wchar_t* arg = c;
		std::wstring consoleOutput;
		while (arg != nullptr) {
			if (log.stream != nullptr) {
				*log.stream << arg;
			}
			consoleOutput += arg;
			arg = va_arg(args, wchar_t*);
		}
		va_end(args);
		if (log.stream != nullptr) {
			*log.stream << "\n";
		}
		std::wcout << consoleOutput << std::endl;
	}

	void WriteLog(LOG log) {
		if (log.stream != nullptr) {
			*log.stream << "---  ---\n";
			*log.stream << "Log file: " << log.logfile << "\n";
			*log.stream << "---  ---\n";
		}
		std::wcout << L"--- ЛОГИРОВАНИЕ ---\n";
		std::wcout << L"Log file: " << log.logfile << L"\n";
		std::wcout << L"--- --- ---\n";
	}

	void WriteParm(LOG log, Parm::PARM parm) {
		if (log.stream != nullptr) {
			*log.stream << "---  ---\n";
			*log.stream << "- : " << parm.in << "\n";
			*log.stream << "- : " << parm.out << "\n";
			*log.stream << "- : " << parm.log << "\n";
			*log.stream << "---  ---\n";
		}
		std::wcout << L"--- ПАРАМЕТРЫ КОМПИЛЯЦИИ ---\n";
		std::wcout << L"Входной файл: " << parm.in << L"\n";
		std::wcout << L"Выходной файл: " << parm.out << L"\n";
		std::wcout << L"Лог-файл: " << parm.log << L"\n";
		std::wcout << L"--- --- ---\n";
	}

	void WriteIn(LOG log, In::IN in) {
		if (log.stream != nullptr) {
			*log.stream << "---  ---\n";
			*log.stream << "  : " << in.size << "\n";
			*log.stream << "  : " << in.lines << "\n";
			*log.stream << "  : " << in.ignor << "\n";
			*log.stream << "---  ---\n";
		}
		std::cout << "--- ИНФОРМАЦИЯ О ВХОДНОМ ФАЙЛЕ ---\n";
		std::cout << "Размер: " << in.size << " байт\n";
		std::cout << "Строк: " << in.lines << "\n";
		std::cout << "Игнорировано символов: " << in.ignor << "\n";
		std::cout << "--- --- ---\n";
	}


	void WriteLexTable(LOG log, LT::LexTable lextable) {
		if (log.stream == nullptr) return;
		*log.stream << "---  ---\n";
		*log.stream << "  :\n";
		for (int i = 0; i < lextable.size; i++) {
			*log.stream << i << "\t" << lextable.table[i].lexema << "\t" << lextable.table[i].sn << "\t" << lextable.table[i].idxTI << "\n";
		}
		*log.stream << "---  ---\n";
	}

	void WriteIdTable(LOG log, IT::IdTable idtable) {
		if (log.stream == nullptr) return;
		*log.stream << "---  ---\n";
		*log.stream << "  :\n";
		char idtype[20];
		char iddatatype[20];
		for (int i = 0; i < idtable.size; i++) {
			if (idtable.table[i].idtype == IT::VARIABLE) {
				strcpy_s(idtype, "");
			}
			else if (idtable.table[i].idtype == IT::FUNCTION) {
				strcpy_s(idtype, "");
			}
			else if (idtable.table[i].idtype == IT::PARAMETER) {
				strcpy_s(idtype, "");
			}
			else if (idtable.table[i].idtype == IT::LITERAL) {
				strcpy_s(idtype, "");
			}
			else {
				strcpy_s(idtype, "");
			};
			if (idtable.table[i].iddatatype == IT::INT) {
				strcpy_s(iddatatype, " (2)");
			}
			else if (idtable.table[i].iddatatype == IT::SYMBOL) {
				strcpy_s(iddatatype, "");
			}
			else {
				strcpy_s(iddatatype, "");
			}
			(*log.stream) << std::setw(20) << std::left << idtable.table[i].id << ":  : " << std::setw(3) << std::left << idtable.table[i].idxfirstLE << ". : " << std::setw(10) << std::left << idtype << ".  : " << iddatatype << "\n";
		}
	}

	void WriteInText(LOG log, In::IN in) {
		if (log.stream == nullptr) return;
		*log.stream << "---  ---\n";
		*log.stream << "  :\n";
		if (in.text != nullptr) {
			*log.stream << in.text;
		}
		*log.stream << "\n---  ---\n";
	}

	void WriteTables(LOG log, IT::IdTable& idtable, LT::LexTable& lextable) {
		if (log.stream == nullptr) return;
		WriteIdTable(log, idtable);
		WriteLexTable(log, lextable);
	}

	void WriteError(LOG log, Error::ERROR error) {
		std::string errorMsg = "--- ОШИБКА ---\n";
		errorMsg += "Error " + std::to_string(error.id) + ": " + error.message + "\n";
		if (error.inext.line != -1) {
			errorMsg += "Line: " + std::to_string(error.inext.line) + ", Column: " + std::to_string(error.inext.col) + "\n";
		}
		errorMsg += "--- --- ---\n";
		
		if (log.stream != nullptr) {
			*log.stream << "---  ---\n";
			*log.stream << "Error " << error.id << ": " << error.message << "\n";
			if (error.inext.line != -1) {
				*log.stream << "Line: " << error.inext.line << ", Column: " << error.inext.col << "\n";
			}
			*log.stream << "---  ---\n";
		}
		std::cerr << errorMsg;
	}

	LOG getlog(wchar_t logfile[]) {
		LOG log;
		wcscpy_s(log.logfile, PARM_MAX_SIZE, logfile);
		log.stream = new std::ofstream;
		log.stream->open(logfile);
		if (!log.stream->is_open()) {
			throw ERROR_THROW(140);
		}
		return log;
	}

	void Close(LOG log) {
		if (log.stream != nullptr) {
			log.stream->close();
		}
	}
}
