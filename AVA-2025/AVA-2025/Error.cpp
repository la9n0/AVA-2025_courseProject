
#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
      ERROR_ENTRY(0, "Системная ошибка: неопределенный код ошибки"),
      ERROR_ENTRY(1, "Ошибка генерации польской записи: обнаружен недопустимый лексема"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
      ERROR_ENTRY(100, "Параметры ошибки: параметр -in должен быть указан"),
      ERROR_ENTRY(101, "Параметры ошибки: превышена максимальная длина параметра"),
      ERROR_ENTRY(102, "Параметры ошибки: ошибка при открытии файла с исходным кодом(-in)"),
      ERROR_ENTRY(103, "Параметры ошибки: ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
      
      // ========== БЛОК ЛЕКСИЧЕСКИХ ОШИБОК (200-299) ==========
      ERROR_ENTRY(200, "Лексический анализ: обнаружен недопустимый символ в исходном файле(-in)"),
      ERROR_ENTRY(201, "Лексический анализ: обнаружен недопустимый символ"),
      ERROR_ENTRY(202, "Лексический анализ: превышен размер таблицы лексем"),
      ERROR_ENTRY(203, "Лексический анализ: превышен размер таблицы идентификаторов"),
      ERROR_ENTRY(204, "Лексический анализ: превышен размер идентификатора"),
      ERROR_ENTRY(205, "Лексический анализ: отсутствует точка входа main"),
      ERROR_ENTRY(206, "Лексический анализ: дублирование объявления точки входа main"),
      ERROR_ENTRY(207, "Лексический анализ: в инструкции не указан тип идентификатора"),
      ERROR_ENTRY(208, "Лексический анализ: в инструкции отсутствует название типа"),
      ERROR_ENTRY(209, "Лексический анализ: дублирование идентификатора функции"),
      ERROR_ENTRY(210, "Лексический анализ: превышено максимальное количество параметров функции"),
      ERROR_ENTRY(211, "Лексический анализ: пустая строка или символ"),
      ERROR_ENTRY(212, "Лексический анализ: пропущена символ '\"'. Возможно, не указан начальный/конечный символ"),
      ERROR_ENTRY(213, "Лексический анализ: превышена максимальная длина строки/символа (256 символов)"),
      ERROR_ENTRY(214, "Лексический анализ: неверное значение литерала"),
      ERROR_ENTRY(215, "Лексический анализ: превышена максимальная длина символа"),
		ERROR_ENTRY_NODEF(216), ERROR_ENTRY_NODEF(217), ERROR_ENTRY_NODEF(218), ERROR_ENTRY_NODEF(219),
		ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
		ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
      
      // ========== БЛОК СИНТАКСИЧЕСКИХ ОШИБОК (300-399) ==========
		ERROR_ENTRY_NODEF(300), ERROR_ENTRY_NODEF(301), ERROR_ENTRY_NODEF(302), ERROR_ENTRY_NODEF(303), ERROR_ENTRY_NODEF(304), ERROR_ENTRY_NODEF(305), ERROR_ENTRY_NODEF(306),
		ERROR_ENTRY_NODEF(307), ERROR_ENTRY_NODEF(308), ERROR_ENTRY_NODEF(309), ERROR_ENTRY_NODEF(310), ERROR_ENTRY_NODEF(311),
		ERROR_ENTRY_NODEF(312), ERROR_ENTRY_NODEF(313), ERROR_ENTRY_NODEF(314), ERROR_ENTRY_NODEF(315), ERROR_ENTRY_NODEF(316),
		ERROR_ENTRY_NODEF(317), ERROR_ENTRY_NODEF(318), ERROR_ENTRY_NODEF(319), ERROR_ENTRY_NODEF(320),
		ERROR_ENTRY_NODEF10(321), ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),ERROR_ENTRY_NODEF10(350),
		ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),ERROR_ENTRY_NODEF10(390),

      // ========== БЛОК СЕМАНТИЧЕСКИХ ОШИБОК (400-499) ==========
      ERROR_ENTRY(400, "Семантический анализ: превышено максимальное количество параметров функции (3)"),
      ERROR_ENTRY(401, "Семантический анализ: несоответствие количества параметров функции"),
      ERROR_ENTRY(402, "Семантический анализ: несоответствие типа параметра функции"),
      ERROR_ENTRY(403, "Семантический анализ: несоответствие типов данных при присваивании"),
      ERROR_ENTRY(404, "Семантический анализ: несоответствие типа возвращаемого значения функции"),
      ERROR_ENTRY(405, "Семантический анализ: недопустимая операция со строковым типом"),
      ERROR_ENTRY(406, "Семантический анализ: неверный тип параметра оператора сравнения"),
      ERROR_ENTRY(407, "Семантический анализ: деление на ноль"),
      ERROR_ENTRY(408, "Семантический анализ: в инструкции не указан тип идентификатора"),
      ERROR_ENTRY(413, "Семантический анализ: неверный тип параметра цикла"),
      ERROR_ENTRY(414, "Семантический анализ: неверный тип параметра унарной операции"),
		ERROR_ENTRY_NODEF(409), ERROR_ENTRY_NODEF(410), ERROR_ENTRY_NODEF(411), ERROR_ENTRY_NODEF(412), ERROR_ENTRY_NODEF(415), ERROR_ENTRY_NODEF(416), ERROR_ENTRY_NODEF(417), ERROR_ENTRY_NODEF(418), ERROR_ENTRY_NODEF(419),
		ERROR_ENTRY_NODEF10(420), ERROR_ENTRY_NODEF10(430), ERROR_ENTRY_NODEF10(440), ERROR_ENTRY_NODEF10(450),
		ERROR_ENTRY_NODEF10(460), ERROR_ENTRY_NODEF10(470), ERROR_ENTRY_NODEF10(480), ERROR_ENTRY_NODEF10(490),

		ERROR_ENTRY_NODEF100(500),
      
      // ========== БЛОК СИНТАКСИЧЕСКИХ ОШИБОК ГРАММАТИКИ (600-699) ==========
      ERROR_ENTRY(600, "Синтаксический анализ: ошибка в структуре программы (правило S)"),
      ERROR_ENTRY(601, "Синтаксический анализ: ошибка в параметрах функции (правило P)"),
      ERROR_ENTRY(602, "Синтаксический анализ: ошибка в теле функции (правило T)"),
      ERROR_ENTRY(603, "Синтаксический анализ: ошибка в теле процедуры (правило G)"),
      ERROR_ENTRY(604, "Синтаксический анализ: ошибка в списке параметров (правило E)"),
      ERROR_ENTRY(605, "Синтаксический анализ: ошибка в параметрах функции (правило F)"),
      ERROR_ENTRY(606, "Синтаксический анализ: ошибка в списке аргументов (правило N)"),
      ERROR_ENTRY(607, "Синтаксический анализ: ошибка в арифметическом операторе (правило A)"),
      ERROR_ENTRY(608, "Синтаксический анализ: ошибка в значении (правило V)"),
      ERROR_ENTRY(609, "Синтаксический анализ: ошибка в выражении (правило W)"),
      ERROR_ENTRY(610, "Синтаксический анализ: отсутствует символ ';' в конце строки"),
      ERROR_ENTRY(611, "Синтаксический анализ: ошибка в операторе процедуры (правило X)"),
      
		ERROR_ENTRY_NODEF(612), ERROR_ENTRY_NODEF(613), ERROR_ENTRY_NODEF(614), ERROR_ENTRY_NODEF(615),
		ERROR_ENTRY_NODEF(616), ERROR_ENTRY_NODEF(617), ERROR_ENTRY_NODEF(618), ERROR_ENTRY_NODEF(619),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690)
	};

	ERROR GetError(int id)
	{
        ERROR err;
		if (id < 0 || id > ERROR_MAX_ENTRY)
            err = errors[0];
		else
            err = errors[id];
        err.position.line = -1;
        err.position.col = -1;
        return err;
	}

	ERROR GetError(int id, int line, int col)
	{
		ERROR err = GetError(id);
		err.position.col = col;
		err.position.line = line;
		return err;
	}
}
