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
#include "Polish.h"

#include <iostream>

#define EXP1 72
#define EXP2 17
#define EXP3 1

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

		WriteLexems(logger, lex.Lextable, lex.IDtable); // печатаем таблицу лексем
		WriteItentifiers(logger, lex.IDtable); // печатаем таблицу идентификаторов

		if (Polish::PolishNotation(EXP1, lex.Lextable, lex.IDtable)) {
			std::cout << EXP1 << ": польская запись построена" << std::endl;
		} else {
			std::cout << EXP1 << ": польская запись не построена" << std::endl;
		}
		if (Polish::PolishNotation(EXP2, lex.Lextable, lex.IDtable)) {
			std::cout << EXP2 << ": польская запись построена" << std::endl;
		} else {
			std::cout << EXP2 << ": польская запись не построена" << std::endl;
		}
		if (Polish::PolishNotation(EXP3, lex.Lextable, lex.IDtable)) {
			std::cout << EXP3 << ": польская запись построена" << std::endl;
		} else {
			std::cout << EXP3 << ": польская запись не построена" << std::endl;
		}

		WriteLexems(logger, lex.Lextable, lex.IDtable); // печатаем таблицу лексем

		Log::Close(logger);
	}
	catch (Error::ERROR e){
		std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
		std::cout << "Строка " << e.inext.line + 1 << " позиция " << e.inext.col << std::endl << std::endl;;
	}

	system("pause");
	return 0;
}

