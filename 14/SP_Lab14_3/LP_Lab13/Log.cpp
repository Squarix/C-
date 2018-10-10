#include "stdafx.h"
#include "Log.h"
#include "Error.h"
#include <fstream>
#include <stdio.h>  
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include "Parm.h"

namespace Log
{
	LOG getlog(wchar_t logfile[])// создаем и открываем потоковый вывод
	{
		LOG log;
		wcscpy_s(log.logfile, logfile);
		log.stream = new std::ofstream(logfile, std::ofstream::out);
		if (log.stream->fail()) {
			throw ERROR_THROW(112);
		}
		return log;
	}

	void WriteLine(LOG log, char*c, ...)
	{
		char** pc = &c;            //адрес первого указателя
		int len = 0;
		while (*pc != "") { // цикл для определения общей длины сцепляемых строк
			len += strlen(*pc);
			pc++;
		}
		char *str = new char[len + 1];       //память для строки
		str[0] = 0;                       // очищаем строку
		pc = &c;                       // установка на 1-й параметр
		while (*pc != "") // цикл для сцепления строк
		{
			strcat(str, *pc);             // прицепляем 
			pc++;                       // перемещаемся на следующую
		}
		log.stream->write(str, len);
		delete[] str;
	}

	void WriteLine(LOG log, wchar_t*c, ...)
	{
		wchar_t** pc = &c; //адрес первого указателя 
		int len = 0;
		while (*pc != L"") { // цикл для определения общей длины сцепляемых строк
			len += wcslen(*pc);
			pc++;
		}
		wchar_t *str = new wchar_t[len + 1]; //память для строки 
		char* strl = new char[len + 1];
		str[0] = 0; // очищаем строку
		pc = &c; // установка на 1-й параметр 
		while (*pc != L"") // цикл для сцепления строк 
		{
			wcscat(str, *pc); // прицепляем 
			pc++; // перемещаемся на следующую 
		}
		wcstombs(strl, str, len + 1);
		log.stream->write(strl, len);
		delete[] str;
	}

	void WriteLog(LOG log)
	{
		time_t curTime;
		tm timeStruct;// структура с датой и временем
		time(&curTime);

		char strTime[30];
		localtime_s(&timeStruct, &curTime);// преобразует секунды в текущую дату

		strftime(strTime, 1024, "%d.%m.%Y %H:%M:%S", &timeStruct);// время и дата в строку
		*log.stream << "---- Протокол ------ " << strTime << " ------------------" << std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		*log.stream << "---- Параметры ------" << std::endl;

		char temp[PARM_MAX_SIZE + 1];
		wcstombs(temp, PARM_LOG, wcslen(PARM_LOG) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.log, wcslen(parm.log) + 1);
		*log.stream << temp << std::endl;

		wcstombs(temp, PARM_OUT, wcslen(PARM_OUT) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.out, wcslen(parm.out) + 1);
		*log.stream << temp << std::endl;

		wcstombs(temp, PARM_IN, wcslen(PARM_IN) + 1);
		*log.stream << temp << " ";
		wcstombs(temp, parm.in, wcslen(parm.in) + 1);
		*log.stream << temp << std::endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---- Исходные данные ------" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано    : " << in.ignor << std::endl;
		*log.stream << "Количество строк   : " << in.lines << std::endl;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
	}

	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
		log.stream = NULL;
	}

	void WriteLexems(LOG log, const LT::LexTable& lex)
	{
		Log::WriteLine(log, "---- Таблица лексем ---- \n", "");
		int j = 0;
		while (j < lex.size) 
		{
			int cur_line = lex.table[j].sn; // запоминаем номер строки для текущей лексемы
			Log::WriteLine(log, (char *)std::to_string(cur_line).c_str(), " ", ""); // печатаем номер строки
			while (j < lex.size && cur_line == lex.table[j].sn) {
				char lexname[2];
				lexname[0] = lex.table[j].lexema[0];
				lexname[1] = 0;
				Log::WriteLine(log, (char *)lexname, "");
				j++;
			}
			Log::WriteLine(log, "\n", "");
		}
	}

	void WriteItentifiers(LOG log, const IT::IdTable& ids)
	{
		Log::WriteLine(log, "----Таблица идентификаторов---- \n", "");
		*log.stream << std::setw(10) << "Имя " << std::setw(10) << "Тип Данных " << std::setw(15) << "Тип Идентификатора " << std::setw(15) << "Номер таблицы лексем " << 
			std::setw(15) << "Область видимости " << std::setw(15) << "Знач. по умолчанию" << std::endl ;
		for (int i = 0; i < ids.size; i++)
		{
			if (ids.table[i].idtype != IT::IDTYPE::L) {
				*log.stream << std::setw(10) << ids.table[i].id;
			} else {
				*log.stream << std::setw(10) << "Literal";

			}

			if (ids.table[i].iddatatype == IT::IDDATATYPE::INT) {
				*log.stream << std::setw(10) << "Integer";
			} else {
				*log.stream << std::setw(10) << "String";
			}

			if (ids.table[i].idtype == IT::IDTYPE::V) {
				*log.stream << std::setw(15) << "Variable";
			} else if (ids.table[i].idtype == IT::IDTYPE::F) {
				*log.stream << std::setw(15) << "Function";
			} else if (ids.table[i].idtype == IT::IDTYPE::P) {
				*log.stream << std::setw(15) << "Parameter";
			} else if (ids.table[i].idtype == IT::IDTYPE::L) {
				*log.stream << std::setw(15) << "Literal";
			}

			*log.stream << std::setw(15) << ids.table[i].idxfirstLE;

			*log.stream << std::setw(15) << ids.table[i].vis;

			if (ids.table[i].idtype == IT::IDTYPE::V || ids.table[i].idtype == IT::IDTYPE::L) {
				if (ids.table[i].iddatatype == IT::IDDATATYPE::INT) {
					*log.stream << std::setw(15) << ids.table[i].value.vint << std::endl;
				} else {
					*log.stream << std::setw(15) << "\'" << ids.table[i].value.vstr.str << "\'" << std::endl;
				}
			} else {
				*log.stream << std::setw(15) << "N/A" << std::endl;
			}
		}
	}
}