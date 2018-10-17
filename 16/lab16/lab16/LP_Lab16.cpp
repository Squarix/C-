// LP_Lab13.cpp: ���������� ����� ����� ��� ����������� ����������.
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

#define MFST_TRACE_START cout << setw(4) << left << "��� " << ": " << setw(20) << left << " �������" << setw(30) << left << " ������� �����" \
							<< setw(20) << left << " ����" << endl;

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
			std::cout << "������ " << e.id << ": " << e.message << std::endl << std::endl;
			std::cout << "������ " << e.inext.line + 1 << " ������� " << e.inext.col << std::endl << std::endl;
		}
	}
	catch (Error::ERROR e){
		std::cout << "������ " << e.id << ": " << e.message << std::endl << std::endl;
		std::cout << "������ " << e.inext.line + 1 << " ������� " << e.inext.col << std::endl << std::endl;;
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
	//	std::cout << "������ " << e.id << ": " << e.message << std::endl << std::endl;
	//	std::cout << "������ " << e.inext.line + 1 << " ������� " << e.inext.col << std::endl << std::endl;
	//}


	//try {
	//	Parm::PARM parm = Parm::getparm(argc, argv);
	//	In::IN in = In::getin(parm.in);

	//	Log::LOG logger = Log::getlog(parm.log);

	//	Log::WriteLog(logger); // �������� ���������
	//	Log::WriteParm(logger, parm); // �������� ������� ��������� ���������
	//	Log::WriteIn(logger, in); // �������� ���������� �� �����

	//	In::parsOfToken(in);
	//	Lexer::LEX lex = Lexer::RunAnalysis(in, logger); // ��������� �� �������

	//	WriteLexems(logger, lex.Lextable, lex.IDtable); // �������� ������� ������
	//	WriteItentifiers(logger, lex.IDtable); // �������� ������� ���������������

	//	if (Polish::PolishNotation(EXP1, lex.Lextable, lex.IDtable)) {
	//		std::cout << EXP1 << ": �������� ������ ���������" << std::endl;
	//	}
	//	else {
	//		std::cout << EXP1 << ": �������� ������ �� ���������" << std::endl;
	//	}
	//	if (Polish::PolishNotation(EXP2, lex.Lextable, lex.IDtable)) {
	//		std::cout << EXP2 << ": �������� ������ ���������" << std::endl;
	//	}
	//	else {
	//		std::cout << EXP2 << ": �������� ������ �� ���������" << std::endl;
	//	}
	//	if (Polish::PolishNotation(EXP3, lex.Lextable, lex.IDtable)) {
	//		std::cout << EXP3 << ": �������� ������ ���������" << std::endl;
	//	}
	//	else {
	//		std::cout << EXP3 << ": �������� ������ �� ���������" << std::endl;
	//	}

	//	WriteLexems(logger, lex.Lextable, lex.IDtable); // �������� ������� ������

	//	Log::Close(logger);
	//}
	//catch (Error::ERROR e) {
	//	std::cout << "������ " << e.id << ": " << e.message << std::endl << std::endl;
	//	std::cout << "������ " << e.inext.line + 1 << " ������� " << e.inext.col << std::endl << std::endl;;
	//}



	system("pause");
	return 0;
}

