#pragma once
#include <string>
#include <stack>
#include <vector>

using namespace std;

#define ID_MAXSIZE			21
#define TI_MAXSIZE			4096
#define TI_UINT_DEFAULT		0x00000000
#define TI_SHORT_DEFAULT	0x0000
#define TI_CHAR_DEFAULT		0x00
#define TI_BOOL_DEFAULT		0x00
#define TI_STR_DEFAULT		0x00
#define TI_NULLIDX			0xffffffff
#define GLOBAL				"global"
#define TI_STR_MAXSIZE		256
#define FUNC_STRCMP			"strcmp"


#define PARM_ID_DEFAULT_LOCATION		L"D:\\university\\3_sem\\kpo\\kurs_project\\AVA-2025\\Debug\\Files\\"
#define PARM_ID_DEFAULT_EXT				L".id.txt"

namespace IT
{
	enum class IDDATATYPE { DEF, UINT, SHORT, CHAR, BOOL, STR };
	enum class IDTYPE { D, V, F, P, L, C };

	struct Entry
	{
		int idxfirstLE;
		char areaOfVisibility[ID_MAXSIZE]{};
		char id[ID_MAXSIZE]{};
		IDDATATYPE	iddatatype;
		IDTYPE	idtype;
		union
		{
			unsigned int vuint;
			short vshort;
			char vchar;
			bool vbool;
			struct
			{
				unsigned char len;
				char str[TI_STR_MAXSIZE];
			} vstr;
		}value;
		struct Param
		{
			int count;
			vector<IDDATATYPE> types;
		} params;
		string FullName;
		Entry(int idxfirstLE, string areaOfVisibility, const char* id, IDDATATYPE iddatatype, IDTYPE idtype);
		Entry(int idxfirstLE, IDDATATYPE iddatatype, IDTYPE idtype, char* value);
	};
	struct IdTable
	{
		int maxsize;
		int current_size;
		Entry** table;

		IdTable(int size);
	};

	static Entry strcmp(0, string(GLOBAL), FUNC_STRCMP, IDDATATYPE::UINT, IDTYPE::F);

	void Add(IdTable& idtable, Entry* entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], stack<string> areaOfVisibility);
	int IsLiteralChar(IdTable& idtable, char* lexema);
	int IsLiteralBool(IdTable& idtable, char* lexema);
	int IsLiteralString(IdTable& idtable, char* lexema);
	void PrintIdTable(IdTable& idtable, const wchar_t* in);
	void Delete(IdTable& idtable);
}
