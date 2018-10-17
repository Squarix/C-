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

		Log::WriteLog(logger); // �������� ���������
		Log::WriteParm(logger, parm); // �������� ������� ��������� ���������
		Log::WriteIn(logger, in); // �������� ���������� �� �����

		In::parsOfToken(in);
		Lexer::LEX lex = Lexer::RunAnalysis(in, logger); // ��������� �� �������

		WriteLexems(logger, lex.Lextable, lex.IDtable); // �������� ������� ������
		WriteItentifiers(logger, lex.IDtable); // �������� ������� ���������������

		if (Polish::PolishNotation(EXP1, lex.Lextable, lex.IDtable)) {
			std::cout << EXP1 << ": �������� ������ ���������" << std::endl;
		} else {
			std::cout << EXP1 << ": �������� ������ �� ���������" << std::endl;
		}
		if (Polish::PolishNotation(EXP2, lex.Lextable, lex.IDtable)) {
			std::cout << EXP2 << ": �������� ������ ���������" << std::endl;
		} else {
			std::cout << EXP2 << ": �������� ������ �� ���������" << std::endl;
		}
		if (Polish::PolishNotation(EXP3, lex.Lextable, lex.IDtable)) {
			std::cout << EXP3 << ": �������� ������ ���������" << std::endl;
		} else {
			std::cout << EXP3 << ": �������� ������ �� ���������" << std::endl;
		}

		WriteLexems(logger, lex.Lextable, lex.IDtable); // �������� ������� ������

		Log::Close(logger);
	}
	catch (Error::ERROR e){
		std::cout << "������ " << e.id << ": " << e.message << std::endl << std::endl;
		std::cout << "������ " << e.inext.line + 1 << " ������� " << e.inext.col << std::endl << std::endl;;
	}

	system("pause");
	return 0;
}

