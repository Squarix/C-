// LP_Lab13.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "Error.h"
#include "In.h"
#include "Log.h"
#include "Parm.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "LexAnalis.h"

#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");

	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);

		Log::LOG logger = Log::getlog(parm.log);

		Log::WriteLog(logger); // печатаем заголовок
		Log::WriteParm(logger, parm); // печатаем входные параметры программы
		Log::WriteIn(logger, in); // печатаем статистику по входу

		In::parsOfToken(in);
		Lexer::LEX lex = Lexer::RunAnalysis(in, logger); // разбираем на лексемы

		WriteLexems(logger, lex.Lextable); // печатаем таблицу лексем
		WriteItentifiers(logger, lex.IDtable); // печатаем таблицу идентификаторов

		Log::Close(logger);
	}
	catch (Error::ERROR e){
		std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
		std::cout << "Строка " << e.inext.line + 1 << " позиция " << e.inext.col << std::endl << std::endl;;
	}

	system("pause");
	return 0;
}

