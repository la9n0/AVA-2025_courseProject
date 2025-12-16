#include <iostream>
#include <time.h>
#include <cstring>

extern "C" {
    int __stdcall slength(char* buffer, char* str)
    {
        if (str == nullptr)
            return 0;
        int len = 0;
        for (int i = 0; i < 256; i++)
            if (str[i] == '\0')
            {
                len = i; break;
            }
        return len;
    }

    int __stdcall outrad(char* ptr)
    {
        if (ptr == nullptr)
        {
            std::cout << std::endl;
        }
        for (int i = 0; ptr[i] != '\0'; i++)
            std::cout << ptr[i];
        return 0;
    }

    char* __stdcall copystr(char* buffer, char* str)
    {
        int i = 0;
        for (int j = 0; str[j] != '\0'; j++)
        {
            if (i == 255)
                break;
            buffer[i++] = str[j];
        }
        buffer[i] = '\0';
        return buffer;
    }

    int __stdcall compare(char* ptr, char* a, char* b)
    {
        if (strcmp(a, b) < 0)
            return 0;
        if (strcmp(a, b) == 0)
            return 1;
        if (strcmp(a, b) > 0)
            return 2;
        return 0;
    }

    int __stdcall rnd(char* ptr, int a, int b)
    {
        srand(time(NULL));
        int res;
        res = rand() % b + a;
        return res;
    }

    int __stdcall outlich(int value)
    {
        std::cout << value;
        return 0;
    }
}
