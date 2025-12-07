#include "pch.h"
#include "framework.h"
#include <iostream>
#include <cstring>

extern "C" {
    short __stdcall Sum(short firstOperand, short secondOperand) {
        return firstOperand + secondOperand;
    }
    short __stdcall Pow(short operand, short power) {
        if (power == 0) {
            return 1;
        }
        if (power < 0) {
            return 0;
        }
        short result = 1;
        for (short i = 0; i < power; i++) {
            result *= operand;
        }
        return result;
    }

    short __stdcall StrCmp(const char* s1, const char* s2) {
        return (short)strcmp(s1, s2);
    }

    void __stdcall writestr(const char* str) {
        std::cout << str << std::endl;
    }

    void __stdcall writechar(char ch) {
        std::cout << ch << std::endl;
    }

    void __stdcall writeint(short n) {
        std::cout << n << std::endl;
    }

    void __stdcall writebool(bool b) {
        if (b) {
            std::cout << "true" << std::endl;
        }
        else {
            std::cout << "false" << std::endl;
        }
    }
}
