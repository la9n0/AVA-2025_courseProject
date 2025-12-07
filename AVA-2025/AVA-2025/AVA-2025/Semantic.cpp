#include "Semantic.h"
#include "Error.h"
#include <cstring>
#pragma warning(disable : 1041)
namespace SA {

	void operands(MFST::LEX lex) {
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].lexema == LEX_ASSIGNMENT) {
				int cur = -1; 
				IT::IDDATATYPE datatype = (IT::IDDATATYPE)0; 

				while (lex.lextable.table[i + cur].lexema != LEX_SEMICOLON) {
					if (lex.lextable.table[i + cur].lexema == LEX_ID || lex.lextable.table[i + cur].lexema == LEX_LITERAL) {
						if (datatype == (IT::IDDATATYPE)0) {
							datatype = lex.idtable.table[lex.lextable.table[i + cur].idxTI].iddatatype;
						}
						else {
							if (datatype != lex.idtable.table[lex.lextable.table[i + cur].idxTI].iddatatype) {
								throw ERROR_THROW_IN(703, lex.lextable.table[i + cur].sn, lex.lextable.table[i + cur].cn);
							}
						}

						if (lex.idtable.table[lex.lextable.table[i + cur].idxTI].idtype == IT::FUNCTION ||
							lex.idtable.table[lex.lextable.table[i + cur].idxTI].idtype == IT::STATIC_FUNCTION) {
							while (lex.lextable.table[i + cur].lexema != LEX_RIGHTTHESIS) {
								cur++;
							}
						}
					}

					// Проверка на применение унарных операций к типу SYMBOL
					if (datatype == IT::SYMBOL && (lex.lextable.table[i + cur].lexema == LEX_INCREMENT || 
						lex.lextable.table[i + cur].lexema == LEX_DECREMENT || 
						lex.lextable.table[i + cur].lexema == LEX_INVERSION) && cur != 0) {
						throw ERROR_THROW_IN(704, lex.lextable.table[i + cur].sn, lex.lextable.table[i + cur].cn);
					}

					cur++; 
				}

				i += cur - 1;
			}

			// Проверка на неизвестный оператор 'b'
			if (lex.lextable.table[i].lexema == 'b') {
				if (lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype !=
					lex.idtable.table[lex.lextable.table[i + 1].idxTI].iddatatype) {
					throw ERROR_THROW_IN(703, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
				}
			}
		}
	}

    void functions(MFST::LEX lex) {
        for (int i = 0; i < lex.lextable.size; i++) {
            if (lex.lextable.table[i].lexema == LEX_DISPLAY) {
                // Если функция DISPLAY не имеет параметров, выбрасываем ошибку
                if (lex.lextable.table[i + 2].lexema == ')') {
                    throw ERROR_THROW_IN(714, lex.lextable.table[i + 2].sn, lex.lextable.table[i + 2].cn);
                }
            }

            if (lex.lextable.table[i].lexema == LEX_ID &&
                lex.lextable.table[i - 1].lexema == LEX_FUNCTION &&
                lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::FUNCTION)
            {
                int cur = 1;
                IT::IDDATATYPE returnType = lex.idtable.table[lex.lextable.table[i].idxTI].iddatatype;

                // Функция должна иметь return
                while (i + cur < lex.lextable.size && lex.lextable.table[i + cur].lexema != LEX_RETURN) {
                    cur++;
                }

                if (i + cur == lex.lextable.size) {
                    throw ERROR_THROW_IN(700, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
                }

                // Проверка типа возвращаемого значения
                if (i + cur < lex.lextable.size && (lex.lextable.table[i + cur + 1].lexema == LEX_ID ||
                    lex.lextable.table[i + cur + 1].lexema == LEX_LITERAL) &&
                    lex.idtable.table[lex.lextable.table[i + cur + 1].idxTI].idtype != IT::FUNCTION &&
                    lex.idtable.table[lex.lextable.table[i + cur + 1].idxTI].iddatatype != returnType) {
                    throw ERROR_THROW_IN(700, lex.lextable.table[i + cur].sn, lex.lextable.table[i + cur].cn);
                }
            }
        }

        // Проверка параметров для объявления функции и её вызова
        for (int i = 0; i < lex.lextable.size; i++) {
            if (lex.lextable.table[i].lexema == LEX_ID &&
                lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::FUNCTION &&
                lex.lextable.table[i - 1].lexema == LEX_FUNCTION)
            {
                IT::IDDATATYPE* ids = new IT::IDDATATYPE[16]; 
                int idsSize = 0;
                int funcPos = lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE; 

                while (lex.lextable.table[funcPos + 1].lexema != LEX_RIGHTTHESIS)
                {
                    if (lex.lextable.table[funcPos + 1].lexema == LEX_ID || lex.lextable.table[funcPos + 1].lexema == LEX_LITERAL) {
                        ids[idsSize] = lex.idtable.table[lex.lextable.table[funcPos + 1].idxTI].iddatatype;
                        idsSize++;
                    }
                    funcPos++;

                    if (idsSize == 16) {
                        throw ERROR_THROW_IN(705, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
                    }
                }
                delete[] ids;
            }

            // Проверка для стандартных функций 
            if (lex.lextable.table[i].lexema == LEX_ID &&
                lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::STATIC_FUNCTION)
            {
                int cur = 2;
                IT::IDDATATYPE dt = IT::INT;
                if (strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "StrCmp") == 0) {
                    dt = IT::SYMBOL; // StrCmp принимает строки (SYMBOL)
                }
                int numberOfParams = 0; 
                while (lex.lextable.table[i + cur].lexema != LEX_RIGHTTHESIS) {
                    if (lex.lextable.table[i + cur].lexema == LEX_ID || lex.lextable.table[i + cur].lexema == LEX_LITERAL) {
                        if (lex.idtable.table[lex.lextable.table[i + cur].idxTI].iddatatype == dt) {
                            numberOfParams++;
                        }
                        else {
                            throw ERROR_THROW_IN(713, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
                        }
                    }
                    cur++;
                }
                if (numberOfParams != 2) {
                    throw ERROR_THROW_IN(713, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
                }
            }

            // Проверка на вызов функции и соответствие параметров
            if (lex.lextable.table[i].lexema == LEX_ID &&
                lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::FUNCTION &&
                lex.lextable.table[i - 1].lexema != LEX_FUNCTION)
            {
                IT::IDDATATYPE* ids = new IT::IDDATATYPE[16];
                int idsSize = 0; 
                int funcPos = lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE;

                if (lex.lextable.table[i + 1].lexema != LEX_LEFTTHESIS) {
                    throw ERROR_THROW_IN(706, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
                }

                while (lex.lextable.table[funcPos + 1].lexema != LEX_RIGHTTHESIS)
                {
                    if (lex.lextable.table[funcPos + 1].lexema == LEX_ID ||
                        lex.lextable.table[funcPos + 1].lexema == LEX_LITERAL) {
                        ids[idsSize] = lex.idtable.table[lex.lextable.table[funcPos + 1].idxTI].iddatatype;
                        idsSize++;
                    }
                    funcPos++;

                    if (idsSize == 16) {
                        throw ERROR_THROW_IN(705, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
                    }
                }

                int cur = 1;
                int paramCount = 0;
                while (lex.lextable.table[i + cur].lexema != LEX_RIGHTTHESIS) {
                    if (lex.lextable.table[i + cur].lexema == LEX_ID ||
                        lex.lextable.table[i + cur].lexema == LEX_LITERAL) {
                        if (lex.idtable.table[lex.lextable.table[i + cur].idxTI].iddatatype != ids[paramCount]) {
                            throw ERROR_THROW_IN(702, lex.lextable.table[i + cur].sn, lex.lextable.table[i + cur].cn);
                        }
                        paramCount++;
                    }
                    cur++;
                }

                if (paramCount != idsSize) {
                    throw ERROR_THROW_IN(701, lex.lextable.table[i + cur].sn, lex.lextable.table[i + cur].cn);
                }
                i += cur; 
                delete[] ids; 
            }
        }

        // Проверка возвращаемого значения функции
        for (int i = 0; i < lex.lextable.size; i++) {
            if (lex.lextable.table[i].lexema == LEX_ASSIGNMENT &&
                lex.lextable.table[i - 1].lexema == LEX_ID &&
                lex.lextable.table[i + 1].lexema == LEX_ID &&
                lex.idtable.table[lex.lextable.table[i + 1].idxTI].idtype == IT::FUNCTION) {

                int funcIdx = lex.lextable.table[i + 1].idxTI;
                IT::IDDATATYPE returnType = lex.idtable.table[funcIdx].iddatatype; 

                int destIdx = lex.lextable.table[i - 1].idxTI; 
                IT::IDDATATYPE destType = lex.idtable.table[destIdx].iddatatype; 

                if (returnType != destType) {
                    throw ERROR_THROW_IN(707, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
                }
            }
        }
    }

    void literals(MFST::LEX lex) {
        for (int i = 0; i < lex.idtable.size; i++) {
            if (lex.idtable.table[i].idtype == IT::LITERAL && lex.idtable.table[i].iddatatype == IT::INT) {
                short value = lex.idtable.table[i].value.vint;
                if (value < -32768 || value > 32767) {
                    throw ERROR_THROW_IN(712, lex.lextable.table[lex.idtable.table[i].idxfirstLE].sn, lex.lextable.table[lex.idtable.table[i].idxfirstLE].cn);
                }
            }
        }
    }

	void fors(MFST::LEX lex) {
		for (int i = 0; i < lex.lextable.size; i++) {
			if (lex.lextable.table[i].lexema == LEX_FOR) {
				int cur = 2;
				IT::IDDATATYPE varType = (IT::IDDATATYPE)0;
				IT::IDDATATYPE exprType = (IT::IDDATATYPE)0;
				bool isFunc = false;
				
				// Проверка типа переменной цикла
				if (lex.lextable.table[i + cur].lexema == LEX_ID) {
					varType = lex.idtable.table[lex.lextable.table[i + cur].idxTI].iddatatype;
					if (varType != IT::INT) {
						throw ERROR_THROW_IN(710, lex.lextable.table[i + cur].sn, lex.lextable.table[i + cur].cn);
					}
				}
				
				cur++; // Пропускаем ':'
				
				// Проверка типа выражения
				while (lex.lextable.table[i + cur].lexema != LEX_RIGHTTHESIS || isFunc) {
					if (lex.lextable.table[i + cur].lexema == LEX_ID || lex.lextable.table[i + cur].lexema == LEX_LITERAL) {
						if (exprType == (IT::IDDATATYPE)0) {
							exprType = lex.idtable.table[lex.lextable.table[i + cur].idxTI].iddatatype;
						}
						else if (exprType != lex.idtable.table[lex.lextable.table[i + cur].idxTI].iddatatype) {
							throw ERROR_THROW_IN(710, lex.lextable.table[i + cur].sn, lex.lextable.table[i + cur].cn);
						}
					}
					if (lex.lextable.table[i + cur].lexema == LEX_LEFTTHESIS) isFunc = true;
					if (lex.lextable.table[i + cur].lexema == LEX_RIGHTTHESIS) isFunc = false;
					cur++;
				}
				
				if (exprType != IT::INT) {
					throw ERROR_THROW_IN(710, lex.lextable.table[i].sn, lex.lextable.table[i].cn);
				}
			}
		}
	}

	bool startSA(MFST::LEX lex) {
		functions(lex);
		operands(lex);
		literals(lex);
		fors(lex);
		return true;
	};

}
