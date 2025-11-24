#include "stdafx.h"
#include "IT.h"
#include "Error.h"

using namespace std;

namespace IT
{
	IdTable::IdTable(int size)
	{
		if (size > TI_MAXSIZE)
			throw ERROR_THROW(127);

		maxsize = TI_MAXSIZE;
		current_size = 0;
		table = new Entry * [size];
	}

	Entry::Entry(int idxfirstLE, string areaOfVisibility, const char* id, IDDATATYPE iddatatype, IDTYPE idtype)
	{
		this->idxfirstLE = idxfirstLE;
		strncpy(this->areaOfVisibility, areaOfVisibility.c_str(), ID_MAXSIZE - 1);
		strncpy(this->id, id, ID_MAXSIZE - 1);
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		if (iddatatype == IT::IDDATATYPE::UINT)
			this->value.vuint = TI_UINT_DEFAULT;
		else if (iddatatype == IT::IDDATATYPE::SHORT)
			this->value.vshort = TI_SHORT_DEFAULT;
		else if (iddatatype == IT::IDDATATYPE::CHAR)
			this->value.vchar = TI_CHAR_DEFAULT;
		else if (iddatatype == IT::IDDATATYPE::BOOL)
			this->value.vbool = TI_BOOL_DEFAULT;
		else
		{
			this->value.vstr.len = 0;
			this->value.vstr.str[0] = TI_STR_DEFAULT;
		}
		this->params.count = 0;
		if (this->idtype == IT::IDTYPE::V || this->idtype == IT::IDTYPE::P)
			FullName = string(this->id) + '_' + string(this->areaOfVisibility);
		else
			FullName = string(this->id);
	}

	Entry::Entry(int idxfirstLE, IDDATATYPE iddatatype, IDTYPE idtype, char* value)
	{
		char str[10];
		static int count = 0;
		sprintf(str, "%d", count++);
		strcpy(this->id, "L");
		strcat(this->id, str);
		strcpy(this->areaOfVisibility, GLOBAL);
		this->idxfirstLE = idxfirstLE;
		this->iddatatype = iddatatype;
		this->idtype = idtype;
		if (iddatatype == IT::IDDATATYPE::UINT)
			this->value.vuint = (unsigned int)atoi(value);
		else if (iddatatype == IT::IDDATATYPE::SHORT)
			this->value.vshort = (short)atoi(value);
		else if (iddatatype == IT::IDDATATYPE::CHAR)
			this->value.vchar = value[0];
		else if (iddatatype == IT::IDDATATYPE::BOOL)
			this->value.vbool = (strcmp(value, "true") == 0 || strcmp(value, "1") == 0);
		else
		{
			this->value.vstr.len = strlen(value);
			strncpy(this->value.vstr.str, value, TI_STR_MAXSIZE - 1);
			this->value.vstr.str[TI_STR_MAXSIZE - 1] = TI_STR_DEFAULT;
		}
		FullName = string(this->id);
	}

	void Add(IdTable& idtable, Entry* entry)
	{
		if (idtable.current_size < idtable.maxsize)
		{
			idtable.table[idtable.current_size] = entry;
			idtable.current_size++;
		}
		else
			throw ERROR_THROW(128);
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n > idtable.current_size)
			throw ERROR_THROW(129);

		return *idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE], stack<string> areaOfVisibility)
	{
		int size = areaOfVisibility.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < idtable.current_size; j++)
			{
				if (!strcmp(idtable.table[j]->areaOfVisibility, areaOfVisibility.top().c_str()))
					if (!strcmp(idtable.table[j]->id, id))
						return j;
			}
			areaOfVisibility.pop();
		}
		return -1;
	}

	int IsLiteralChar(IdTable& idtable, char* lexema)
	{
		char ch = lexema[0];
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i]->idtype == IT::IDTYPE::L && idtable.table[i]->iddatatype == IT::IDDATATYPE::CHAR)
				if (idtable.table[i]->value.vchar == ch)
					return i;
		}
		return -1;
	}

	int IsLiteralBool(IdTable& idtable, char* lexema)
	{
		bool val = (strcmp(lexema, "true") == 0 || strcmp(lexema, "1") == 0);
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i]->idtype == IT::IDTYPE::L && idtable.table[i]->iddatatype == IT::IDDATATYPE::BOOL)
				if (idtable.table[i]->value.vbool == val)
					return i;
		}
		return -1;
	}

	int IsLiteralString(IdTable& idtable, char* lexema)
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i]->idtype == IT::IDTYPE::L && idtable.table[i]->iddatatype == IT::IDDATATYPE::STR)
				if (!strcmp(idtable.table[i]->value.vstr.str, lexema))
					return i;
		}
		return -1;
	}

	void Delete(IdTable& idtable)
	{
		for (int i = 1; i < idtable.current_size; i++)
		{
			delete idtable.table[i];
		}
		delete[] idtable.table;
	}

	void PrintIdTable(IdTable& idtable, const wchar_t* in)
	{
		wchar_t* id = new wchar_t[wcslen(PARM_ID_DEFAULT_LOCATION) + wcslen(in) + wcslen(PARM_ID_DEFAULT_EXT) + 1] {};
		wcscat(id, PARM_ID_DEFAULT_LOCATION);
		wcscat(id, in);
		wcscat(id, PARM_ID_DEFAULT_EXT);

		ofstream idStream(id);
		delete[] id;
		if (!idStream.is_open())
			throw ERROR_THROW(125);

		idStream << "" << endl;
		idStream << " LE\t" << " \t" << "\t" << " \t" << " \t" << "\t" << " \n";
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i]->idtype == IT::IDTYPE::V)
			{
				if (idtable.table[i]->iddatatype == IT::IDDATATYPE::UINT)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "V" << '\t' << setw(10) << "UINT" << '\t' << setw(8) << idtable.table[i]->value.vuint << '\t' << setw(12) << "-" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::SHORT)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "V" << '\t' << setw(10) << "SHORT" << '\t' << setw(8) << idtable.table[i]->value.vshort << '\t' << setw(12) << "-" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::CHAR)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "V" << '\t' << setw(10) << "CHAR" << '\t' << setw(8) << idtable.table[i]->value.vchar << '\t' << setw(12) << "-" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::BOOL)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "V" << '\t' << setw(10) << "BOOL" << '\t' << setw(8) << (idtable.table[i]->value.vbool ? "true" : "false") << '\t' << setw(12) << "-" << endl;
				else
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "V" << '\t' << setw(10) << "STR" << '\t' << setw(8) << idtable.table[i]->value.vstr.str << '\t' << setw(12) << (int)idtable.table[i]->value.vstr.len << endl;

			if (idtable.table[i]->idtype == IT::IDTYPE::P)
			{
				if (idtable.table[i]->iddatatype == IT::IDDATATYPE::UINT)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "P" << '\t' << setw(10) << "UINT" << '\t' << setw(8) << idtable.table[i]->value.vuint << '\t' << setw(12) << "-" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::SHORT)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "P" << '\t' << setw(10) << "SHORT" << '\t' << setw(8) << idtable.table[i]->value.vshort << '\t' << setw(12) << "-" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::CHAR)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "P" << '\t' << setw(10) << "CHAR" << '\t' << setw(8) << idtable.table[i]->value.vchar << '\t' << setw(12) << "-" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::BOOL)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "P" << '\t' << setw(10) << "BOOL" << '\t' << setw(8) << (idtable.table[i]->value.vbool ? "true" : "false") << '\t' << setw(12) << "-" << endl;
				else
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(18) << "P" << '\t' << setw(10) << "STR" << '\t' << setw(8) << idtable.table[i]->value.vstr.str << '\t' << setw(12) << (int)idtable.table[i]->value.vstr.len << endl;

		}

		idStream << "\n" << endl;
		idStream << " LE\t" << " \t" << "\t" << "  \n";
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i]->idtype == IT::IDTYPE::F)
			{
				if (idtable.table[i]->iddatatype == IT::IDDATATYPE::UINT)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(19) << "UINT" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::SHORT)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(19) << "SHORT" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::CHAR)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(19) << "CHAR" << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::BOOL)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(19) << "BOOL" << endl;
			}
				else
				{
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(17) << idtable.table[i]->areaOfVisibility << '\t' << setw(13) << idtable.table[i]->id << '\t' << setw(19) << "STR" << endl;

				}
		}

		idStream << "\n" << endl;
		idStream << " LE\t" << "\t" << " \t" << " \t\t" <<setw(34)<< "\n";
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i]->idtype == IT::IDTYPE::L)
			{
				if (idtable.table[i]->iddatatype == IT::IDDATATYPE::UINT)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(12) << idtable.table[i]->id << setw(11) << "UINT" << '\t' << setw(15) << "-" <<'\t'<<'\t' << setw(40) << idtable.table[i]->value.vuint << '\t' << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::SHORT)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(12) << idtable.table[i]->id << setw(11) << "SHORT" << '\t' << setw(15) << "-" <<'\t'<<'\t' << setw(40) << idtable.table[i]->value.vshort << '\t' << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::CHAR)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(12) << idtable.table[i]->id << setw(11) << "CHAR" << '\t' << setw(15) << "-" <<'\t'<<'\t' << setw(40) << idtable.table[i]->value.vchar << '\t' << endl;
				else if (idtable.table[i]->iddatatype == IT::IDDATATYPE::BOOL)
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(12) << idtable.table[i]->id << setw(11) << "BOOL" << '\t' << setw(15) << "-" <<'\t'<<'\t' << setw(40) << (idtable.table[i]->value.vbool ? "true" : "false") << '\t' << endl;
				else
					idStream << setw(9) << idtable.table[i]->idxfirstLE << '\t' << setw(12) << idtable.table[i]->id << setw(11) << "STR" << '\t' << setw(15) << (int)idtable.table[i]->value.vstr.len <<setw(38)<<'\t' << idtable.table[i]->value.vstr.str << endl;
			}
		}
	}
}
