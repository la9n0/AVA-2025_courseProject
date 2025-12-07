#pragma once
#define LEXEMA_FIXSIZE 1 // 
#define LT_MAXSIZE 4096 //    
#define LT_TI_NULLIDX 0xffffffff //   
#define LEX_INT 't'       // int (2 )
#define LEX_SYMBOL 's'    // symbol (char)

#define LEX_ID 'i'        // 
#define LEX_LITERAL 'l'   //
#define LEX_FUNCTION 'f'  // function
#define LEX_FOR 'o'		  // for - 
#define LEX_DECLARE 'd'   // declare
#define LEX_RETURN 'r'    // return
#define LEX_DISPLAY 'p'   // display (print)
#define LEX_MAIN 'm'      // main -   

#define LEX_ASSIGNMENT ':'// 
#define LEX_SEMICOLON ';'  
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define	LEX_BRACELET '}'
#define LEX_LEFTTHESIS '('
#define LEX_RIGHTTHESIS ')'

#define LEX_INCREMENT 'u'   // ++ - 
#define LEX_DECREMENT 'v'   // -- - 
#define LEX_INVERSION 'w'   // ~ - 

#include "In.h"
#include <vector>

namespace LT {
	struct Entry {
		char lexema; //
		int sn; //   
		int cn;
		int idxTI; //  
		std::vector<char>data;

		Entry( //    
			char lexema,
			int sn,
			int col,
			int idxTI
		) {
			this->lexema = lexema;
			this->sn = sn;
			this->cn = col;
			this->idxTI = idxTI;
		};

		Entry() = default;
	};

	struct LexTable {
		int size;			     // 
		std::vector<Entry>table; //  
	};
	LexTable Create();
	void AddEntry(
		LexTable& lextable,
		Entry entry
	);
	Entry GetEntry(
		LexTable& lextable,
		int n                    //   
	);
	void Delete(LexTable& lextable);
}
