
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
      ERROR_ENTRY_NODEF(205), ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
      ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
      ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
      
      // ========== БЛОК СИНТАКСИЧЕСКИХ ОШИБОК (300-399) ==========
      ERROR_ENTRY(300, "Синтаксический анализ: неизвестный идентификатор"),
      ERROR_ENTRY(301, "Синтаксический анализ: отсутствует точка входа main"),
      ERROR_ENTRY(302, "Синтаксический анализ: дублирование объявления точки входа main"),
      ERROR_ENTRY(303, "Синтаксический анализ: в инструкции не указан тип идентификатора"),
      ERROR_ENTRY(304, "Синтаксический анализ: в инструкции отсутствует название типа"),
      ERROR_ENTRY(305, "Синтаксический анализ: дублирование идентификатора функции"),
      ERROR_ENTRY(306, "Синтаксический анализ: превышено максимальное количество параметров функции"),
      // Семантические ошибки в диапазоне 300-399
      ERROR_ENTRY(307, "Семантический анализ: превышено максимальное количество параметров функции (3)"),
      ERROR_ENTRY(308, "Семантический анализ: несоответствие количества параметров функции"),
      ERROR_ENTRY(309, "Семантический анализ: несоответствие типа параметра функции"),
      ERROR_ENTRY(310, "Лексический анализ: пустая строка или символ"),
      ERROR_ENTRY(311, "Синтаксический анализ: пропущена символ '\"'. Возможно, не указан начальный/конечный символ"),
      // Лексическая ошибка в диапазоне 300-399
      ERROR_ENTRY(312, "Лексический анализ: превышена максимальная длина строки/символа (256 символов)"),
      ERROR_ENTRY(313, "Лексический анализ: неверное значение литерала"),
      // Семантические ошибки в диапазоне 300-399
      ERROR_ENTRY(314, "Семантический анализ: несоответствие типов данных при присваивании"),
      ERROR_ENTRY(315, "Семантический анализ: несоответствие типа возвращаемого значения функции"),
      ERROR_ENTRY(316, "Семантический анализ: недопустимая операция со строковым типом"),
      ERROR_ENTRY(317, "Семантический анализ: неверный тип параметра инструкции"),
      ERROR_ENTRY(318, "Семантический анализ: деление на ноль"),
      ERROR_ENTRY(319, "Лексический анализ: превышена максимальная длина символа"),
      ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),ERROR_ENTRY_NODEF10(350),
      ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),ERROR_ENTRY_NODEF10(390),

      ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
      
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
      ERROR_ENTRY(610, "Синтаксический анализ: ошибка в операторе (правило K)"),
      ERROR_ENTRY(611, "Синтаксический анализ: ошибка в операторе процедуры (правило X)"),
      
      // ========== БЛОК СЕМАНТИЧЕСКИХ ОШИБОК (612-615) ==========
      ERROR_ENTRY(612, "Семантический анализ: неверный параметр. Параметры должны быть идентификатором/выражением"),
      ERROR_ENTRY(613, "Семантический анализ: ошибка в идентификаторе параметра"),
      ERROR_ENTRY(614, "Семантический анализ: недопустимый идентификатор присваивания"),
      ERROR_ENTRY(615, "Семантический анализ: недопустимый идентификатор присваивания в теле типов/значения операторов"),
    ERROR_ENTRY_NODEF(616), ERROR_ENTRY_NODEF(617),ERROR_ENTRY_NODEF(618), ERROR_ENTRY_NODEF(619),
    ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
    ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
    ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
    };

    ERROR GetError(int id)
    {
        if (id < 0 || id > ERROR_MAX_ENTRY)
            return errors[0];
        else
            return errors[id];
    }

    ERROR GetError(int id, int line, int col)
    {
        ERROR err = GetError(id);
        err.position.col = col;
        err.position.line = line;
        return err;
    }
}
