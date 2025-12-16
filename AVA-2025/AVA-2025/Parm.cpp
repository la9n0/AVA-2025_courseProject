#include "Error.h"
#include "Parm.h"
#include <cwchar>
#include <locale>
#include <windows.h>

namespace Parm
{
	void makeAbsolutePath(wchar_t* path, size_t size)
	{
		if (path == nullptr || *path == L'\0')
			return;

		// Используем расширенный путь для поддержки длинных путей (до 32767 символов)
		wchar_t fullPath[32768];
		DWORD result = GetFullPathNameW(path, 32767, fullPath, nullptr);
		if (result > 0 && result < 32767)
		{
			wcscpy_s(path, size, fullPath);
		}
	}

	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM parm = { L"", L"", L"" };

		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)   throw ERROR_THROW(101)
			else
			{
				if (wcsncmp(argv[i], PARM_IN, wcslen(PARM_IN)) == 0)
					wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN));
				else if (wcsncmp(argv[i], PARM_OUT, wcslen(PARM_OUT)) == 0)
					wcscpy_s(parm.out, argv[i] + wcslen(PARM_OUT));
				else if (wcsncmp(argv[i], PARM_LOG, wcslen(PARM_LOG)) == 0)
					wcscpy_s(parm.log, argv[i] + wcslen(PARM_LOG));
			}
		}

		if (*parm.in == NULL)
			throw ERROR_THROW(100);

		// Преобразуем относительные пути в абсолютные
		makeAbsolutePath(parm.in, PARM_MAX_SIZE);

		if (*parm.out == NULL)
		{
			// Полный путь по умолчанию для out.asm
			wcscpy_s(parm.out, L"D:\\university\\3_sem\\kpo\\courseProject\\AVA-2025\\AVA-2025\\Assembler\\out.asm");
		}
		else
		{
			// Преобразуем указанный путь в абсолютный
			makeAbsolutePath(parm.out, PARM_MAX_SIZE);
		}

		if (*parm.log == NULL)
		{
			// Создаем путь для log файла на основе входного файла
			// parm.in уже преобразован в абсолютный путь
			wcscpy_s(parm.log, parm.in);
			wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, sizeof(PARM_LOG_DEFAULT_EXT));
			// Убеждаемся, что путь log файла тоже абсолютный
			makeAbsolutePath(parm.log, PARM_MAX_SIZE);
		}
		else
		{
			// Преобразуем указанный путь в абсолютный
			makeAbsolutePath(parm.log, PARM_MAX_SIZE);
		}

		return parm;
	};
}
