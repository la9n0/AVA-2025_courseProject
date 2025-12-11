
#include "Error.h"

namespace Error
{
    ERROR errors[ERROR_MAX_ENTRY] =
    {
      ERROR_ENTRY(0, "Системная ошибка: неопределенный код ошибки"),
      ERROR_ENTRY(1, "Системная ошибка: системный сбой"),
      ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
      ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
      ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
      ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
      ERROR_ENTRY(100, "Параметры ошибки: параметр -in должен быть указан"),
      ERROR_ENTRY(101, "Параметры ошибки: параметры имеют недопустимое значение"),
      ERROR_ENTRY(102, "Параметры ошибки: ошибка при открытии файла с исходным кодом(-in)"),
      ERROR_ENTRY(103, "Параметры ошибки: ошибка при создании файла протокола(-log)"),
      ERROR_ENTRY_NODEF(104), ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107), ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
      ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140),
      ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
      ERROR_ENTRY(200, "Лексический анализ: превышение размера в исходном файле(-in)"),
      ERROR_ENTRY(201, "Лексический анализ: обнаружен недопустимый символ"),
      ERROR_ENTRY(202, "Лексический анализ: неверное имя таблицы лексем"),
      ERROR_ENTRY(203, "Лексический анализ: неверное имя таблицы идентификаторов"),
      ERROR_ENTRY(204, "Лексический анализ: превышен размер идентификатора"),
      ERROR_ENTRY_NODEF(205), ERROR_ENTRY_NODEF(206), ERROR_ENTRY_NODEF(207), ERROR_ENTRY_NODEF(208), ERROR_ENTRY_NODEF(209),
      ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230), ERROR_ENTRY_NODEF10(240),
      ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260), ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),
      ERROR_ENTRY(300, "Синтаксический анализ: неизвестный идентификатор"),
      ERROR_ENTRY(301, "Синтаксический анализ: отсутствует точка входа main"),
      ERROR_ENTRY(302, "Синтаксический анализ: дублирование объявления точки входа main"),
      ERROR_ENTRY(303, "Синтаксический анализ: в инструкции не указан тип идентификатора"),
      ERROR_ENTRY(304, "Синтаксический анализ: в инструкции отсутствует название типа"),
      ERROR_ENTRY(305, "Синтаксический анализ: функция продублирована идентификатор"),
      ERROR_ENTRY(306, "Синтаксический анализ: превышена максимальная длина переменной функции"),
      ERROR_ENTRY(307, "Синтаксический анализ: функция имеет переменные с ошибкой"),
      ERROR_ENTRY(308, "Синтаксический анализ: кол-во параметров функции у определения переменной не совпадает"),
      ERROR_ENTRY(309, "Синтаксический анализ: неправильное место определения переменной"),
      ERROR_ENTRY(310, "Синтаксический анализ: недопустимое значение присвоения/переданного параметра переменной"),
      ERROR_ENTRY(311, "Синтаксический анализ: пропущена символ '\"'. Возможно, не указан начальный/конечный символ"),
      ERROR_ENTRY(312, "Синтаксический анализ: неверный формат объявления функции"),
      ERROR_ENTRY(313, "Синтаксический анализ: недопустимый модификатор функции"),
      ERROR_ENTRY(314, "Синтаксический анализ: типы ошибки в параметре не совпадают"),
      ERROR_ENTRY(315, "Синтаксический анализ: тип функции с переменной функции не совпадают"),
      ERROR_ENTRY(316, "Синтаксический анализ: неправильное выражение оператора справа от знака '='"),
      ERROR_ENTRY(317, "Синтаксический анализ: неверные параметры инструкции"),
      ERROR_ENTRY(318, "Синтаксический анализ: функция не найдена"),
      ERROR_ENTRY(319, "Синтаксический анализ: неверный порядок объявления функции"),
      ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),ERROR_ENTRY_NODEF10(350),
      ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),ERROR_ENTRY_NODEF10(390),

    ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
    ERROR_ENTRY(600, "Семантический анализ: неверный оператор сравнения"),
    ERROR_ENTRY(601, "Семантический анализ: не найден оператор присвоения функции"),
    ERROR_ENTRY(602, "Семантический анализ: ошибка в теле функции"),
    ERROR_ENTRY(603, "Семантический анализ: ошибка в теле процедуры"),
    ERROR_ENTRY(604, "Семантический анализ: ошибка в вызове присвоения функции"),
    ERROR_ENTRY(605, "Семантический анализ: ошибка в вызове функции/процедуры"),
    ERROR_ENTRY(606, "Семантический анализ: ошибка в вызове присвоения переменной функции"),
    ERROR_ENTRY(607, "Семантический анализ: ошибка при идентификации типов/значения операторов"),
    ERROR_ENTRY(608, "Семантический анализ: ошибка в типе типов/значения операторов"),
    ERROR_ENTRY(609, "Семантический анализ: ошибка в порядке типов/значения операторов"),
    ERROR_ENTRY(610, "Семантический анализ: неверный операнд условия"),
    ERROR_ENTRY(611, "Семантический анализ: неверный идентификатор процедуры"),
    ERROR_ENTRY(612, "Семантический анализ: неверный параметр. Параметры должны идентификатора/выражение"),
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
