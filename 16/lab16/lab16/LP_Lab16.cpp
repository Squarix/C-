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
#include "MFST.h"

#include <iostream>

#define EXP1 72
#define EXP2 17
#define EXP3 1

using namespace std;

#define MFST_TRACE_START cout << setw(4) << left << "Шаг " << ": " << setw(20) << left << " Правило" << setw(30) << left << " Входная лента" \
							<< setw(20) << left << " Стек" << endl;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	
	char* test;
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		Log::LOG logger = Log::getlog(parm.log);
		In::parsOfToken(in);
		Lexer::LEX lex_1 = Lexer::RunAnalysis(in, logger);
		Log::Close(logger);

		test = new char[lex_1.Lextable.size + 2];
		for (int i = 0; i < lex_1.Lextable.size; i++)
			test[i] = lex_1.Lextable.table[i].lexema[0];
		test[lex_1.Lextable.size] = '$';
		test[lex_1.Lextable.size + 1] = 0;

		std::cout << test << endl;

		Lexer::LEX lex;
		lex.Lextable = LT::Create(strlen(test));
		lex.Lextable.size = strlen(test);
		for (int i = 0; i < strlen(test); i++)
			lex.Lextable.table[i] = LT::Entry(test[i], 1, 0);

		MFST::Mfst mfst(lex, GRB::Greibach::getGreibach());
		MFST_TRACE_START
			try {
			mfst.start();
			mfst.printRules();
		}
		catch (Error::ERROR e) {
			std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
			std::cout << "Строка " << e.inext.line + 1 << " позиция " << e.inext.col << std::endl << std::endl;
		}
	}
	catch (Error::ERROR e){
		std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
		std::cout << "Строка " << e.inext.line + 1 << " позиция " << e.inext.col << std::endl << std::endl;;
	}

	//char test[] = "tfi(ti,ti){dti;i=i*((i+i);ri;};m{dti;ri;};$";
	////char test[] = "m{dti;ri;};$";

	//Lexer::LEX lex;
	//lex.Lextable = LT::Create(strlen(test));
	//lex.Lextable.size = strlen(test);
	//for (int i = 0; i < strlen(test); i++)
	//	lex.Lextable.table[i] = LT::Entry(test[i], 1, 0);

	//MFST::Mfst mfst(lex, GRB::Greibach::getGreibach());
	//MFST_TRACE_START
	//	try {
	//	mfst.start();
	//	mfst.printRules();
	//}
	//catch (Error::ERROR e) {
	//	std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
	//	std::cout << "Строка " << e.inext.line + 1 << " позиция " << e.inext.col << std::endl << std::endl;
	//}


	//try {
	//	Parm::PARM parm = Parm::getparm(argc, argv);
	//	In::IN in = In::getin(parm.in);

	//	Log::LOG logger = Log::getlog(parm.log);

	//	Log::WriteLog(logger); // печатаем заголовок
	//	Log::WriteParm(logger, parm); // печатаем входные параметры программы
	//	Log::WriteIn(logger, in); // печатаем статистику по входу

	//	In::parsOfToken(in);
	//	Lexer::LEX lex = Lexer::RunAnalysis(in, logger); // разбираем на лексемы

	//	WriteLexems(logger, lex.Lextable, lex.IDtable); // печатаем таблицу лексем
	//	WriteItentifiers(logger, lex.IDtable); // печатаем таблицу идентификаторов

	//	if (Polish::PolishNotation(EXP1, lex.Lextable, lex.IDtable)) {
	//		std::cout << EXP1 << ": польская запись построена" << std::endl;
	//	}
	//	else {
	//		std::cout << EXP1 << ": польская запись не построена" << std::endl;
	//	}
	//	if (Polish::PolishNotation(EXP2, lex.Lextable, lex.IDtable)) {
	//		std::cout << EXP2 << ": польская запись построена" << std::endl;
	//	}
	//	else {
	//		std::cout << EXP2 << ": польская запись не построена" << std::endl;
	//	}
	//	if (Polish::PolishNotation(EXP3, lex.Lextable, lex.IDtable)) {
	//		std::cout << EXP3 << ": польская запись построена" << std::endl;
	//	}
	//	else {
	//		std::cout << EXP3 << ": польская запись не построена" << std::endl;
	//	}

	//	WriteLexems(logger, lex.Lextable, lex.IDtable); // печатаем таблицу лексем

	//	Log::Close(logger);
	//}
	//catch (Error::ERROR e) {
	//	std::cout << "Ошибка " << e.id << ": " << e.message << std::endl << std::endl;
	//	std::cout << "Строка " << e.inext.line + 1 << " позиция " << e.inext.col << std::endl << std::endl;;
	//}



	system("pause");
	return 0;
}

