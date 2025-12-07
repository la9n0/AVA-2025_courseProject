#include "Log.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdarg>
#include <cstring>
#include "IT.h"
#include "LT.h"
#include "Parm.h"
#include "Error.h"

namespace Log {
	void WriteLine(LOG log, char* c, ...) {
		if (log.stream == nullptr) return;
		va_list args;
		va_start(args, c);
		char* arg = c;
		while (arg != nullptr) {
			*log.stream << arg;
			arg = va_arg(args, char*);
		}
		va_end(args);
		*log.stream << "\n";
	}
	
	void WriteLine(LOG log, wchar_t* c, ...) {
		if (log.stream == nullptr) return;
		va_list args;
		va_start(args, c);
		wchar_t* arg = c;
		while (arg != nullptr) {
			*log.stream << arg;
			arg = va_arg(args, wchar_t*);
		}
		va_end(args);
		*log.stream << "\n";
	}

	void WriteLog(LOG log) {
		if (log.stream == nullptr) return;
		*log.stream << "---  ---\n";
		*log.stream << "Log file: " << log.logfile << "\n";
		*log.stream << "---  ---\n";
	}

	void WriteParm(LOG log, Parm::PARM parm) {
		if (log.stream == nullptr) return;
		*log.stream << "---  ---\n";
		*log.stream << "- : " << parm.in << "\n";
		*log.stream << "- : " << parm.out << "\n";
		*log.stream << "- : " << parm.log << "\n";
		*log.stream << "---  ---\n";
	}

	void WriteIn(LOG log, In::IN in) {
		if (log.stream == nullptr) return;
		*log.stream << "---  ---\n";
		*log.stream << "  : " << in.size << "\n";
		*log.stream << "  : " << in.lines << "\n";
		*log.stream << "  : " << in.ignor << "\n";
		*log.stream << "---  ---\n";
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
		if (log.stream == nullptr) return;
		*log.stream << "---  ---\n";
		*log.stream << "Error " << error.id << ": " << error.message << "\n";
		if (error.inext.line != -1) {
			*log.stream << "Line: " << error.inext.line << ", Column: " << error.inext.col << "\n";
		}
		*log.stream << "---  ---\n";
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
